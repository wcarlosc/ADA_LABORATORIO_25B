import java.util.*;

public class Ejercicio03 {
    
    static final int INF = (int)1e8;
    
    static int[] bellmanFord(int V, List<int[]> edges, int src) {
        int[] dist = new int[V];
        Arrays.fill(dist, INF);
        dist[src] = 0;
        
        for (int i = 0; i < V; i++) {
            for (int[] edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int wt = edge[2];
                if (dist[u] != INF && dist[u] + wt < dist[v]) {
                    if (i == V - 1) {
                        return new int[]{-1};
                    }
                    dist[v] = dist[u] + wt;
                }
            }
        }
        
        return dist;
    }
    
    static List<int[]> randomGraph(int numNodes, int numEdges) {
        List<int[]> edges = new ArrayList<>();
        Random rand = new Random();
        int r = 0;
        
        for (int i = 0; i < numNodes; i++) {
            for (int j = i + 1; j < numNodes; j++) {
                if (r >= numEdges) break;
                int weight = rand.nextInt(20) - 10; // Pesos negativos: -10 a 9
                edges.add(new int[]{i, j, weight});
                r++;
            }
            if (r >= numEdges) break;
        }
        
        // Forzar ciclo negativo ocasionalmente
        if (rand.nextInt(2) == 0 && numNodes >= 3) {
            edges.add(new int[]{0, 1, -3});
            edges.add(new int[]{1, 2, -2});
            edges.add(new int[]{2, 0, -3});
        }
        
        return edges;
    }
    
    public static void main(String[] args) {
        
        List<int[]> edges = randomGraph(7, 7);
        
        System.out.println("Grafo generado:");
        for (int[] e : edges) {
            System.out.println(e[0] + " -> " + e[1] + " (peso: " + e[2] + ")");
        }
        
        int[] result = bellmanFord(V, edges, 0);
        
        if (result.length == 1 && result[0] == -1) {
            System.out.println("\nCICLO NEGATIVO DETECTADO!");
        } else {
            System.out.println("\nDistancias desde vertice 0:");
            for (int i = 0; i < V; i++) {
                if (result[i] == INF) {
                    System.out.println("Vertice " + i + ": INF");
                } else {
                    System.out.println("Vertice " + i + ": " + result[i]);
                }
            }
        }
    }
}