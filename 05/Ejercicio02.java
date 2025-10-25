import java.util.Random;

public class Ejercicio02 {
    
    static final int INF = (int)1e8;
    
    static void floydWarshall(int[][] dist) {
        int V = dist.length;
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }
    
    static void showGraphMatrix(int[][] dist) {
        int V = dist.length;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF) {
                    System.out.print("INF ");
                } else {
                    System.out.print(dist[i][j] + "   ");
                }
            }
            System.out.println();
        }
    }
    
    public static void main(String[] args) {
        Random rand = new Random();
        int V = 6;
        int[][] dist = new int[V][V];
        
        // Inicializar con INF
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = INF;
            }
        }
        
        // Diagonal nula
        for (int i = 0; i < V; i++) {
            dist[i][i] = 0;
        }
        
        // Aristas aleatorias con grafo dirigido
        int numEdges = 10;
        for (int i = 0; i < numEdges; i++) {
            int u = rand.nextInt(V);
            int v = rand.nextInt(V);
            if (u != v) {
                dist[u][v] = rand.nextInt(20) + 1;
            }
        }
        
        System.out.println("Grafo inicial:");
        showGraphMatrix(dist);
        
        floydWarshall(dist);
        
        System.out.println("\nDistancias minimas:");
        showGraphMatrix(dist);
    }
}