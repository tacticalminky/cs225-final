# To be able to use this script, you need to
# a) pip install networkx
# b) pip install matplotlib
# if you don't already have these two. The simple solution is download the 
# packages and run it in PyCharm if you dont wanna do it in terminal.
# Along with that, you have to make sure that the output-graph.csv is in the same folder as this
# python script for it to work, and then it will paste the final image in the same location.

# The code will ask for a user input, and the choices will be listed on screen. The default value will be white

import matplotlib.pyplot as plot
import networkx as nx

# Take CSV -> Graph
def make_graph(iterations):
    # Open file
    graph = nx.Graph()
    csv = open("output-graph.csv", encoding="utf8")
    lines = csv.readlines()[1:]  # Skip line 1

    # Go through lines to add edges
    iterate = 0
    for line in lines:
        if iterate == iterations:
            break
        iterate += 1

        delim_1 = line.split('"')

        if len(delim_1) == 3:
            parts = line.split(',')
            graph.add_node(parts[1])
            continue

        names = delim_1[3].split(',')

        for x in range(1, len(names)):
            graph.add_edge(names[0], names[x])
    csv.close()

    # Make pretty
    deg = dict(graph.degree)
    vals = list(deg.values())
    cols = []
    
    color_map = {
        0: "blue",
        1: "brown",
        2: "yellow",
        3: "orange",
        4: "pink",
        5: "green",
        6: "red"
    }

    vals.sort()

    for v in vals:
        num = int(float(v) / 20.0)
        if num > 6:
            num = 6

        cols.append(color_map[num])
    return [vals, cols, graph]


# Display for 364 nodes to show connected components
# This type of display maxes out at 364 nodes, hence the value
val, col, g = make_graph(364)

nx.draw(g, node_size=[2 * (v+1) for v in val], node_color=[c for c in col])
plot.savefig("connected.png")
plot.clf()

# Display for ALL the nodes at random to show strongest shows
rval, rcol, rg = make_graph(4000)

e_c = input("Edge Color: ['white' / 'black' ]:")
if e_c == 'white' or e_c == 'black':
    pass
else:
    print("Bad edge color, defaulting to white")
    e_c = 'white'

nx.draw_random(rg, node_size=[2 * (rv+1) for rv in rval], node_color=[rc for rc in rcol], edge_color=e_c)
plot.savefig("jumbo.png")
plot.clf()
