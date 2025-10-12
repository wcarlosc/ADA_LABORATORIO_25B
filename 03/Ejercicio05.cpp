#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
struct Producto {
    string codigo;
    string nombre;
    double precio;
    
    void mostrar() const {
        cout << left << setw(15) << codigo 
             << setw(30) << nombre 
             << right << setw(10) << fixed << setprecision(2) << precio << endl;
    }
};
void merge(vector<Producto>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<Producto> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].precio >= R[j].precio) {
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
void mergeSort(vector<Producto>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
int partition(vector<Producto>& arr, int low, int high) {
    double pivot = arr[high].precio;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].precio > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<Producto>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
vector<Producto> leerArchivo(const string& nombreArchivo) {
    vector<Producto> productos;
    ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'" << endl;
        return productos;
    }
    
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        Producto p;
        getline(ss, p.codigo, ',');
        getline(ss, p.nombre, ',');
        ss >> p.precio;
        
        productos.push_back(p);
    }
    archivo.close();
    return productos;
}
void mostrarProductos(const vector<Producto>& productos, const string& titulo) {
    cout << "\n" << titulo << "\n";
    cout << string(60, '=') << endl;
    cout << left << setw(15) << "CODIGO" 
         << setw(30) << "NOMBRE" 
         << right << setw(10) << "PRECIO" << endl;
    cout << string(60, '-') << endl;
    
    for (const auto& p : productos) {
        p.mostrar();
    }
    cout << string(60, '=') << endl;
}
void crearArchivoEjemplo() {
    ofstream archivo("productos.txt");
  
    if (archivo.is_open()) {
        archivo << "P001,Laptop HP,1200.50\n";
        archivo << "P002,Mouse Logitech,25.99\n";
        archivo << "P003,Teclado Mecanico,85.00\n";
        archivo << "P004,Monitor Samsung,350.75\n";
        archivo << "P005,Auriculares Sony,120.00\n";
        archivo << "P006,Webcam HD,45.50\n";
        archivo << "P007,Disco Duro 1TB,75.99\n";
        archivo << "P008,Memoria RAM 16GB,95.00\n";
        archivo << "P009,SSD 500GB,110.25\n";
        archivo << "P010,Impresora Epson,280.00\n";
        
        archivo.close();
        cout << "Archivo 'productos.txt' creado exitosamente.\n";
    }
}
int main() {
    string nombreArchivo;
    int opcion;
    
    cout << "========================================\n";
    cout << "  ORDENAMIENTO DE PRODUCTOS POR PRECIO\n";
    cout << "========================================\n\n";
    
    cout << "1. Usar archivo existente\n";
    cout << "2. Crear archivo de ejemplo\n";
    cout << "Opcion: ";
    cin >> opcion;
    
    if (opcion == 2) {
        crearArchivoEjemplo();
        nombreArchivo = "productos.txt";
    } else {
        cout << "\nIngrese el nombre del archivo (ejemplo: productos.txt): ";
        cin >> nombreArchivo;
    }
    vector<Producto> productos = leerArchivo(nombreArchivo);
    
    if (productos.empty()) {
        cout << "\nNo se encontraron productos en el archivo.\n";
        return 1;
    }
    
    cout << "\nSe cargaron " << productos.size() << " productos.\n";
    mostrarProductos(productos, "PRODUCTOS ORIGINALES");
    vector<Producto> productosMerge = productos;
    mergeSort(productosMerge, 0, productosMerge.size() - 1);
    mostrarProductos(productosMerge, "ORDENADOS CON MERGE SORT (Mayor a Menor)");
    vector<Producto> productosQuick = productos;
    quickSort(productosQuick, 0, productosQuick.size() - 1);
    mostrarProductos(productosQuick, "ORDENADOS CON QUICK SORT (Mayor a Menor)");
    
    return 0;
}
