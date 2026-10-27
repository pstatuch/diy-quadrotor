
#include <Arduino.h>
#include "config.h"

constexpr int RX_PIN = RADIO_UART_RX_PIN;
constexpr int TX_PIN = RADIO_UART_TX_PIN;

HardwareSerial ReceiverSerial(1);

uint8_t frame[64];
int framePos = 0;
int frameLength = 0;

uint16_t channels[16];

uint8_t crc8DvbS2(const uint8_t *data, int len) {
    uint8_t crc = 0;

    for (int i = 0; i < len; i++) {
        crc ^= data[i];

        for (int bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0xD5;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

bool decodeChannels() {
    // CRSF frame: address, length, type, payload, CRC
    if (frame[2] != 0x16 || frameLength != 26) {
        return false;
    }

    // CRC obejmuje typ ramki i payload
    uint8_t crc = crc8DvbS2(&frame[2], 23);

    if (crc != frame[25]) {
        return false;
    }

    // 22 bajty payload = 16 kanałów po 11 bitów
    const uint8_t *p = &frame[3];

    for (int ch = 0; ch < 16; ch++) {
        int bitIndex = ch * 11;
        uint16_t value = 0;

        for (int bit = 0; bit < 11; bit++) {
            int index = bitIndex + bit;

            if (p[index / 8] & (1 << (index % 8))) {
                value |= (1 << bit);
            }
        }

        channels[ch] = value;
    }

    return true;
}

void initReceiver() {
    Serial.begin(115200);

    ReceiverSerial.begin(
        420000,
        SERIAL_8N1,
        RX_PIN,
        TX_PIN
    );

    Serial.println("CRSF channel decoder started");
}

void updateChanels() {
    while (ReceiverSerial.available()) {
        uint8_t b = ReceiverSerial.read();

        if (framePos == 0) {
            if (b != 0xC8) continue;

            frame[framePos++] = b;
            continue;
        }

        if (framePos >= (int)sizeof(frame)) {
            framePos = 0;
            continue;
        }

        frame[framePos++] = b;

        if (framePos == 2) {
            frameLength = frame[1] + 2;

            if (frameLength < 4 ||
                frameLength > (int)sizeof(frame)) {
                framePos = 0;
                continue;
            }
        }

        if (framePos == frameLength) {
            if (decodeChannels()) {
                static uint32_t lastPrint = 0;

                if (millis() - lastPrint >= 100) {
                    lastPrint = millis();

                    for (int ch = 0; ch < 16; ch++) {
                        Serial.printf(
                            "CH%02d:%4u ",
                            ch + 1,
                            channels[ch]
                        );
                    }

                    Serial.println();
                }
            }

            framePos = 0;
        }
    }
}
