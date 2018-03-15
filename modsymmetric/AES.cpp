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
