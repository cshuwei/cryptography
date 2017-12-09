#include <iostream>
#include <string>
#include "hill.h"
using namespace std;

Hill::Hill() {
    init();
    getdeckey();
}
void Hill::init() {
    int i, j;
    while (1) {
        cout << "Input the key: " << endl;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                cin >> key[i][j];
            }
        }
        det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
        if ((0 == det) | (gcd(det, 26) != 1)) {
            cout << "The key can't be inversed, reinput the key!" << endl;
            continue;
        } else {
            getdeckey();
            cout << "Input the plaintext:" << endl;
            cin >> plaintext;
            break;
        }
    }
}

void Hill::getdeckey() {
    exteuc ext;
    int inversedet, i, j;
    ext = exteuclid(det, 26);
    inversedet = ext.s;

    deckey[0][0] = key[1][1];
    deckey[0][1] = -key[0][1];
    deckey[1][0] = -key[1][0];
    deckey[1][1] = key[0][0];

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            deckey[i][j] = (deckey[i][j] * inversedet) % 26;
            if (deckey[i][j] < 0) {
                deckey[i][j] += 26;
            }
        }
    }
}


void Hill::cutplaintext() {
    int i;
    if (plaintext.length() % 2 == 1) {
        plaintext += "z";
    }
    
    for (i = 0; i < plaintext.length(); i++) {
        vintext.push_back(plaintext[i]);
    }
}


void Hill::encryption() {
    cutplaintext();
    int ciphtext[2] = {0, 0};
    int plaitext[2] = {0, 0};    
    int i, j, k;
    for (i = 0; i < vintext.size(); i += 2) {
        plaitext[i % 2] = int(vintext[i] - 'a');
        plaitext[(i + 1) % 2] = int(vintext[i + 1] - 'a');
        
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                ciphtext[j] += key[j][k] * plaitext[k];
            }
        }
        
        for (j = 0; j < 2; j++) {
            ciphtext[j] = ciphtext[j] % 26;
            ciphertext.push_back(char(ciphtext[j] + int('a')));
            ciphtext[j] = 0;
        }
    }
}

void Hill::decryption() {
    int ciphtext[2] = {0, 0};
    int plaitext[2] = {0, 0};
    int i, j, k;
    for (i = 0; i < ciphertext.size(); i += 2) {
        ciphtext[i % 2] = int(ciphertext[i] - 'a');
        ciphtext[(i + 1) % 2] = int(ciphertext[i + 1] - 'a');
 
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                plaitext[j] += deckey[j][k] * ciphtext[k];
            }
        }
        
        for (j = 0; j < 2; j++) {
            plaitext[j] = plaitext[j] % 26;
            dectext.push_back(char(plaitext[j] + int('a')));
            plaitext[j] = 0;
        }
    }
}

exteuc Hill::exteuclid(int a, int b) {
    exteuc ext1, ext2;
    if (0 == b) {
        ext2.d = a;
        ext2.s = 1;
        ext2.t = 0;
        return ext2;
    }
    
    ext2 = exteuclid(b, a % b);
    ext1.d = ext2.d;
    ext1.s = ext2.t;
    ext1.t = ext2.s - (a / b) * ext2.t;
    return ext1;
}

void Hill::showresult() {
    int i;
    cout << "plaintext: " << plaintext << endl;
    cout << "ciphertext: ";
    for (i = 0; i < ciphertext.size(); i++) {
        cout << ciphertext[i];
    }
    cout << endl;

    cout << "dectext: ";
    for (i = 0; i < dectext.size(); i++) {
        cout << dectext[i];
    }
    cout << endl;
}

int Hill::gcd(int n, int k) {
    if (0 == n) 
        return k;
    if (0 == k)
        return n;
    return gcd(k, n % k);
}
