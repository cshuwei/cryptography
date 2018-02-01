#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DES {
public:
    DES();
    void setKey(string k);
    void setPlainText(string p);
    unsigned long long permutations(unsigned long long num, const int p[], int pmax, int n);
    void genEncKey();
    unsigned long long SBoxes(unsigned long long num);
    void encryption();
    void decryption();
    void showBinary(unsigned long long num);
    void showResult();

private:
    unsigned long long keyLeftShift(unsigned long long k, int n);
    unsigned long long key;
    unsigned long long plainText;
    unsigned long long ciperText;
    unsigned long long decipherText;
    unsigned long long encKey[16];
    static const int IP[64];
    static const int IPI[64];
    static const int keyIP[56];
    static const int encKeyRound[16];
    static const int CP[48];                      //compress permutation
    static const int EP[48];                      //extended permutation
    static const int SBox[32][16];
    static const int P[32];    
};

const int DES::IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 1, 8,
    57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 3, 23, 15, 7
};

DES::DES() {
    key = 0;
    plainText = 0;
    cipherText = 0;
    decipherText = 0;
}

void DES::setKey(string k) {
    unsigned long long c;
    for (int i = 0; i < 8; i++) {
        c = k[i];
        key = (c << (7 - i) * 8) | key;
    }
}

void DES::setPlainText(string p) {
    unsigned long long c;
    for (int i = 0; i < 8; i++) {
        c = p[i];
        plainText = (c << (7 - i) * 8) | plainText;
    }
}

void DES::genEncKey() {
    unsigned long long gkey;
    gkey = permutations(key, keyIP, 64, 56);
    for (int i = 0; i < 16; i++) {
        gkey = keyLeftShift(gkey, encKeyRound[i]);
        encKey[i] = permutations(gkey, CP, 56, 48);
    }
}

unsigned long long DES::keyLeftShift(unsigned long long k , int n) {
    unsigned long long tempKey = 0;
    unsigned long long L, R;
    L = (k & 0xFFFFFFF0000000LL) >> 28;
    R = k & 0x0000000FFFFFFFLL;
    switch (n) {
        case 0: 
            tempKey = k;
            break;        
        case 1: 
            L = ((L & 0x7FFFFFF) << 1) | ((L >> 27) & 1);
            R = ((R & 0x7FFFFFF) << 1) | ((R >> 27) & 1);
            tempKey = (L << 28) | R;
            break;
        case 2:
            L = ((L & 0x3FFFFFF) << 2) | ((L >> 26) & 3);
            R = ((R & 0x3FFFFFF) << 2) | ((R >> 26) & 3);
            tempKey = (L << 28) | R;
            break;
        default:
            break;
    }
    return tempKey;
}

unsigned long long DES::permutations(unsigned long long num, const int p[], int pmax, int n) {
    unsigned long long temp = 0;
    for (int i = 0; i < n; i++) {
        temp <<= 1;
        temp |= (num >> (pmax - p[i])) & 1;
    }
    return temp;
}

void DES::encryption() {
    unsigned long long temp = permutations(plainText, IP, 64, 64);
    unsigned long long L, R, tempR;
    L = (temp & 0xFFFFFFFF00000000LL) >> 32;
    R = (temp & 0x00000000FFFFFFFFLL);
    tempR = R;
    for (int i = 0; i < 16; i++) {
        tempR = permutations(R, EP, 32, 48);
        tempR = tempR ^ encKey[i];
        tempR = SBoxes(tempR);
        tempR = permutations(tempR, P, 32, 32);
        tempR = tempr ^ L;
        L = R;
        R = tempR;
    }
    temp = (R << 32) | L;
    temp = permutations(temp, IPI, 64, 64);
    decipherText = temp;
}

void DES::showBinary(unsigned long long  num) {
    vector<int> v;
    do {
        v.push_back(num % 2);
        num = (num - num % 2) / 2;
    } while(num != 0);
    for (int i = (v.size() - 1); i >=0; i--) {
        cout << v[i];
    }
    cout << endl;
}

void DES::showResult() {
    int i;
    cout << "key = ";
    for (i = 0; i < 8; i++) {
        cout << (char)((key >> (7 - i) * 8) & 0xFF);
    }
    cout << endl;
    cout << "plainText = ";
    for (i = 0; i < 8; i++) {
        cout << (char)((plainText >> (7 - i) * 8) & 0xFF);
    }
    cout << endl;
    cout << "cipherText = ";
    for (i = 0; i < 8; i++) {
        cout << (char) ((cipherText >> (7 - i) * 8) & 0xFF);
    }
    cout << endl;
    cout << "decipherText = ";
    for (i = 0; i < 8; i++) {
        cout << (char) ((decipherText >> (7 - i) * 8) & 0xFF);
    }
    cout << endl;
}
