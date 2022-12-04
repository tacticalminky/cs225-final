import networkx as nx
import matplotlib.pyplot as plot

# Take CSV -> Graph Edges
graph = nx.Graph()
csv = open("output-graph.csv")

lines = csv.readlines()[1:]  # Skip line 1
for line in lines:
    parts = line.split(',')

    if len(parts) == 1:
        graph.add_node(parts[0])

    for x in range(1, len(parts), 2):
        graph.add_edge(parts[0], parts[x], weight=(int(parts[x + 1])))

csv.close()

# Display?
nx.draw(graph, with_labels=True)
plot.savefig("connected_components.png")
