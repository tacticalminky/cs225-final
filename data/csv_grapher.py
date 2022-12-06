# To be able to use this script, you need to
# a) pip install networkx
# b) pip install matplotlib
# if you don't already have these two. The simple solution is download the 
# packages and run it in PyCharm if you dont wanna do it in terminal.
# Along with that, you have to make sure that the output-graph.csv is in the same folder as this
# python script for it to work, and then it will paste the final image in the same location.

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
        graph.add_edge(parts[0], parts[x], weight=(float(parts[x + 1])))

csv.close()

# Display
nx.draw(graph, with_labels=True)
plot.savefig("connected_components.png")
