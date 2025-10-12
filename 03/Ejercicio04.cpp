#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;
using namespace chrono;

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace chrono;

void merge(vector<int>& arr, int l, int m, int r, int& comparaciones) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        comparaciones++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    } 
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vector<int>& arr, int l, int r, int& comparaciones) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comparaciones);
        mergeSort(arr, m + 1, r, comparaciones);
        merge(arr, l, m, r, comparaciones);
    }
}
int partition(vector<int>& arr, int low, int high, int& comparaciones) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        comparaciones++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(vector<int>& arr, int low, int high, int& comparaciones) {
    if (low < high) {
        int pi = partition(arr, low, high, comparaciones);
        quickSort(arr, low, pi - 1, comparaciones);
        quickSort(arr, pi + 1, high, comparaciones);
    }
}
int busquedaBinaria(const vector<int>& arr, int elemento, int& comparaciones) {
    int izq = 0;
    int der = arr.size() - 1;
    
    while (izq <= der) {
        comparaciones++;
        int medio = izq + (der - izq) / 2;
        if (arr[medio] == elemento) {
            return medio;
        }
        comparaciones++;
        if (arr[medio] < elemento) {
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }
    
    return -1;
}
int busquedaSecuencial(const vector<int>& arr, int elemento, int& comparaciones) {
    for (int i = 0; i < arr.size(); i++) {
        comparaciones++;
        if (arr[i] == elemento) {
            return i;
        }
    }
    return -1;
}
vector<int> generarAleatorios(int n, int min = 1, int max = 10000) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}
void mostrarArreglo(const vector<int>& arr, int max_elementos = 20) {
    int n = arr.size();
    if (n <= max_elementos) {
        for (int i = 0; i < n; i++) {
            cout << arr[i];
            if (i < n - 1) cout << ", ";
        }
        cout << endl;
    } else {
        for (int i = 0; i < max_elementos / 2; i++) {
            cout << arr[i] << ", ";
        }
        cout << "... ";
        for (int i = n - max_elementos / 2; i < n; i++) {
            cout << arr[i];
            if (i < n - 1) cout << ", ";
        }
        cout << endl;
    }
}

