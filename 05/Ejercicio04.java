import java.util.*;

public class Ejercicio04 {
    
    static final int INF = (int)1e8;
    
    static class Node implements Comparable<Node> {
        int dist, vertex;
        Node(int dist, int vertex) {
            this.dist = dist;
            this.vertex = vertex;
        }
        public int compareTo(Node other) {
            return Integer.compare(this.dist, other.dist);
        }
    }
    
    static List<List<int[]>> constructAdj(List<int[]> edges, int V) {
        List<List<int[]>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], wt = edge[2];
            adj.get(u).add(new int[]{v, wt});
            adj.get(v).add(new int[]{u, wt});
        }
        return adj;
    }
    
    static int[] dijkstra(int V, List<int[]> edges, int src) {
        List<List<int[]>> adj = constructAdj(edges, V);
        PriorityQueue<Node> pq = new PriorityQueue<>();
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        
        pq.add(new Node(0, src));
        dist[src] = 0;
        
        while (!pq.isEmpty()) {
            Node current = pq.poll();
            int u = current.vertex;
            
            for (int[] neighbor : adj.get(u)) {
                int v = neighbor[0];
                int weight = neighbor[1];
                
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.add(new Node(dist[v], v));
                }
            }
        }
        return dist;
    }
    
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
                if (dist[i][j] == INF) System.out.print("INF ");
                else System.out.print(dist[i][j] + "   ");
            }
            System.out.println();
        }
    }
    
    static int[] bellmanFord(int V, List<int[]> edges, int src) {
        int[] dist = new int[V];
        Arrays.fill(dist, INF);
        dist[src] = 0;
        
        for (int i = 0; i < V; i++) {
            for (int[] edge : edges) {
                int u = edge[0], v = edge[1], wt = edge[2];
                if (dist[u] != INF && dist[u] + wt < dist[v]) {
                    if (i == V - 1) return new int[]{-1};
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
                int weight = rand.nextInt(20) + 1;
                edges.add(new int[]{i, j, weight});
                r++;
            }
            if (r >= numEdges) break;
        }
        return edges;
    }
    
    static void test(int n) {
        int numEdges = n * (n - 1) / 2;
        List<int[]> edges = randomGraph(n, numEdges);
        
        System.out.println("nodos = " + n + " | aristas = " + numEdges);
        
        // Dijkstra
        long start = System.currentTimeMillis();
        dijkstra(n, edges, 0);
        long dijkstraTime = System.currentTimeMillis() - start;
        System.out.println("Tiempo Dijkstra: " + dijkstraTime + " ms");
        
        // Bellman-Ford
        start = System.currentTimeMillis();
        bellmanFord(n, edges, 0);
        long bellmanTime = System.currentTimeMillis() - start;
        System.out.println("Tiempo Bellman-Ford: " + bellmanTime + " ms");
        
        // Floyd-Warshall
        int[][] dist = new int[n][n];
        for (int i = 0; i < n; i++) {
            Arrays.fill(dist[i], INF);
            dist[i][i] = 0;
        }
        for (int[] e : edges) {
            dist[e[0]][e[1]] = e[2];
            dist[e[1]][e[0]] = e[2];
        }
        start = System.currentTimeMillis();
        floydWarshall(dist);
        long floydTime = System.currentTimeMillis() - start;
        System.out.println("Tiempo Floyd-Warshall: " + floydTime + " ms\n");
    }
    
    public static void main(String[] args) {
        System.out.println("=== GRAFOS ===\n");
        
        test(100);
        test(500);
        test(1000);
    }
}