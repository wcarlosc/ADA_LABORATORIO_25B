#include <iostream>
using namespace std;

int mcdStandard(int a, int b) {
    while (a != b) {
        if (a > b) a -= b;
        else b -= a;
    }
    return a;
}
int mcdEuclides(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
int main() {
    int a, b;
    cin >> a >> b;
    cout <<"MCD Ciclos:"<< mcdStandard(a, b) << endl;
    cout <<"MCD Euclides:"<< mcdEuclides(a, b) << endl;
    system("pause");
    return 0;
}
