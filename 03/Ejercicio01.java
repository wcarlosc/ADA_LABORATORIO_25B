import java.util.Scanner;

class Estudiante {
    String codigo;
    String nombre;
    float promedio;
    Estudiante(String c, String n) {
        codigo = c;
        nombre = n;
    }
    void calcularPromedio(float[] notas) {
        float suma = 0;
        for (float nota : notas) {
            suma += nota;
        }
        promedio = (notas.length > 0) ? (suma / notas.length) : 0f;
    }
    
}
class Ejercicio01{

    static void mergeSort(Estudiante[] arr, int izq, int der) {
        if (izq < der) {
            int mid = (izq + der) / 2;
            mergeSort(arr, izq, mid);
            mergeSort(arr, mid + 1, der);
            merge(arr, izq, mid, der);
        }
    }

    static void merge(Estudiante[] arr, int izq, int mid, int der) {
        int n1 = mid - izq + 1;
        int n2 = der - mid;
        Estudiante[] L = new Estudiante[n1];
        Estudiante[] R = new Estudiante[n2];
        for (int i = 0; i < n1; i++) 
            L[i] = arr[izq + i];
        for (int j = 0; j < n2; j++) 
            R[j] = arr[mid + 1 + j];
        int i = 0, j = 0, k = izq;
        while (i < n1 && j < n2) {
            if (Float.compare(L[i].promedio, R[j].promedio) >= 0) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Cantidad de estudiantes: ");
        int n = sc.nextInt();
        Estudiante[] estudiantes = new Estudiante[n];


        for (int idx = 0; idx < n; idx++) {
            System.out.println("\n--- Estudiante " + (idx + 1) + " ---");
            System.out.print("Código: ");
            String codigo = sc.nextLine().trim();
            sc.nextLine();
            System.out.println("Nombre: ");
            String nombre = sc.nextLine().trim();


            System.out.print("Número de cursos: ");
            int k = sc.nextInt();


            float[] notas = new float[k];
            for (int i = 0; i < k; i++) {
                System.out.print("  Nota del curso " + (i + 1) + ": ");
                notas[i] = sc.nextFloat();
            }


            Estudiante e = new Estudiante(codigo, nombre);
            e.calcularPromedio(notas);
            estudiantes[idx] = e;
        }
        mergeSort(estudiantes, 0, n - 1);
        System.out.println("\n Resultados");
        for (Estudiante e : estudiantes) {
         
            String promedioTexto = String.format( "%.2f", e.promedio);
            System.out.println(e.codigo + " " + e.nombre + " " + promedioTexto);
        }
        sc.close();
    }
}
