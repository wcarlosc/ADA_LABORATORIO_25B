import random

class Graph:
    def __init__(self):
        self.nodes = [] #contiene representaciones e.g ("A","B",...)
        self.edges = [] #contiene las aristas e.g ("A","B",5),("C","B",5),...
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
    return random.randint(2, 10)

def find(parent, node):
    if parent[node] != node:
        parent[node] = find(parent, parent[node])
    return parent[node]

def kruskal(graph):
    result = Graph()
    parent = {node: node for node in graph.nodes}
    sorted_edges = sorted(graph.edges, key=lambda x: x[2]) # ordena por pesos
    
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

print("***Original****")
g = random_graph(11, 20)
g.print_graph()

print("\n***Kruskal****")
g_kruskal = kruskal(g)
g_kruskal.print_graph()

print("\n***Prim****")
g_prim = prim(g)
g_prim.print_graph()