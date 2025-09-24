#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string n){
    int i = 0,j = n.size()-1;
    bool r = true;
    while (i < j){
        if(n[i] == n[j]){
            i++;
            j--;
        }else{
            return false;
        }
    }
    return r;
}

int main() {
    int n;
    cin >> n;
    if (isPalindrome(to_string(n))){
        cout<<"Es palindromo"<<endl;
    }else{
        cout<<"No es palindromo"<<endl;
    }

    system("pause");
    return 0;
}
