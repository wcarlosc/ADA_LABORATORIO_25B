#include <iostream>
using namespace std;

int loopAdd(int n){
    int addition;
    for(int i = 1; i <= n; i++){
        addition += i;
    }
    return addition;
}
int formulaAd(int n){
    return n*(n+1)/2;
}

int main() {
    int n;
    cin >> n;
    cout<<"Suma en ciclos: "<<loopAdd(n)<<endl;
    cout<<"Suma con formula: "<<formulaAd(n)<<endl;

    system("pause");
    return 0;
}
