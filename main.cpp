/* mbed Microcontroller Library
 * Copyright (c) 2021 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <array>
#include <string>
#include <vector>

#include "mbed.h"

Mutex stdio_mutex;

InterruptIn button(A0);
DigitalOut A(D12);
DigitalOut B(D13);
DigitalOut C(D2);
DigitalOut D(D3);
DigitalOut E(D4);
DigitalOut F(D5);
DigitalOut G(D6);
DigitalOut DP(D7);
DigitalOut Digit1(D8);
DigitalOut Digit2(D9);
DigitalOut Digit3(D10);
DigitalOut Digit4(D11);
Thread Display;
Thread Echo_RN;
Thread Rn4020;

int Counter(0);

// BLE
BufferedSerial rn(PA_11, PA_12);
BufferedSerial pc(USBTX, USBRX);

std::array<DigitalOut*, 11> Pins = {&A, &B, &C, &D, &E, &F, &G, &Digit1, &Digit2, &Digit3, &Digit4};
std::array<int, 4> Digits = {7, 8, 9, 10};
std::array<int, 4> Numbers = {1, 2, 3, 4};

std::vector<std::vector<int>> Single_Digit = {{0, 1, 2, 3, 4, 5},    {1, 2},
                                              {0, 1, 3, 4, 6},       {0, 1, 2, 3, 6},
                                              {1, 2, 5, 6},          {0, 2, 3, 5, 6},
                                              {0, 2, 3, 4, 5, 6},    {0, 1, 2, 5},
                                              {0, 1, 2, 3, 4, 5, 6}, {0, 1, 2, 3, 5, 6}};

std::vector<std::vector<int>> Single_Digit_Hex = {{0, 1, 2, 3, 4, 5},    {1, 2},
                                                  {0, 1, 3, 4, 6},       {0, 1, 2, 3, 6},
                                                  {1, 2, 5, 6},          {0, 2, 3, 5, 6},
                                                  {0, 2, 3, 4, 5, 6},    {0, 1, 2, 5},
                                                  {0, 1, 2, 3, 4, 5, 6}, {0, 1, 2, 3, 5, 6},
                                                  {0, 1, 2, 4, 5, 6},    {2, 3, 4, 5, 6},
                                                  {0, 3, 4, 5},          {1, 2, 3, 4, 6},
                                                  {0, 3, 4, 5, 6},       {0, 4, 5, 6}};

void print_string(std::string);
void pin_reset();
void print_num();
void display_loop();
void RN_echo_loop();
void Recieve_loop();
void counter_reset();

// BLE
void RN_write(std::string);
void PC_write(std::string);
void BLE_Setup();

int Hex_char_to_int(char s) {
    if ((s >= '0') && (s <= '9')) return s - '0';
    if ((s >= 'a') && (s <= 'f')) return s - 'a' + 10;
    if ((s >= 'A') && (s <= 'F')) return s - 'A' + 10;
    return 0;
}

int main() {
    Display.start(display_loop);
    button.mode(PullUp);
    button.rise(counter_reset);
    // UART
    rn.set_baud(115200);
    rn.set_format(8, BufferedSerial::None, 1);
    pc.set_baud(9600);
    pc.set_format(8, BufferedSerial::None, 1);
    Echo_RN.start(RN_echo_loop);
    ThisThread::sleep_for(1000ms);
    PC_write("Initializing\n\r");
    BLE_Setup();
    Echo_RN.terminate();
    Rn4020.start(Recieve_loop);
    while (1) {  // wait around, interrupts will interrupt this!
        ThisThread::sleep_for(1000ms);
        Counter++;
        char buf[50];
        sprintf(buf, "SUW,955CAEE350744338BD514F8945096ADE,%04x\n\r", Counter);
        RN_write(buf);  // 読み出しを4Byte
    }
}

void pin_reset() {
    for (int i = 0; i < 11; ++i) {
        *Pins[i] = 1;
    }
    for (int i = 0; i < (int)Digits.size(); ++i) {
        *Pins[Digits[i]] = 0;
    }
}

void print_num() {
    int Counter_Buf = Counter;
    Numbers[3] = Counter_Buf % 10;
    Counter_Buf /= 10;
    Numbers[2] = Counter_Buf % 10;
    Counter_Buf /= 10;
    Numbers[1] = Counter_Buf % 10;
    Counter_Buf /= 10;
    Numbers[0] = Counter_Buf % 10;
    Counter_Buf /= 10;
    for (int i = 0; i < (int)Digits.size(); ++i) {
        *Pins[Digits[i]] = 1;
        for (int j = 0; j < (int)Single_Digit[Numbers[i]].size(); ++j) {
            *Pins[Single_Digit[Numbers[i]][j]] = 0;
        }
        ThisThread::sleep_for(10ms);
        for (int j = 0; j < (int)Single_Digit[Numbers[i]].size(); ++j) {
            *Pins[Single_Digit[Numbers[i]][j]] = 1;
        }
        *Pins[Digits[i]] = 0;
    }
}

void display_loop() {
    pin_reset();
    while (1) {
        print_num();
    }
}

void RN_echo_loop() {
    char buf[64] = {0};
    while (1) {
        if (uint32_t num = rn.read(buf, sizeof(buf))) {
            pc.write(buf, num);
        }
    }
}

void Recieve_loop() {
    char buf[32] = {0};
    int prev = 0;
    int data = 0;
    while (1) {
        ThisThread::sleep_for(1000ms);
        RN_write("SUR,F92DF428C4D940349F1AD8BCF3D2223D\n\r");  // 書き出しを4Byte
        uint32_t num = rn.read(buf, sizeof(buf));
        data = 16 * 256 * Hex_char_to_int(buf[0]) + 256 * Hex_char_to_int(buf[1]) +
               16 * Hex_char_to_int(buf[2]) + 1 * Hex_char_to_int(buf[3]);
        if (data != prev) {
            Counter = data;
        }
        prev = data;
    }
}

void counter_reset() { Counter = 0; }

// Event
void print_string(std::string str) { printf("%s", str.c_str()); }

// BLE
void RN_write(std::string str) { rn.write(str.c_str(), str.size()); }

void PC_write(std::string str) { pc.write(str.c_str(), str.size()); }

void BLE_Setup() {
    ThisThread::sleep_for(1500ms);
    PC_write("RN4020を初期化中\n\r");
    RN_write("SF,1\r");  // 工場出荷時の設定に戻す
    ThisThread::sleep_for(500ms);
    PC_write("再起動\n\r");
    RN_write("R,1\r\n");  // 再起動
    ThisThread::sleep_for(1500ms);
    PC_write("プライベートサービスの設定を許可\n\r");
    RN_write("SS,C0000001\r\n");  //
    ThisThread::sleep_for(500ms);
    PC_write("RN4020をペリフェラルに設定\n\r");
    RN_write("SR,00000000\r\n");
    ThisThread::sleep_for(500ms);
    PC_write("すでにあるプライベートサービスを消去\n\r");
    RN_write("PZ\r\n");
    ThisThread::sleep_for(500ms);
    PC_write("プライベートUUIDを設定\n\r");
    RN_write("PS,59FF01A0305E4792B287BA41E7DF33B7\r\n");
    ThisThread::sleep_for(200ms);
    /* RN_write("PC,CF360C17E1E041378B8F5DBA634D0E6A,01,04\r\n"); // ブロードキャスト */
    /* ThisThread::sleep_for(200ms); */
    /* RN_write("PC,D25849BBB6804AE1B855EA9EABE8AEDB,02,04\n\r"); // 読み出し */
    /* ThisThread::sleep_for(200ms); */
    /* RN_write("PC,287B890FD4814806ABF7B31FE78A414C,04,04\n\r"); // 応答なし書き込み */
    /* ThisThread::sleep_for(200ms); */
    /* RN_write("PC,603B159624D6468AA6F46B07FF9E614D,08,04\n\r"); // 書き込み */
    /* ThisThread::sleep_for(200ms); */
    /* RN_write("PC,99D0CAF32E80446AB6B502BBB5EB923E,10,04\n\r"); // ノーティフィケーション */
    /* ThisThread::sleep_for(200ms); */
    /* RN_write("PC,45D471BC1BE145A99382069C8DC61E3F,20,04\n\r"); // インディケーション */
    /* ThisThread::sleep_for(200ms); */
    /* ここでは、読み出しと書き込みだけしかやらなくていいので、その二つを設定 */
    /* ThisThread::sleep_for(200ms); */
    RN_write("PC,955CAEE350744338BD514F8945096ADE,02,04\n\r");  // 読み出しを4Byte
    ThisThread::sleep_for(200ms);
    RN_write("PC,F92DF428C4D940349F1AD8BCF3D2223D,08,04\n\r");  // 書き出しを4Byte
    ThisThread::sleep_for(200ms);
    PC_write("各サービスの設定完了\n\r");
    RN_write("U\r");
    ThisThread::sleep_for(500ms);
    PC_write("再起動\n\r");
    RN_write("R,1\r");
    ThisThread::sleep_for(1500ms);
    RN_write("A\r");
    RN_write("LS\r");
    ThisThread::sleep_for(500ms);
}
