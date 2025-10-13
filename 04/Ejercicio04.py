import random
import time

class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = []
        self.cost = 0
    
    def add_node(self, value):
        if value not in self.nodes:
            self.nodes.append(value)
    
    def add_edge(self, node1, node2, weight):
        self.add_node(node1)
        self.add_node(node2)
        self.cost += weight
        self.edges.append((node1, node2, weight))
    
    def print_graph(self):
        print("Nodos:")
        for n in self.nodes:
            print(f"{n} " , end="")
        print("\nAristas:")
        for (n1, n2, w) in self.edges:
            print(f"  {n1} - {n2} : {w}")
        print(f"costo: {self.cost}")

def random_graph(num_nodes, num_edges):
    g = Graph()
    for i in range(num_nodes):
        g.add_node(chr(65 + i))
    r = 0
    for i in range(num_nodes):
        for j in range(i + 1, num_nodes):
            if r >= num_edges:
                break
            g.add_edge(g.nodes[i], g.nodes[j], number_random())
            r += 1
    return g

def number_random():
    return random.randint(1, 10)

def find(parent, node):
    if parent[node] != node:
        parent[node] = find(parent, parent[node])
    return parent[node]

def kruskal(graph):
    result = Graph()
    parent = {node: node for node in graph.nodes}
    sorted_edges = sorted(graph.edges, key=lambda x: x[2])
    
    for node1, node2, weight in sorted_edges:
        root1 = find(parent, node1)
        root2 = find(parent, node2)
        if root1 != root2:
            result.add_edge(node1, node2, weight)
            parent[root2] = root1
    
    return result

def prim(graph):
    result = Graph()
    if not graph.nodes:
        return result
    
    distance = {node: float('inf') for node in graph.nodes}
    parent = {node: None for node in graph.nodes}
    adj = {node: [] for node in graph.nodes}
    
    for node1, node2, weight in graph.edges:
        adj[node1].append((node2, weight))
        adj[node2].append((node1, weight))
    
    start = graph.nodes[0]
    distance[start] = 0
    queue = [(0, start)]
    visited = set()
    
    while queue:
        queue.sort()
        _, u = queue.pop(0)
        if u in visited:
            continue
        visited.add(u)
        
        if parent[u] is not None:
            result.add_edge(parent[u], u, distance[u])
        
        for v, weight in adj[u]:
            if v not in visited and weight < distance[v]:
                parent[v] = u
                distance[v] = weight
                queue.append((weight, v))
    
    return result

def kruskal_matrix(graph):
    result = Graph()
    n = len(graph.nodes)
    node_index = {graph.nodes[i]: i for i in range(n)}
    matrix = [[float('inf')] * n for _ in range(n)]
    
    for node1, node2, weight in graph.edges:
        i, j = node_index[node1], node_index[node2]
        matrix[i][j] = matrix[j][i] = weight
    
    edges_list = []
    for i in range(n):
        for j in range(i + 1, n):
            if matrix[i][j] != float('inf'):
                edges_list.append((graph.nodes[i], graph.nodes[j], matrix[i][j]))
    
    parent = {node: node for node in graph.nodes}
    sorted_edges = sorted(edges_list, key=lambda x: x[2])
    
    for node1, node2, weight in sorted_edges:
        root1 = find(parent, node1)
        root2 = find(parent, node2)
        if root1 != root2:
            result.add_edge(node1, node2, weight)
            parent[root2] = root1
    
    return result

def prim_matrix(graph):
    result = Graph()
    if not graph.nodes:
        return result
    
    n = len(graph.nodes)
    node_index = {graph.nodes[i]: i for i in range(n)}
    matrix = [[float('inf')] * n for _ in range(n)]
    
    for node1, node2, weight in graph.edges:
        i, j = node_index[node1], node_index[node2]
        matrix[i][j] = matrix[j][i] = weight
    
    distance = [float('inf')] * n
    parent = [None] * n
    visited = [False] * n
    
    distance[0] = 0
    
    for _ in range(n):
        u = min((d, i) for i, d in enumerate(distance) if not visited[i])[1]
        visited[u] = True
        
        if parent[u] is not None:
            result.add_edge(graph.nodes[parent[u]], graph.nodes[u], distance[u])
        
        for v in range(n):
            if not visited[v] and matrix[u][v] < distance[v]:
                parent[v] = u
                distance[v] = matrix[u][v]
    
    return result

def test(n):
    nodesMax = (int)(n *(n - 1)/2) 
    g = random_graph(n, nodesMax)
    print(f"nodos = {n} |  aristas = {nodesMax}")
    
    start = time.time()
    g_kruskal = kruskal(g)
    print("Tiempo kruskal (lista) :",(time.time() - start)* 1000 , "ms")
    
    start = time.time()
    g_prim = prim(g)
    print("Tiempo prim (lista) :",(time.time() - start)* 1000 , "ms")
    
    start = time.time()
    g_kruskal_matrix = kruskal_matrix(g)
    print("Tiempo kruskal (matriz) :",(time.time() - start)* 1000 , "ms")
    
    start = time.time()
    g_prim_matrix = prim_matrix(g)
    print("Tiempo prim (matriz) :",(time.time() - start)* 1000 , "ms")

print("****10 nodos****")
test(10)
print("\n****50 nodos****")
test(50)
print("\n****100 nodos****")
test(100)