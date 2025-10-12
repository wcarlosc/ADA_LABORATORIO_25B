#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

class Student {
public:
    string name;
    string code;
    float average;

    Student(string n, string c, float p):name(n),code(c),average(p) {}
    Student() : name(""), code(""), average(0.0f) {}
    Student(string n):name(n),
        code(to_string(10000000 + rand() % 90000000)),
        average(static_cast<float>(rand()) / RAND_MAX * 20.0f) {}

    string getName() const { return name;}
    string getCode() const { return code;}
    float getAverage() const { return average;}

};

template <typename T, typename Compare>
void merge(vector<T>& arr, int left, int mid, int right, Compare comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (comp(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

template <typename T, typename Compare>
void mergeSort(vector<T>& arr, int left, int right, Compare comp) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, comp);
    mergeSort(arr, mid + 1, right, comp);
    merge(arr, left, mid, right, comp);
}

int main(){
    vector<Student> students(10);
    vector<string> names = {"Alejandro","Camila","Mateo","Valeria","Sebastian","Lucia","Diego","Sofia","Gabriel","Mariana"};
    for (int i = 0; i < (int)names.size(); i++) {
        students[i] = Student(names[i]);
    }
    cout << "Original"<<endl;
    for (auto& s : students)
        cout <<"* "<< s.getName() << " - " << s.getCode() << " - " << s.getAverage() <<endl;
    
    cout << "Por nombre"<<endl;
    mergeSort(students, 0, students.size()-1,
              [](const Student& a, const Student& b) {
                  return a.getName() < b.getName();
              });
    for (auto& s : students)
        cout <<"* "<< s.getName() << " - " << s.getCode() << " - " << s.getAverage() <<endl;

    cout << "Por código"<<endl;
    mergeSort(students, 0, students.size()-1, [](const Student& a, const Student& b) {
        return a.getCode() < b.getCode();
    });
    for (auto& s : students)
        cout <<"* "<< s.getName() << " - " << s.getCode() << " - " << s.getAverage() <<endl;

    cout << "Por promedio "<<endl;
    mergeSort(students, 0, students.size()-1, [](const Student& a, const Student& b) {
        return a.getAverage() < b.getAverage();
    });

    for (auto& s : students)
        cout <<"* "<< s.getName() << " - " << s.getCode() << " - " << s.getAverage() << "\n";
}
