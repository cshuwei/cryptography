#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const char c[27] = {'d','j','k','z','u','y','c','m','l','i','w','b','v',\
                   'n','o','p','q','a','r','s','h','g','f','t','x','e',' '};

void encryption(ifstream& fin, ofstream& fout);
void decryption(ifstream& fin, ofstream& fout);
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("file.in");
    if (fin.fail()) {
        cout << "File open error!(Input)" << endl;
        exit(1);
    }
    
    fout.open("file.out");
    if (fout.fail()) {
        cout << "File open error!(Output)" << endl;
    }
    
    encryption(fin, fout);
    fin.close();
    fout.close();
    
    fin.open("file.out");
    if (fin.fail()) {
        cout << "File open error!(Input)" << endl;
        exit(1);
    }
   
    fout.open("file.out2");
    if (fout.fail()) {
        cout << "File open error!(Output)" << endl;
    }
    
    decryption(fin, fout); 
    
    fin.close();
    fout.close();
    return 0;
}

void encryption(ifstream& fin, ofstream& fout) {
    char next, ch;
    int i;
    while (fin.get(next)) {
        if (next >= 'a' && next <= 'z') {
            i = next - 'a';
            ch = c[i];
            fout << ch;
        } else {
            fout << ' ';
        }
    }
}

void decryption(ifstream& fin, ofstream& fout) {
    char ch, chout;
    while (fin.get(ch)) {
        for (int i = 0; i <= 26; i++) {
            if (ch == c[i]) {
                if (26 == i) {
                    fout << ' ';
                } else {
                    chout = char('a' + i);
                    fout << chout;
                }
            }
        }
    }
}
