#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void insort(vector<string> s){
    string aux;
    cout<<"pasos:"<<endl;
    for (int i = 1; i < s.size(); i++) {
        aux = s[i];
        int j = i - 1;
        
        while (s[j] > s[j + 1] && j >= 0){
            s[j + 1] = s[ j ];
            s[j] = aux;
            j--;
            for(string x: s){
                cout<<x<<"-";
            }
            cout<<endl;
        }
    }
    cout<<endl;
    cout<<"****Orden Insort****"<<endl;
    for(string x: s){
        cout<<x<<"-";
    }
    cout<<endl;
}

int main() {
    cout <<"Cantidad:" ;
    int n;
    cin>>n; 
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cout<<"nombre "<<i+1<<":";
        cin>> s[i];
    }
    insort(s); 
    system("pause");
    return 0;

}
