import random
import networkx as nx
import matplotlib.pyplot as plt

class Graph:
    def __init__(self):
        self.adj = {}
        self.cost = 0
    
    def addNode(self, value):
        if value not in self.adj:
            self.adj[value] = []
    
    def addEdge(self, node1, node2, weight):
        self.addNode(node1)
        self.addNode(node2)
        self.cost += weight
        self.adj[node1].append((node2, weight))
        self.adj[node2].append((node1, weight))
    
    def getEdges(self):
        seen = set()
        edges = []
        for node1 in self.adj:
            for node2, weight in self.adj[node1]:
                edge = tuple(sorted([node1, node2]))
                if edge not in seen:
                    seen.add(edge)
                    edges.append((node1, node2, weight))
        return edges
    
    def printGraph(self):
        print("Nodos:")
        for n in self.adj:
            print(f"{n} ", end="")
        print("\nAristas:")
        for n1, n2, w in self.getEdges():
            print(f"  {n1} - {n2} : {w}")
        print(f"costo: {self.cost}")
        
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
        g.addEdge(node1, node2, random.randint(2, 10))
    
    return g

def find(parent, node):
    if parent[node] != node:
        parent[node] = find(parent, parent[node])
    return parent[node]

def visualizeSteps(graph, steps, title):
    G = nx.Graph()
    for n in graph.adj:
        G.add_node(n)
    for n1, n2, w in graph.getEdges():
        G.add_edge(n1, n2, weight=w)
    
    pos = nx.spring_layout(G, seed=42)
    fig, ax = plt.subplots(figsize=(10, 8))
    
    currentStep = [0]
    
    def update(frame):
        ax.clear()
        mstEdges = steps[currentStep[0]]
        
        nx.draw_networkx_nodes(G, pos, node_color='lightblue', node_size=700, ax=ax)
        edgeColors = ['red' if (u, v) in mstEdges or (v, u) in mstEdges else 'lightgray' for u, v in G.edges()]
        edgeWidths = [3 if (u, v) in mstEdges or (v, u) in mstEdges else 1 for u, v in G.edges()]
        nx.draw_networkx_edges(G, pos, edge_color=edgeColors, width=edgeWidths, ax=ax)
        nx.draw_networkx_labels(G, pos, font_size=12, font_weight='bold', ax=ax)
        edgeLabels = {(u, v): G[u][v]['weight'] for u, v in G.edges()}
        nx.draw_networkx_edge_labels(G, pos, edgeLabels, font_size=10, ax=ax)
        
        ax.set_title(f"{title} - Step {currentStep[0]}/{len(steps)-1}", fontsize=14, fontweight='bold')
        ax.axis('off')
    
    def onKey(event):
        if event.key == 'right' and currentStep[0] < len(steps) - 1:
            currentStep[0] += 1
            update(None)
            fig.canvas.draw()
        elif event.key == 'left' and currentStep[0] > 0:
            currentStep[0] -= 1
            update(None)
            fig.canvas.draw()
    
    fig.canvas.mpl_connect('key_press_event', onKey)
    update(None)
    plt.tight_layout()
    plt.show()

def kruskal(graph, visualize=False):
    result = Graph()
    parent = {node: node for node in graph.adj}
    sortedEdges = sorted(graph.getEdges(), key=lambda x: x[2])
    
    steps = [[]]
    mstEdges = []
    
    for node1, node2, weight in sortedEdges:
        root1 = find(parent, node1)
        root2 = find(parent, node2)
        if root1 != root2:
            result.addEdge(node1, node2, weight)
            parent[root2] = root1
            mstEdges.append((node1, node2))
            steps.append(mstEdges.copy())
    
    if visualize:
        visualizeSteps(graph, steps, "Kruskal")
    
    return result

def prim(graph, visualize=False):
    result = Graph()
    if not graph.adj:
        return result
    
    distance = {node: float('inf') for node in graph.adj}
    parent = {node: None for node in graph.adj}
    
    steps = [[]]
    mstEdges = []
    
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
            mstEdges.append((parent[u], u))
            steps.append(mstEdges.copy())
        
        for v, weight in graph.adj[u]:
            if v not in visited and weight < distance[v]:
                parent[v] = u
                distance[v] = weight
                queue.append((weight, v))
    
    if visualize:
        visualizeSteps(graph, steps, "Prim")
    
    return result

print("***Original****")
g = randomGraph(7, 15)
g.printGraph()
print("\n***Kruskal****")
gKruskal = kruskal(g, visualize=True)
gKruskal.printGraph()
print("\n***Prim****")
gPrim = prim(g, visualize=True)
gPrim.printGraph()