import random
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

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
    return random.randint(2, 10)

def find(parent, node):
    if parent[node] != node:
        parent[node] = find(parent, parent[node])
    return parent[node]

def visualize_steps(graph, steps, title):
    G = nx.Graph()
    for n in graph.nodes:
        G.add_node(n)
    for n1, n2, w in graph.edges:
        G.add_edge(n1, n2, weight=w)
    
    pos = nx.spring_layout(G, seed=42)
    fig, ax = plt.subplots(figsize=(10, 8))
    
    current_step = [0]
    
    def update(frame):
        ax.clear()
        mst_edges = steps[current_step[0]]
        
        nx.draw_networkx_nodes(G, pos, node_color='lightblue', node_size=700, ax=ax)
        edge_colors = ['red' if (u, v) in mst_edges or (v, u) in mst_edges else 'lightgray' for u, v in G.edges()]
        edge_widths = [3 if (u, v) in mst_edges or (v, u) in mst_edges else 1 for u, v in G.edges()]
        nx.draw_networkx_edges(G, pos, edge_color=edge_colors, width=edge_widths, ax=ax)
        nx.draw_networkx_labels(G, pos, font_size=12, font_weight='bold', ax=ax)
        edge_labels = {(u, v): G[u][v]['weight'] for u, v in G.edges()}
        nx.draw_networkx_edge_labels(G, pos, edge_labels, font_size=10, ax=ax)
        
        ax.set_title(f"{title} - Step {current_step[0]}/{len(steps)-1}", fontsize=14, fontweight='bold')
        ax.axis('off')
    
    def on_key(event):
        if event.key == 'right' and current_step[0] < len(steps) - 1:
            current_step[0] += 1
            update(None)
            fig.canvas.draw()
        elif event.key == 'left' and current_step[0] > 0:
            current_step[0] -= 1
            update(None)
            fig.canvas.draw()
    
    fig.canvas.mpl_connect('key_press_event', on_key)
    update(None)
    plt.tight_layout()
    plt.show()

def kruskal(graph, visualize=False):
    result = Graph()
    parent = {node: node for node in graph.nodes}
    sorted_edges = sorted(graph.edges, key=lambda x: x[2])
    
    steps = [[]]
    mst_edges = []
    
    for node1, node2, weight in sorted_edges:
        root1 = find(parent, node1)
        root2 = find(parent, node2)
        if root1 != root2:
            result.add_edge(node1, node2, weight)
            parent[root2] = root1
            mst_edges.append((node1, node2))
            steps.append(mst_edges.copy())
    
    if visualize:
        visualize_steps(graph, steps, "Kruskal")
    
    return result

def prim(graph, visualize=False):
    result = Graph()
    if not graph.nodes:
        return result
    
    distance = {node: float('inf') for node in graph.nodes}
    parent = {node: None for node in graph.nodes}
    adj = {node: [] for node in graph.nodes}
    
    for node1, node2, weight in graph.edges:
        adj[node1].append((node2, weight))
        adj[node2].append((node1, weight))
    
    steps = [[]]
    mst_edges = []
    
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
            mst_edges.append((parent[u], u))
            steps.append(mst_edges.copy())
        
        for v, weight in adj[u]:
            if v not in visited and weight < distance[v]:
                parent[v] = u
                distance[v] = weight
                queue.append((weight, v))
    
    if visualize:
        visualize_steps(graph, steps, "Prim")
    
    return result

print("***Original****")
g = random_graph(7, 18)
g.print_graph()

print("\n***Kruskal****")
g_kruskal = kruskal(g, visualize=True)
g_kruskal.print_graph()

print("\n***Prim****")
g_prim = prim(g, visualize=True)
g_prim.print_graph()