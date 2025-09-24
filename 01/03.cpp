#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> bubbleSortNames(vector<string> names){
    int n = names.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (names[j] > names[j + 1]) {  
                string temp = names[j];
                names[j] = names[j + 1];
                names[j + 1] = temp;
            }
        }
    }
    return names;
}
int main() {
    vector<string> names1 = {"juan","carlos","diego","fulano","pedro","paco","kevin","cielo","cielo","cielo","cielo"};
    vector<string> names2 = {"juan","carlos","diego","fulano","pedro","paco","kevin","cielo","cielo","cielo","cielo"};
    names1 = bubbleSortNames(names1);
    cout<<"***Metodo Burbuja***"<<endl;
    for(string s: names1){
        cout<<s<<" - ";
    }

    sort(names2.begin(), names2.end());
    
    cout<<"\n***Metodo sort de c++***"<<endl;
    for(string s: names2){
        cout<<s<<" - ";
    }
    return 0;
}
