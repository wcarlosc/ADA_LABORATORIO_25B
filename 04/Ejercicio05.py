import random

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
            print(f"  {n1} - {n2} : {w} km")
        print(f"Costo total: {self.cost} km de fibra")

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

# PROBLEMA 
def red_fibra_optica():
    g = Graph()
    # Distritos
    distritos = {
        "Cercado": "A", "Yanahuara": "B", "Cayma": "C", 
        "Miraflores": "D", "Paucarpata": "E", "SocabayaJ.L.B.yR.": "F"
    }
    
    # Conexiones posibles
    conexiones = [
        ("Cercado", "Yanahuara", 3), ("Cercado", "Cayma", 5), ("Cercado", "Miraflores", 4),
        ("Cercado", "Paucarpata", 6), ("Yanahuara", "Cayma", 4), ("Yanahuara", "Miraflores", 5),
        ("Cayma", "SocabayaJ.L.B.yR.", 8), ("Miraflores", "Paucarpata", 3), 
        ("Paucarpata", "SocabayaJ.L.B.yR.", 7), ("Miraflores", "SocabayaJ.L.B.yR.", 9)
    ]
    
    for d1, d2, dist in conexiones:
        g.add_edge(distritos[d1], distritos[d2], dist)
    
    return g, distritos

print("FIBRA ÓPTICA")
print("\nDistritos a conectar:")
g_ciudad, distritos = red_fibra_optica()
for nombre, codigo in distritos.items():
    print(f"  {codigo} = {nombre}")
print("\n---Red completa (todas las conexiones posibles)---")
g_ciudad.print_graph()
print("\n---Solución con KRUSKAL (mínimo costo)---")
g_kruskal = kruskal(g_ciudad)
g_kruskal.print_graph()
print("\n---Solución con PRIM (mínimo costo)---")
g_prim = prim(g_ciudad)
g_prim.print_graph()
