import java.util.Arrays;
import java.util.Random;

class Main {

    public static int particion(float arr[], int menor, int mayor) {
        float pivote = arr[mayor];  
        int i = menor - 1;
        for (int j = menor; j < mayor; j++) {
            if (arr[j] < pivote) {
                i++;
             
                float temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }


        float temp = arr[i + 1];
        arr[i + 1] = arr[mayor];
        arr[mayor] = temp;


        return i + 1;
    }

    public static void quicksort(float arr[], int menor, int mayor) {
        if (menor < mayor) {
            int pi = particion(arr, menor, mayor);
            quicksort(arr, menor, pi - 1);
            quicksort(arr, pi + 1, mayor);
        }
    }


    static final Random rng = new Random();
    public static int particionAleatorio(float arr[], int menor, int mayor) {
        int pivotIndex = menor + rng.nextInt(mayor - menor + 1);
        float pivote = arr[pivotIndex];
        int i = menor;
        int j = mayor;
        while (i <= j) {
            while (arr[i] < pivote) i++;
            while (arr[j] > pivote) j--;


            if (i <= j) {
               
                float temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;


                i++;
                j--;
            }
        }
        return i;
    }
    public static void quicksortAleatorio(float arr[], int menor, int mayor) {
        if (menor < mayor) {
            int pi = particionAleatorio(arr, menor, mayor);
            quicksortAleatorio(arr, menor, pi - 1);
            quicksortAleatorio(arr, pi, mayor);
        }
    }

    public static void main(String[] args) {
        float arrBase[] = {38.5f, 27.1f, 43.0f, 3.3f, 9.9f, 82.2f, 10.0f};


        float arrFijo[] = Arrays.copyOf(arrBase, arrBase.length);
        float arrRand[] = Arrays.copyOf(arrBase, arrBase.length);


        long t0 = System.nanoTime();
        quicksort(arrFijo, 0, arrFijo.length - 1);
        long t1 = System.nanoTime();


       
        long t2 = System.nanoTime();
        quicksortAleatorio(arrRand, 0, arrRand.length - 1);
        long t3 = System.nanoTime();

        System.out.println("Ordenado (pivote fijo):      " + Arrays.toString(arrFijo));
        System.out.println("Tiempo (pivote fijo):        " + (t1 - t0) + " ns");
        System.out.println("Ordenado (pivote aleatorio): " + Arrays.toString(arrRand));
        System.out.println("Tiempo (pivote aleatorio):   " + (t3 - t2) + " ns");
    }
}
