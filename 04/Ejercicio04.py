import random
import time

class Graph:
    def __init__(self):
        self.adj = {} 
        self.matrix = []
        self.nodes = []
        self.cost = 0
        self.useMatrix = False
    
    def addNode(self, value):
        if value not in self.adj:
            self.adj[value] = []
        if value not in self.nodes:
            self.nodes.append(value)
            n = len(self.nodes)
            for row in self.matrix:
                row.append(0)
            self.matrix.append([0] * n)
    
    def addEdge(self, node1, node2, weight):
        self.addNode(node1)
        self.addNode(node2)
        self.cost += weight
        # Lista de adyacencia
        self.adj[node1].append((node2, weight))
        self.adj[node2].append((node1, weight))
        # Matriz de adyacencia
        i = self.nodes.index(node1)
        j = self.nodes.index(node2)
        self.matrix[i][j] = weight
        self.matrix[j][i] = weight
    
    def getEdges(self):
        if self.useMatrix:
            edges = []
            for i in range(len(self.nodes)):
                for j in range(i + 1, len(self.nodes)):
                    if self.matrix[i][j] > 0:
                        edges.append((self.nodes[i], self.nodes[j], self.matrix[i][j]))
            return edges
        else:
            seen = set()
            edges = []
            for node1 in self.adj:
                for node2, weight in self.adj[node1]:
                    edge = tuple(sorted([node1, node2]))
                    if edge not in seen:
                        seen.add(edge)
                        edges.append((node1, node2, weight))
            return edges

def randomGraph(numNodes, numEdges):
    g = Graph()
    nodes = [chr(65 + i) for i in range(numNodes)]
    for n in nodes:
        g.addNode(n)
    
    possibleEdges = []
    for i in range(numNodes):
        for j in range(i + 1, numNodes):
            possibleEdges.append((nodes[i], nodes[j]))
    
    random.shuffle(possibleEdges)
    selectedEdges = possibleEdges[:min(numEdges, len(possibleEdges))]
    
    for node1, node2 in selectedEdges:
        g.addEdge(node1, node2, random.randint(2, 20))
    
    return g

def find(parent, node):
    if parent[node] != node:
        parent[node] = find(parent, parent[node])
    return parent[node]

def kruskal(graph):
    result = Graph()
    parent = {node: node for node in graph.adj}
    sortedEdges = sorted(graph.getEdges(), key=lambda x: x[2])
    
    for node1, node2, weight in sortedEdges:
        root1 = find(parent, node1)
        root2 = find(parent, node2)
        if root1 != root2:
            result.addEdge(node1, node2, weight)
            parent[root2] = root1
    
    return result

def prim(graph):
    result = Graph()
    if not graph.adj:
        return result
    
    distance = {node: float('inf') for node in graph.adj}
    parent = {node: None for node in graph.adj}
    
    start = list(graph.adj.keys())[0]
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
            result.addEdge(parent[u], u, distance[u])
        
        for v, weight in graph.adj[u]:
            if v not in visited and weight < distance[v]:
                parent[v] = u
                distance[v] = weight
                queue.append((weight, v))
    
    return result

def kruskalMatrix(graph):
    result = Graph()
    parent = {node: node for node in graph.nodes}
    graph.useMatrix = True
    sortedEdges = sorted(graph.getEdges(), key=lambda x: x[2])
    graph.useMatrix = False
    
    for node1, node2, weight in sortedEdges:
        root1 = find(parent, node1)
        root2 = find(parent, node2)
        if root1 != root2:
            result.addEdge(node1, node2, weight)
            parent[root2] = root1
    
    return result

def primMatrix(graph):
    result = Graph()
    if not graph.nodes:
        return result
    
    distance = {node: float('inf') for node in graph.nodes}
    parent = {node: None for node in graph.nodes}
    
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
            result.addEdge(parent[u], u, distance[u])
        
        uIdx = graph.nodes.index(u)
        for vIdx, weight in enumerate(graph.matrix[uIdx]):
            if weight > 0:
                v = graph.nodes[vIdx]
                if v not in visited and weight < distance[v]:
                    parent[v] = u
                    distance[v] = weight
                    queue.append((weight, v))
    
    return result

def test(n):
    nodesMax = int(n * (n - 1) / 2) 
    g = randomGraph(n, nodesMax)
    print(f"nodos = {n} |  aristas = {nodesMax}")
    
    start = time.time()
    kruskal(g)
    print("Tiempo kruskal (lista) :", (time.time() - start) * 1000, "ms")
    start = time.time()
    kruskalMatrix(g)
    print("Tiempo kruskal (matriz) :", (time.time() - start) * 1000, "ms")
    
    start = time.time()
    prim(g)
    print("Tiempo prim (lista) :", (time.time() - start) * 1000, "ms")
    start = time.time()
    primMatrix(g)
    print("Tiempo prim (matriz) :", (time.time() - start) * 1000, "ms")

print("****10 nodos****")
test(10)
print("\n****50 nodos****")
test(50)
print("\n****100 nodos****")
test(100)