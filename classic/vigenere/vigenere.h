#ifndef  __VIGENERE_H
#define  __VIGENERE_H
#include <string>
using namespace std;

class Vigenere {
private:
    int cipher_table[26][26];
    string key;
    string plaintext;
    string ciphertext;
    string decodedtext;
public:
    Vigenere();
    void init();
    void setkey();
    void setplaintext();
    void encryption();
    void decryption();
    void output();
    int getposition(int p, int n);
};

#endif
