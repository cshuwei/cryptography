#include <iostream>

using namespace std;

typedef unsigned char byte;
struct word {
    byte wordKey[4];
};

class AES {
    public:
        AES();
        void setCipherKey(byte key[]);
        void setPlainText(byte plain[]);
        void keyExpansion(byte key[], word w[]);
        word rotWord(word w);
        word subWord(word w);
        word wordXor(word w1, word w2);
        void encryption(word in[], word out[], word key[]);
        void processEncryption();
        void addRoundKey(word in[], int round);
        void subByte(word in[]);
        void shiftRows(word in[]);
        void mixColumn(word in[]);
        byte GFMultiplyByte(byte L, byte R);
        void decryption(word in[], word out[], word key[]);
        void processDecryption();
        void invShiftRows(word in[]);
        void invSubByte(word in[]);
        void invMixColumn(word in[]);
        void initRcon();

    private:
        byte cipherKey[16];
        word plainText[4];
        word cipherText[4];
        word decipherText[4];
        int Nb, Nk, Nr;
        word Rcon[11];
        word wordKey[44];
        static const byte SBox[16][16];
        static const byte invSBox[16][16];
        static const byte mixColumnMatrix[4][4];
        static const byte invMixColumnMatrix[4][4];
};

const byte AES::mixColumnMatrix[4][4] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
};

const byte AES::invMixColumnMatrix[4][4] = {
    {0x0e, 0x0b, 0x0d, 0x09},
    {0x09, 0x0e, 0x0b, 0x0d},
    {0x0d, 0x09, 0x0e, 0x0b},
    {0x0b, 0x0d, 0x09, 0x0e}
};

const byte AES::SBox[16][16] = {

};
};
void AES::setPlainText(byte plain[]) {
    int i;
    for (i = 0; i < 16; i++) {
        plainText[i % 4].wordKey[i / 4] = plain[i];
    }
}


void AES::setCipherKey(byte key[]) {
    int i;
    for (i = 0; i < 16; i++) {
        cipherKey[i] = key[i];
    }
    
    keyExpansion(cipherKey, wordkey);
}

void AES::initRcon() {
    int i, j;
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 4; j++) {
            Rcon[i].wordKey[j] = 0x0;
        }
    }

    for (i = 1; i < 9; i++) {
        Rcon[i].wordKey[0] = 1 << i;
    }
    
    Rcon[9].wordKey[0] = 0x1b;
    Rcon[10].wordKey[0] = 0x36;
}

void AES::keyExpansion(byte key[], word w[]) {
    int i = 0, j, k;
    word temp;
    while (i < Nk) {
        for (j = 0; j < 4; j++) {
            w[i].wordKey[j] = key[j + 4 * i];
        }
        i++;
    }
    i = Nk;
    while (i < Nb * (Nr + 1)) {
        temp = w[i - 1];
        if ((i % Nk) == 0) {
            temp = rotWord(temp);
            temp = subWord(temp);
            temp = wordXOR(temp, Rcon[i / Nk]);
        } else if (Nk > 6 && (i % Nk) == 4) {
            temp = subWord(temp);
        }
        w[i] = wordXOR(w[i - Nk], temp);
        i++;
    }

    word tempState[44];
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 4; j+) {
            for (k = 0; k < 4; k++) {
                tempState[j + i * 4].wordKey[k] = w[k + i * 4].wordKey[j];
            }
        }
    }
    for (i = 0; i < 44; i++) {
        for (j = 0; j < 4;j++) {
            w[i].wordKey[j] = tempState[i].wordKey[j];
        }
    }
}

word AES::rotWord(word w) {
    int i;
    word temp;
    for (i = 0; i < 4; i++) {
        temp.wordKey[(i + 3) % 4] = w.wordKey[i];
    }
    return temp;
}

word AES::subWord(word w) {
    int i;
    byte L, R;
    for (i = 0; i < 4; i++) {
        L = w.wordKey[i] >> 4;
        R = w.wordKey[i] & 0x0F;
        w.wordKey[i] = SBox[L][R];
    }
    return w;
}