int main() {
    int n, algoritmo, elementoBuscado;
    
    cout << "========================================\n";
    cout << "  ORDENAMIENTO Y BÚSQUEDA CON ANÁLISIS\n";
    cout << "========================================\n\n";
    
    cout << "Ingrese el número de elementos (n): ";
    cin >> n;
    
    vector<int> arr = generarAleatorios(n);
    
    cout << "\nArreglo original generado (" << n << " elementos):\n";
    mostrarArreglo(arr);
    

    cout << "\nSeleccione algoritmo de ordenamiento:\n";
    cout << "1. Merge Sort\n";
    cout << "2. Quick Sort\n";
    cout << "Opción: ";
    cin >> algoritmo;
    
    int comparacionesOrdenamiento = 0;
    auto inicio = high_resolution_clock::now();
    
    vector<int> arrOrdenado = arr;
    
    if (algoritmo == 1) {
        cout << "\nOrdenando con MERGE SORT...\n";
        mergeSort(arrOrdenado, 0, arrOrdenado.size() - 1, comparacionesOrdenamiento);
    } else {
        cout << "\nOrdenando con QUICK SORT...\n";
        quickSort(arrOrdenado, 0, arrOrdenado.size() - 1, comparacionesOrdenamiento);
    }
    
    auto fin = high_resolution_clock::now();
    duration<double, milli> tiempoOrdenamiento = fin - inicio;
    
    cout << "\nArreglo ordenado:\n";
    mostrarArreglo(arrOrdenado);
    
    cout << "\nIngrese el elemento a buscar: ";
    cin >> elementoBuscado;
    
    cout << "\n========================================\n";
    cout << "  BÚSQUEDA BINARIA\n";
    cout << "========================================\n";
    
    int comparacionesBinaria = 0;
    inicio = high_resolution_clock::now();
    int posBinaria = busquedaBinaria(arrOrdenado, elementoBuscado, comparacionesBinaria);
    fin = high_resolution_clock::now();
    duration<double, micro> tiempoBinaria = fin - inicio;
    
    if (posBinaria != -1) {
        cout << "Elemento " << elementoBuscado << " encontrado en posición: " << posBinaria << endl;
    } else {
        cout << "Elemento " << elementoBuscado << " NO encontrado" << endl;
    }
    
    cout << "\n========================================\n";
    cout << "  BÚSQUEDA SECUENCIAL (sin ordenar)\n";
    cout << "========================================\n";
    
    int comparacionesSecuencial = 0;
    inicio = high_resolution_clock::now();
    int posSecuencial = busquedaSecuencial(arr, elementoBuscado, comparacionesSecuencial);
    fin = high_resolution_clock::now();
    duration<double, micro> tiempoSecuencial = fin - inicio;
    
    if (posSecuencial != -1) {
        cout << "Elemento " << elementoBuscado << " encontrado en posición: " << posSecuencial << endl;
    } else {
        cout << "Elemento " << elementoBuscado << " NO encontrado" << endl;
    }
    
    cout << "\n========================================\n";
    cout << "  ANÁLISIS DE COMPLEJIDAD TEMPORAL\n";
    cout << "========================================\n\n";
    
    string nombreAlgoritmo = (algoritmo == 1) ? "Merge Sort" : "Quick Sort";
    double complejidadTeoricaOrden = n * log2(n);
    int complejidadTeoricaBinaria = log2(n);
    
    cout << fixed << setprecision(4);
    cout << "ORDENAMIENTO (" << nombreAlgoritmo << "):\n";
    cout << "  Tiempo real:            " << tiempoOrdenamiento.count() << " ms\n";
    cout << "  Comparaciones:          " << comparacionesOrdenamiento << endl;
    cout << "  Complejidad teórica:    O(n log n) ≈ " << complejidadTeoricaOrden << endl;
    cout << endl;
    
    cout << "BÚSQUEDA BINARIA (con ordenamiento previo):\n";
    cout << "  Tiempo búsqueda:        " << tiempoBinaria.count() << " μs\n";
    cout << "  Comparaciones búsqueda: " << comparacionesBinaria << endl;
    cout << "  Complejidad teórica:    O(log n) ≈ " << complejidadTeoricaBinaria << endl;
    cout << "  ---\n";
    cout << "  TOTAL comparaciones:    " << (comparacionesOrdenamiento + comparacionesBinaria) << endl;
    cout << "  TOTAL tiempo:           " << tiempoOrdenamiento.count() << " ms + " << tiempoBinaria.count() << " μs\n";
    cout << endl;
    
    cout << "BÚSQUEDA SECUENCIAL (sin ordenamiento):\n";
    cout << "  Tiempo búsqueda:        " << tiempoSecuencial.count() << " μs\n";
    cout << "  Comparaciones:          " << comparacionesSecuencial << endl;
    cout << "  Complejidad teórica:    O(n) = " << n << " (peor caso)\n";
    cout << endl;
    
    cout << "========================================\n";
    cout << "  COMPARACIÓN FINAL\n";
    cout << "========================================\n";
    
    int diferenciaComparaciones = (comparacionesOrdenamiento + comparacionesBinaria) - comparacionesSecuencial;
    
    cout << "\nOrdenamiento + Búsqueda Binaria vs Búsqueda Secuencial:\n";
    cout << "  Diferencia en comparaciones: " << diferenciaComparaciones;
    
    if (diferenciaComparaciones > 0) {
        cout << " (más comparaciones con ordenamiento)\n";
        cout << "\n  CONCLUSIÓN: Para UNA sola búsqueda, la búsqueda secuencial\n";
        cout << "  es más eficiente. Sin embargo, si se realizan MÚLTIPLES\n";
        cout << "  búsquedas, el costo del ordenamiento se amortiza.\n";
    } else {
        cout << " (menos comparaciones con ordenamiento)\n";
        cout << "\n  CONCLUSIÓN: El ordenamiento + búsqueda binaria fue más eficiente.\n";
    }
    
    int busquedasParaAmortizar = ceil((double)comparacionesOrdenamiento / (comparacionesSecuencial - comparacionesBinaria));
    cout << "\n  Número de búsquedas necesarias para amortizar el\n";
    cout << "  costo del ordenamiento: aproximadamente " << busquedasParaAmortizar << " búsquedas.\n";
    
    cout << "\n========================================\n";
    
    return 0;
}

    int n2 = r - m;
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[i], arr[min_idx]);
    }
}
vector<int> generarAleatorios(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}
double medirTiempoMerge(vector<int> arr) {
    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1);
    auto end = high_resolution_clock::now();
    duration<double, milli> tiempo = end - start;
    return tiempo.count();
}
double medirTiempoQuick(vector<int> arr) {
    auto start = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto end = high_resolution_clock::now();
    duration<double, milli> tiempo = end - start;
    return tiempo.count();
}
double medirTiempoInsertion(vector<int> arr) {
    auto start = high_resolution_clock::now();
    insertionSort(arr);
    auto end = high_resolution_clock::now();
    duration<double, milli> tiempo = end - start;
    return tiempo.count();
}
double medirTiempoSelection(vector<int> arr) {
    auto start = high_resolution_clock::now();
    selectionSort(arr);
    auto end = high_resolution_clock::now();
    duration<double, milli> tiempo = end - start;
    return tiempo.count();
}

int main() {
    const int N = 10000;
    
    cout << "Número de elementos: " << N << "\n";
    vector<int> arrOriginal = generarAleatorios(N);
    vector<int> arr1 = arrOriginal;
    double tiempoMerge = medirTiempoMerge(arr1);
    vector<int> arr2 = arrOriginal;
    double tiempoQuick = medirTiempoQuick(arr2);
    vector<int> arr3 = arrOriginal;
    double tiempoInsertion = medirTiempoInsertion(arr3);
    vector<int> arr4 = arrOriginal;
    double tiempoSelection = medirTiempoSelection(arr4);
    cout << fixed << setprecision(2);
    cout << "RESULTADOS:\n";
    cout << "1. Merge Sort:      " << setw(10) << tiempoMerge << " ms\n";
    cout << "2. Quick Sort:      " << setw(10) << tiempoQuick << " ms\n";
    cout << "3. Insertion Sort:  " << setw(10) << tiempoInsertion << " ms\n";
    cout << "4. Selection Sort:  " << setw(10) << tiempoSelection << " ms\n";

    return 0;
}
