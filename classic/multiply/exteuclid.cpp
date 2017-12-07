#include <iostream>
using namespace std;
// extent euclid algorithm
struct exteuc {
    int d;
    int s;
    int t;
};

exteuc exteuclid(int a, int b);

int main() {
    exteuc ext;
    int a, b;
    cout << "Please input two integers:";
    cin >> a >> b;
    ext = exteuclid(a, b);
    cout << "d = " << ext.d << " " << "s = " << ext.s << " "<< "t = "<< ext.t <<endl;
    return 0;
}

exteuc exteuclid(int a, int b) {
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
