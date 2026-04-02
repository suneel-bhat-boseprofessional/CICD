"""
TUII Packet Test Vector Generator
Run: python test_packets.py
Generates hex byte sequences for testing Protocol_ProcessReceivedData()
"""
import struct

def crc16_ccitt(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= byte << 8
        for _ in range(8):
            if crc & 0x8000:
                crc = (crc << 1) ^ 0x1021
            else:
                crc <<= 1
            crc &= 0xFFFF
    return crc

def build_packet(name, sof, payload_str):
    payload = payload_str.encode('ascii')
    length = len(payload)
    crc_data = bytes([length]) + payload
    crc = crc16_ccitt(crc_data)
    packet = bytes(sof) + struct.pack('<H', crc) + bytes([length]) + payload
    hex_str = ' '.join(f'{b:02X}' for b in packet)
    print(f'\n=== {name} ===')
    print(f'  Payload ({length}B): {payload_str}')
    print(f'  LEN: 0x{length:02X} ({length})')
    print(f'  CRC16: 0x{crc:04X}  (LE bytes: {crc&0xFF:02X} {(crc>>8)&0xFF:02X})')
    print(f'  Full packet ({len(packet)}B hex):')
    print(f'  {hex_str}')
    c_arr = ', '.join(f'0x{b:02X}' for b in packet)
    print(f'  C array: uint8_t pkt[] = {{ {c_arr} }};')
    return packet

NORM = [0xA2, 0xB2, 0xC2, 0xD2]
OTA  = [0xA1, 0xB1, 0xC1, 0xD1]

print('=' * 60)
print('TUII PACKET TEST VECTORS')
print('=' * 60)

# --- Valid Normal packets ---
build_packet('TEST 1: Normal - ready',
    NORM, '{"action":"ready"}')

build_packet('TEST 2: Normal - setFanSpeed LOW',
    NORM, '{"action":"setFanSpeed","payload":{"speed":"LOW"}}')

build_packet('TEST 3: Normal - setGain',
    NORM, '{"action":"setGain","payload":{"zone":0,"norm":50}}')

build_packet('TEST 4: Normal - setMute',
    NORM, '{"action":"setMute","payload":{"zone":0,"state":"true"}}')

# --- Valid OTA packet ---
build_packet('TEST 5: OTA packet',
    OTA, 'OTA_START')

# --- Negative tests ---
print('\n=== TEST 6: Bad CRC (expect: CRC MISMATCH nack) ===')
good = build_packet('(base)', NORM, '{"action":"ready"}')
bad = bytearray(good)
bad[4] ^= 0xFF  # flip CRC low byte
c_arr = ', '.join(f'0x{b:02X}' for b in bad)
print(f'  C array: uint8_t bad_crc[] = {{ {c_arr} }};')

print('\n=== TEST 7: Bad SOF (expect: INVALID SOF nack) ===')
bad_sof = bytes([0xAA, 0xBB, 0xCC, 0xDD]) + bytes(good[4:])
c_arr = ', '.join(f'0x{b:02X}' for b in bad_sof)
print(f'  C array: uint8_t bad_sof[] = {{ {c_arr} }};')

print('\n=== TEST 8: Truncated packet (expect: LENGTH ERROR nack) ===')
trunc = bytes(good[:5])  # only 5 of 7 header bytes
c_arr = ', '.join(f'0x{b:02X}' for b in trunc)
print(f'  C array: uint8_t trunc[] = {{ {c_arr} }};')
