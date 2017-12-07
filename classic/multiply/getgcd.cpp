#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int gcd(int n, int k);
void get_gcd(int n);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "usage: ./a.out n" << endl;
        exit(1);
    }
    get_gcd(atoi(argv[1]));
    return 0;
}

void get_gcd(int n) {
    int i;
    vector<int> v;
    for (i = 1; i < n; i++) {
        if (1 == gcd(n, i)){
            v.push_back(i);
        }
    }
    
    for (i = 0; i < v.size();i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int gcd(int n, int k) {
    if (0 == n) 
        return k;
    if (0 == k)
        return n;
    return gcd(k, n % k);
}
