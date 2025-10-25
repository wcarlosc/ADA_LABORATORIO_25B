import java.util.*;

public class Ejercicio01 {
    
    static class Edge {
        int u, v, weight;
        Edge(int u, int v, int weight) {
            this.u = u;
            this.v = v;
            this.weight = weight;
        }
    }
    
    static class Node implements Comparable<Node> {
        int vertex, dist;
        Node(int dist, int vertex) {
            this.dist = dist;
            this.vertex = vertex;
        }
        public int compareTo(Node other) {
            return Integer.compare(this.dist, other.dist);
        }
    }
    
    static List<List<int[]>> constructAdj(List<Edge> edges, int V) {
        List<List<int[]>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }
        
        for (Edge edge : edges) {
            adj.get(edge.u).add(new int[]{edge.v, edge.weight});
            adj.get(edge.v).add(new int[]{edge.u, edge.weight});
        }
        return adj;
    }
    
    static int[] dijkstra(int V, List<Edge> edges, int src) {
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
    
    static List<Edge> randomGraph(int numNodes, int numEdges) {
        List<Edge> edges = new ArrayList<>();
        Random rand = new Random();
        int r = 0;
        
        for (int i = 0; i < numNodes; i++) {
            for (int j = i + 1; j < numNodes; j++) {
                if (r >= numEdges) break;
                int weight = rand.nextInt(9) + 2;
                edges.add(new Edge(i, j, weight));
                r++;
            }
            if (r >= numEdges) break;
        }
        return edges;
    }
    
    static char getNodeName(int i) {
        return (char)('A' + i);
    }
    
    public static void main(String[] args) {
        src = 0;
        
        List<Edge> edges = randomGraph(8,15);
        
        System.out.println("Aristas del grafo:");
        for (Edge e : edges) {
            System.out.println(getNodeName(e.u) + " - " + getNodeName(e.v) + " : " + e.weight);
        }
        
        int[] result = dijkstra(V, edges, src);
        
        System.out.println("\nDistancias ordenadas " + getNodeName(src) + ":");
        for (int i = 0; i < V; i++) {
            System.out.println("Vertice " + getNodeName(i) + ": " + result[i]);
        }
    }
}