word AES::wordXOR(word w1, word w2) {
    int i;
    word temp;
    for (i = 0; i < 4; i++) {
        temp.wordKey[i] = w1.wordKey[i] ^ w2.wordKey[i];
    }
    return temp;
}

void AES::encryption(word in[], word out[], word key[]) {
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            out[i].wordKey[j] = in[i].wordKey[j];
        }
    }
    addRoundKey(out, 0);
    for (i = 1; i < 10; 1++) {
        subByte(out);
        shiftRows(out);
        mixColumn(out);
        addRoundKey(out, i);
    }
    subByte(out);
    shiftRows(out);
    addRoundKey(out, 10);
}


void AES::subByte(word in[]) {
    int i, j;
    byte L, R;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            L = in[i].wordKey[j] >> 4;
            R = in[i].wordKey[j] & 0x0F;
            in[i].wordKey[j] = SBox[L][R];
        }
    }
}


void AES::shiftRows(word in[]) {
    int i, j;
    word temp[4];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            temp[i].wordKey[(j + (4 - i)) % 4] = in[i].wordKey[j];
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            in[i].wordKey[j] = temp[i].wordKey[j];
        }
    }
}

void AES::mixColumn(word in[]) {
    word result[4];
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            result[i].wordKey[j] = GFMultiplyByte(mixColumnMatrix[i][0], in[0].wordKey[j]);
            for (k = 1; k < 4; k++) {
                result[i].wordKey[j] ^= GFMultiplyByte(mixColumnMatrix[i][k],in[k].wordKey[j]);
            }
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            in[i].wordKey[j] = result[i].wordKey[j];
        }
    }
}

byte AES::GFMultiplyByte(byte L, byte R) {
    byte temp[8];
    byte result = 0x00;
    temp[0] = L;
    int i;
    for (i = 1; i < 8; i++) {
        if (temp[i - 1] >= 0x80) {
            temp[i] = (temp[i - 1] << 1) ^ 0x1b;
        } else {
            temp[i] = temp[i - 1] << 1;
        }
    }

    for (i = 0; i < 8; i++) {
        if (int((R >> i) & 0x01) == 1) {
            result ^= temp[i];
        }   
    }
    return result;
}

void AES::addRoundKey(word in[], int round) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            in[i].wordKey[j] ^= wordKey[i + 4 * round].wordKey[j];
        }
    }
}

void AES::decryption(word in[], word out[], word key[]) {
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            out[i].wordKey[j] = in[i].wordKey[j];
        }
    }

    addRoundKey(out, 10);
    for (i = 9; i > 0; i--) {
        invShiftRows(out);
        invSubByte(out);
        addRoundKey(out, i);
        invMixColumn(out);
    }
    invShiftRows(out);
    invSubByte(out);
    addRoundKey(out, 0);
}

void AES::invShiftRows(word in[]) {
    int i, j;
    word temp[4];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            temp[i].wordKey[(j + i) % 4] = in[i].wordKey[j];
        }   
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            in[i].wordKey[j] = temp[i].wordKey[j];
        }
    }
}

void AES::invSubByte(word in[]) {
    int i, j;
    byte L, R;
    for (i = 0; i < 4; i++) {
        for ( j = 0; j < 4; j++) {
            L = in[i].wordKey[j] >> 4;
            R = in[i].wordKey[j] & 0x0F;
            in[i].wordKey[j] = invSBox[L][R];
        }
    }
}

void AES::invMixColumn(word in[]) {
    word result[4];
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            result[i].wordKey[j] = GFMultiplyByte(invMixColumnMatrix[i][0], in[0].wordKey[j]);
            GFMultiplyByte(invMixColumnMatrix[i][k], in[k].wordKey[j]);
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            in[i].wordKey[j] = result[i].wordKey[j];
        }
    }
}
