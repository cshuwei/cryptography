#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class Shift {
public:
    Shift(int k):n(k) {}
    void encryption(ifstream& fin, ofstream& fout);
    void decryption(ifstream& fin, ofstream& fout);
private:
    int n;
};

void Shift::encryption(ifstream& fin, ofstream& fout) {
    char next;
    while (fin.get(next)) {
        fout << char((int(next) + n) % 128);
    }
}

void Shift::decryption(ifstream& fin, ofstream& fout) {
    char next;
    while (fin.get(next)) {
        fout << char((int(next) - n) % 128);
    }    
}


int main() {
    ifstream fin;
    ofstream fout;
    fin.open("file.in");
    if (fin.fail()) {
        cout << "File open error!" << endl;
        exit(1);
    }
    fout.open("file.out");
    if (fout.fail()) {
        cout << "File open error!" << endl;
        exit(1);
    }
    Shift shift(2);
    shift.encryption(fin, fout);
    fin.close();
    fout.close();
    
    fin.open("file.out");
    if (fin.fail()) {
        cout << "File open error!" << endl;
        exit(1);
    }
    fout.open("file.out2");
    if (fout.fail()) {
        cout << "File open error!" << endl;
        exit(1);
    }

    shift.decryption(fin, fout);
    fin.close();
    fout.close();
    return 0;
}
