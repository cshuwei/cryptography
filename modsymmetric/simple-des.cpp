#include <iostream>
#include <string>
using namespace std;

class SDES {
public:
    SDES();
    void setKey(string s);
    void setPlainText(string s);
    void fk(int key, int& left, int right);
    void getKey();
    void encryption();
    void decryption();
    int permutations(int num, const int p[], int pmax, int n);
    int shiftLS(int num);
    void showResult();
private:
    int key, key1, key2;
    int plainText;
    int cipherText;
    int deciperText;
    int stringToInt(string s);
    static const int P10[10];
    static const int P8[8];
    static const int IP[8];
    static const int IPI[8];
    static const int EP1[4];
    static const int EP2[4];
    static const int P4[4];
    static const int S0[4][4];
    static const int S1[4][4];
};

const int SDES::P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
const int SDES::P8[8] = {6, 3, 7, 4, 8, 5, 10, 9};
const int SDES::IP[8] = {2, 6, 3, 1, 4, 8, 5, 7};
const int SDES::IPI[8] = {4, 1, 3, 5, 7, 2, 8, 6};
const int SDES::EP1[4] = {4, 1, 2, 3};
const int SDES::EP2[4] = {2, 3, 4, 1};
const int SDES::P4[4] = {2, 4, 3, 1};
const int SDES::S0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
const int SDES::S1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};

void SDES::setKey(string s) {
    key = stringToInt(s);
}

int SDES::stringToInt(s) {
    int key = 0;
    for (i = 0; i < s.length(); i++) {
        key = key * 2 + s[i] - '0';
    }
    return key;
}

void SDES::getKey() {
    int tempKey;
    tempKey = permutations(key, P10, 10, 10);
    tempKey = shiftLS(tempKey);
    key1 = permutations(tempKey, P8, 10, 8);
    tempKey = shiftLS(shiftLS(tempKey));
    key2 = permutations(tempKey, P8, 10, 8);
}

