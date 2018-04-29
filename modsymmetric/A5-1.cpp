#include <iostream>
using namespace std;

#define R1MASK  0x07FFFF
#define R2MASK  0x3FFFFF
#define R3MASK  0x7FFFFF
#define R1MID   0x000100
#define R2MID   0x000400
#define R3MID   0x000400
#define R1TAPS  0x072000
#define R2TAPS  0x300000
#define R3TAPS  0x700080
#define R1OUT   0x040000
#define R2OUT   0x200000
#define R3OUT   0x400000

typedef unsigned char byte;
typedef unsigned long word;
typedef word bit;
const int loop1 = 64;
const int loop2 = 22;
const int mix = 100;

class A5_1 {
public:
    bit parity(word x);
    word clockOne(word reg, word mask, word taps);
    bit majority();
    void clock();
    void clockAllThree();
    bit getBit();
    void setKey(byte key[], word frame);
    void getKey(byte aToBKeyStream[], byte bToAKeyStream[]);
    void run();
private:
    word R1, R2, R3;

};


void A5_1::setKey(byte key[], word frame) {
    int i;
    bit keyBit, frameBit;
    R1 = R2 = R3 = 0;
    for (i = 0; i < loop1; i++) {
        clockAllThree();
        keyBit = (key[i / 8] >> (i & 7)) & 1;
        R1 ^= keyBit;
        R2 ^= keyBit;
        R3 ^= keyBit;
    }

    for (i = 0; i < loop2; i++) {
        clockAllThree();
        frameBit = (frame >> i) & 1;
        R1 ^= frameBit;
        R2 ^= frameBit;
        R3 ^= frameBit;
    }

    for (i = 0; i < mix; i++) {
        clock();
    }
}

bit A5_1::parity(word x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;
}

bit A5_1::majority() {
    int sum;
    sum = parity(R1 & R1MID) + parity(R2 & R2MID) + parity(R3 & R3MID);
    if (sum >= 2) {
        return 1;
    }
    return 0;
}

word A5_1::clockOne(word reg, word mask, word taps) {
    word t = reg & taps;
    reg = (reg << 1) & mask;
    reg |= parity(t);
    return reg;
}

void A5_1::clock() {
    bit maj = majority();
    if (((R1 & R1MID) != 0) == maj) {
        R1 = clockOne(R1, R1MASK, R1TAPS);
    }

    if (((R2 & R2MID) != 0) == maj) {
        R2 = clockOne(R2, R2MASK, R2TAPS);
    }

    if (((R3 & R3MID) != 0) == maj) {
        R3 = clockOne(R3, R3MASK, R3TAPS);
    }
}

void A5_1::clockAllThree() {
    R1 = clockOne(R1, R1MASK, R1TAPS);
    R2 = clockOne(R2, R2MASK, R2TAPS);
    R3 = clockOne(R2, R2MASK, R2TAPS);
}

bit A5_1::getBit() {
    return parity(R1 & R1OUT) ^ parity(R2 & R2OUT) ^ parity(R3 & R3OUT);
}

void A5_1::getKey(byte aToBKeyStream[], byte bToAKeyStream[]) {
    int i;
    for (i = 0; i < 15; i++) {
        aToBKeyStream[i] = bToAKeyStream[i] = 0;
    }

    for (i = 0; i < 114; i++) {
        clock();
        aToBKeyStream[i / 8] |= getBit() << (7 - (i & 7));
    }

    for (i = 0; i < 114; i++) {
        clock();
        bToAKeyStream[i / 8] |= getBit() << (7 - (i & 7));
    }
}

void A5_1::run() {
    byte key[8] = { 0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    word frame = 0x134;
    byte goodAToB[15] = {0x53, 0x4E, 0xAA, 0x58, 0x2F, 0xE8, 0x15, 0x1A,
                         0xB6, 0xE1, 0x85, 0x5A, 0x72, 0x8C, 0x00};
    byte goodBToA[15] = {0x24, 0xFD, 0x35, 0xA3, 0x5D, 0x5F, 0xB6, 0x52,
                         0x6D, 0x32, 0xF9, 0x06, 0xDF, 0x1A, 0xC0};
    byte aToB[15], bToA[15];
    int i;
    setKey(key, frame);
    getKey(aToB, bToA);
    for (i = 0; i < 15; i++) {
        cout << aToB[i] << '\t';
        if (aToB[i] != goodAToB[i]) {
            cout << "A to B Failed!" << endl;
        }
    }

    cout << endl;
    
    for (i = 0; i < 15; i++) {
        cout << bToA[i] << '\t';
        if (bToA[i] != goodBToA[i]) {
            cout << "B to A Failed!" << endl;
        }
    }

    cout << endl;
}

int main() {
    A5_1 a;
    a.run();
    return 0;
}
