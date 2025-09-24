#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;
void insort(vector<int> s){
    int aux;
    int size = (int)s.size();
    int steps = 0;
    for (int i = 1; i < (int)s.size(); i++) {
        aux = s[i];
        int j = i - 1;
        
        while (s[j] > s[j + 1] && j >= 0){
            steps ++;
            s[j + 1] = s[ j ];
            s[j] = aux;
            j--;
        }
    }
    cout<<"Orden Insort"<<endl;
    cout<<"Tamaño de datos: "<<size<<endl;
    cout<<"Iteraciones: " <<steps<<endl;
}
void selectSort(vector<int>& array){
    int size = (int)array.size();
    int steps = 0;
    for(int i = 0; i < size - 1 ; i++){
        int min = i;
        for(int j = i + 1; j < size; j++){
            steps ++;
            if(array[j] < array[min]){
                min = j;
            }
        }
        swap(array[i], array[min]);
    }
    cout<<"Orden Select"<<endl;
    cout<<"Tamaño de datos: "<<size<<endl;
    cout<<"Iteraciones: " <<steps<<endl;
}
void choose( vector<int>& nums1,vector<int>& nums2,vector<int>& nums3){
    int opcion;
    cout << "Elige opcion: \n";
    cout << "1. insert sort\n";
    cout << "2. select sort\n";
    cin >> opcion;

2    switch (opcion) {
        case 1:
            cout<<(int)nums1.size()<<" datos:";
            insort(nums1);
            cout<<endl;
            cout<<(int)nums2.size()<<" datos:";
            insort(nums2);
            cout<<endl;
            cout<<(int)nums3.size()<<" datos:";
            insort(nums3);
            cout<<endl;
            break;
        case 2:
            cout<<(int)nums1.size()<<" datos:";
            selectSort(nums1);
            cout<<endl;
            cout<<(int)nums2.size()<<" datos:";
            selectSort(nums2);
            cout<<endl;
            cout<<(int)nums3.size()<<" datos:";
            selectSort(nums3);
            cout<<endl;
            break;
        default:
            cout << "Opcion invalida\n";
    }
    return;
}

int main() {
    vector<int> nums1(1000);
    vector<int> nums2(5000);
    vector<int> nums3(10000);
    for(int i = 0; i < (int)nums1.size(); i++){
        nums1[i] = (int)(rand() % 1000);
    }
    for(int i = 0; i < (int)nums2.size(); i++){
        nums2[i] = (int)(rand() % 5000);
    }
    for(int i = 0; i < (int)nums3.size(); i++){
        nums3[i] = (int)(rand() % 10000);;
    }
    choose(nums1,nums2,nums3);
    return 0;
}

