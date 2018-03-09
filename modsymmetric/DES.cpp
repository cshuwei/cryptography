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
    unsigned long long cipherText;
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
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};
const int DES::IPI[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};
const int DES::keyIP[56] = {
    57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18, 
    10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23 ,15,  7, 62, 54, 46 ,38 ,30, 22,
    14,  6, 61, 53 ,45, 37, 29, 21, 13,  5, 28, 20, 12 , 4
};
const int DES::encKeyRound[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
const int DES::CP[48] = {
    14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
}; 
const int DES::EP[48] = {
    32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1   
};
const int DES::SBox[32][16] = {
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,    //S1
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,    //S2
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,    //S3
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,    //S4
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,    //S5
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15 ,10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,    //S6  
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,    //S7
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,    //S8
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
};

const int DES::P[32] = {
    16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11, 4, 25
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
        tempR = tempR ^ L;
        L = R;
        R = tempR;
    }
    temp = (R << 32) | L;
    temp = permutations(temp, IPI, 64, 64);
    cipherText = temp;
}

unsigned long long DES::SBoxes(unsigned long long num) {
    int i;
    unsigned long long temp;
    unsigned long long result = 0;
    for (i = 0; i < 8; i++) {
        temp = (num >> ((7 - i) * 6)) & 0x3F;
        int x = ((temp >> 4) & 0x2) | (temp & 0x1) + i * 4;
        int y = (temp >> 1) & 0xF;
        temp = SBox[x][y];
        temp = temp << ((7 - i) * 4);
        result = result | temp;
    }
    return result;
}

void DES::decryption() {
    unsigned long long temp = permutations(cipherText, IP, 64, 64);
    int i, j;
    unsigned long long L, R, tempR;
    L = (temp & 0xFFFFFFFF00000000LL) >> 32;
    R = (temp & 0x00000000FFFFFFFFLL);
    tempR = R;
    for (i = 0; i < 16; i++) {
        tempR = permutations(R, EP, 32, 48);
        tempR = tempR ^ encKey[15 - i];
        tempR = SBoxes(tempR);
        tempR = permutations(tempR, P, 32, 32);
        tempR = tempR ^ L;
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

int main() {
    DES des;
    des.setKey("!2bcde<~");
    des.setPlainText("ABs5EFGH");
    des.genEncKey();
    des.encryption();
    des.decryption();
    des.showResult();
    return 0;
}
