#include <iostream>
#include "vigenere.h"
using namespace std;


int main() {
    Vigenere vigenere;
    vigenere.setkey();
    vigenere.setplaintext();
    vigenere.encryption();
    vigenere.decryption();
    vigenere.output();
}
