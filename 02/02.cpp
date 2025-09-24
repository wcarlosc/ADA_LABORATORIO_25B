#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void selectSort(vector<float>& array){
    int steps = 0;
    int comp = 0;
    int size = (int)array.size();
    for(int i = 0; i < size - 1 ; i++){
        int min = i;
        for(int j = i + 1; j < size; j++){
            steps ++;
            if(array[j] < array[min]){
                min = j;
                comp ++;
            }
        }
        swap(array[i], array[min]);
    }
    cout<<"cantidad de datos: "<<size<<endl;
    cout<<"iteaciones: "<<steps<<endl;
    cout<<"comparaciones: "<<comp<<endl;
}

int main() {
    vector<float> nums= {3.2,4.2,5.6,1.7,2.1,58.7,1.2,24.1,0.2};
    selectSort(nums);
    for(float a: nums) cout <<a<<"  ";
    cout<<endl;
    return 0;

}
