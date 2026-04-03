import serial, struct, time

def crc16_ccitt(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= byte << 8
        for _ in range(8):
            crc = ((crc << 1) ^ 0x1021) if crc & 0x8000 else (crc << 1)
            crc &= 0xFFFF
    return crc

def build_ota_request(cmd, payload=b''):
    sof = bytes([0xA1, 0xB1, 0xC1, 0xD1])
    length = len(payload)
    crc_data = bytes([cmd, (length >> 8) & 0xFF, length & 0xFF]) + payload
    crc = crc16_ccitt(crc_data)
    return sof + crc_data + struct.pack('<H', crc)

def send_ota(ser, name, cmd, payload=b''):
    pkt = build_ota_request(cmd, payload)
    print(f'\n--- {name} ---')
    print(f'TX ({len(pkt)}B): {pkt.hex(" ").upper()}')
    ser.reset_input_buffer()
    ser.write(pkt)
    time.sleep(0.5)
    resp = ser.read(ser.in_waiting or 64)
    if resp:
        print(f'RX ({len(resp)}B): {resp.hex(" ").upper()}')
        # Parse response: SOF(4) CMD(1) STATUS(1) LEN(2) PAYLOAD(LEN) CRC(2)
        if len(resp) >= 8:
            cmd_r = resp[4]
            status = resp[5]
            plen = (resp[6] << 8) | resp[7]
            print(f'  CMD=0x{cmd_r:02X}  STATUS={"OK" if status==0 else "ERROR"}  PayloadLen={plen}')
            if plen > 0 and len(resp) >= 8 + plen:
                print(f'  Payload: {resp[8:8+plen].hex(" ").upper()}')
    else:
        print('RX: (no response)')

# Usage:
port = 'COM21'  # adjust to your port
ser = serial.Serial(port, 115200, timeout=1)

send_ota(ser, 'IDENTIFY', 0x01)
#send_ota(ser, 'UNKNOWN CMD', 0xFF)
send_ota(ser, 'ENTER BOOTLOADER', 0x02)  # uncomment to reboot!

ser.close()