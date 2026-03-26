# Protocol API Reference

**File:** `protocol.c` / `protocol.h`  
**Transport:** UART (idle-line detection)  
**Format:** Single-line JSON, terminated with `\r\n`

---

## Message Envelope

All messages use a flat JSON envelope:

```json
{"action": "string", "payload": {...}}
```

| Field     | Type   | Description                         |
|-----------|--------|-------------------------------------|
| `action`  | string | Identifies the command or event     |
| `payload` | object | Action-specific data                |

> All messages must be sent as a **single line** (no embedded newlines).  
> String buffers: `action` max 32 chars, `payload` max 256 chars.

---

## Error Response (NACK)

On failure the device sends a NACK. **No response is sent on success.**

```json
{"action": "nack", "payload": {"error": "ERROR STRING", "value": -1}}
```

| Field            | Type   | Description                                 |
|------------------|--------|---------------------------------------------|
| `error`          | string | Human-readable error description            |
| `value`          | int    | Error code (negative = parse error, 4xxx = action error) |

---

## Actions

### `identity`

Device identity information sent from the connected device.

```json
{
  "action": "identity",
  "payload": {
    "Id":      "0984621562",
    "Version": "0.0.1",
    "Mac":     "AA:BB:CC:DD:EE:01",
    "Ip":      "192.168.1.100",
    "IpMask":  "255.255.255.0",
    "Gateway": "192.168.1.1",
    "Dhcp":    true
  }
}
```

| Field     | Type    | Required | Description             |
|-----------|---------|----------|-------------------------|
| `Id`      | string  | Yes      | Device identifier       |
| `Version` | string  | Yes      | Firmware version        |
| `Mac`     | string  | Yes      | MAC address             |
| `Ip`      | string  | Yes      | IP address              |
| `IpMask`  | string  | Yes      | Subnet mask             |
| `Gateway` | string  | Yes      | Default gateway         |
| `Dhcp`    | boolean | Yes      | DHCP enabled flag       |

**NACK codes:**

| Code | Error                      |
|------|----------------------------|
| 4201 | `MISSING IDENTITY.ID`      |
| 4202 | `MISSING IDENTITY.VERSION` |
| 4203 | `MISSING IDENTITY.MAC`     |
| 4204 | `MISSING IDENTITY.IP`      |
| 4205 | `MISSING IDENTITY.IPMASK`  |
| 4206 | `MISSING IDENTITY.GATEWAY` |
| 4207 | `MISSING IDENTITY.DHCP`    |

---

### `zone`

Defines or updates a zone. Zones are applied one-by-one. The visible zone count grows automatically as higher indices arrive. By default, the zone screen starts with zero icons.

```json
{
  "action": "zone",
  "payload": {
    "Index": 0,
    "Name":  "Room",
    "Gain": {
      "DefGain": 50,
      "DefMute": false
    },
    "sources": ["HDMI 1", "HDMI 2", "Bluetooth"]
  }
}
```

| Field           | Type     | Required | Description                                      |
|-----------------|----------|----------|--------------------------------------------------|
| `Index`         | int      | Yes      | Zero-based zone index                            |
| `Name`          | string   | Yes      | Display name (max 31 chars)                      |
| `Gain.DefGain`  | int      | No       | Default volume level (0–100)                     |
| `Gain.DefMute`  | boolean  | No       | Default mute state (`true`/`false`)              |
| `sources`       | string[] | No       | Available source names (stored for future use)   |

> Zone count only grows — sending a lower index will not reduce visible icons.  
> `DefMute` is applied before `DefGain` to ensure gain is always the authoritative value.

**NACK codes:**

| Code | Error                |
|------|----------------------|
| 4301 | `MISSING ZONE.INDEX` |
| 4302 | `INVALID ZONE.INDEX` |
| 4303 | `MISSING ZONE.NAME`  |

---

### `setGain`

Sets the gain (volume) for a zone at runtime.

```json
{
  "action": "setGain",
  "payload": {
    "zone": 0,
    "db":   -10.5,
    "norm": 0.75
  }
}
```

| Field  | Type  | Required      | Description                                                   |
|--------|-------|---------------|---------------------------------------------------------------|
| `zone` | int   | Yes           | Target zone index (must be within current zone count)         |
| `norm` | float | Yes (or `db`) | Direct volume value 0–100, rounded to nearest integer         |
| `db`   | float | Yes (or `norm`)| dB value; used as fallback if `norm` is absent               |

> `norm` takes priority over `db` if both are present.

**NACK codes:**

| Code | Error                           |
|------|---------------------------------|
| 4401 | `MISSING GAIN.ZONE`             |
| 4402 | `INVALID GAIN.ZONE`             |
| 4403 | `MISSING GAIN.NORM OR GAIN.DB`  |

---

### `setMute`

Sets the mute state for a zone at runtime.

```json
{
  "action": "setMute",
  "payload": {
    "zone":  0,
    "state": true
  }
}
```

| Field   | Type    | Required | Description                                           |
|---------|---------|----------|-------------------------------------------------------|
| `zone`  | int     | Yes      | Target zone index (must be within current zone count) |
| `state` | boolean | Yes      | `true` / `"1"` to mute; `false` / `"0"` to unmute    |

> Muting saves the current volume. Unmuting restores the last saved volume if the current value is zero.  
> Volume set via `setGain` is preserved through mute/unmute transitions.

**NACK codes:**

| Code | Error                |
|------|----------------------|
| 4501 | `MISSING MUTE.ZONE`  |
| 4502 | `INVALID MUTE.ZONE`  |
| 4503 | `MISSING MUTE.STATE` |

---

### `setFanSpeed` *(internal)*

Controls the PWM fan output.

```json
{
  "action": "setFanSpeed",
  "payload": {
    "speed": "LOW"
  }
}
```

| `speed` value | PWM duty cycle |
|---------------|---------------|
| `LOW`         | 30%           |
| `MID`         | 60%           |
| `HIGH`        | 100%          |

**NACK codes:**

| Code | Error                 |
|------|-----------------------|
| 4001 | `MISSING SPEED`       |
| 4002 | `INVALID SPEED`       |

---

## General NACK Codes

| Code | Error            | Trigger                              |
|------|------------------|--------------------------------------|
| -1   | `INVALID PACKET` | JSON parse failure or missing action |
| 4004 | `FAILED ACTION`  | Action string not recognised         |

---

## Example Session

```
→ {"action":"identity","payload":{"Id":"001","Version":"0.0.1","Mac":"AA:BB:CC:DD:EE:01","Ip":"192.168.1.100","IpMask":"255.255.255.0","Gateway":"192.168.1.1","Dhcp":false}}
← (no response — success)

→ {"action":"zone","payload":{"Index":0,"Name":"Living Room","Gain":{"DefGain":75,"DefMute":false},"sources":["HDMI 1","Bluetooth"]}}
← (no response — success)

→ {"action":"zone","payload":{"Index":1,"Name":"Kitchen","Gain":{"DefGain":50,"DefMute":true},"sources":["HDMI 2"]}}
← (no response — success)

→ {"action":"setGain","payload":{"zone":0,"norm":0.80}}
← (no response — success)

→ {"action":"setMute","payload":{"zone":1,"state":false}}
← (no response — success)

→ {"action":"setGain","payload":{"zone":99,"norm":0.5}}
← {"action":"nack","payload":{"error":"INVALID GAIN.ZONE","value":4402}}

→ bad json here
← {"action":"nack","payload":{"error":"INVALID PACKET","value":-1}}
```
