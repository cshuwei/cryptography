#include <iostream>
#include <fstream>
#include <cstdlib>
#include "vigenere.h"
using namespace std;

Vigenere::Vigenere() {
    init();
}

void Vigenere::init() {
    int i, j;
    for (i = 0; i < 26; i++) {
        for (j = 0; j < 26; j++) {
            cipher_table[i][j] = (i + j) % 26;
        }
    }
}

void Vigenere::setkey() {
    cout << "Please input the key:";
    cin >> key;
}

void Vigenere::setplaintext() {
    ifstream fin;
    char ch;
    int i;
    char pch[1024] = {0};
    fin.open("file.in");
    if (fin.fail()) {
        cout << "File open error!" << endl;
        exit(1);
    }
    while (fin.get(ch) && i < 1024) {
        pch[i++] = ch;
    }
    plaintext = (string)pch;
    fin.close();
}

void Vigenere::encryption() {
    ciphertext = plaintext;
    unsigned int i;
    int m, n;
    for (i = 0; i < plaintext.length(); i++) {
        m = int(plaintext[i] - 'a');
        n = int(key[i % (key.length())] - 'a');
        ciphertext[i] = char('A' + cipher_table[n][m]);
    }
}

void Vigenere::decryption() {
    plaintext2 = ciphertext;
    unsigned int i;
    int m, n;
    for (i = 0; i < ciphertext.length(); i++) {
        n = int(key[i % (key.length())] - 'a');
        m = getposition(i, n);
        plaintext2[i] = char('a' + m);
    }
}

int Vigenere::getposition(int p, int n) {
    int position;
    for (int i = 0; i < 26; i++) {
        if (char(ciphertext[p]) == char('A' + cipher_table[n][i])) {
            position = i;
            break;
        }
    }
    return position;
}

void Vigenere::output() {
    cout << "plaintext:" << plaintext << endl;
    cout << "ciphertext:" << ciphertext << endl;
    cout << "plaintext2:" << plaintext2 << endl;
}
