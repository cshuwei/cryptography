#ifndef __HILL_H
#define __HILL_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct exteuc {
    int d;
    int s;
    int t;
};

class Hill {
private:
    int key[2][2];
    int deckey[2][2];
    int det;
    string plaintext;
    vector<char> ciphertext;
    vector<char> vintext;
    vector<char> dectext;
public:
    Hill();
    void init();
    void cutplaintext();
    void getdeckey();
    void encryption();
    void decryption();
    void showresult();
    int gcd(int n, int k);
    exteuc exteuclid(int a, int b);
};

#endif
