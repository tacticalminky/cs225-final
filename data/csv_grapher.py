# To be able to use this script, you need to
# a) pip install networkx
# b) pip install matplotlib
# c) pip install scipy
# if you don't already have these two. The simple solution is download the
# packages and run it in PyCharm if you dont wanna do it in terminal.
# Along with that, you have to make sure that the output-graph.csv is in the same folder as this
# python script for it to work, and then it will paste the final image in the same location.

# The code will ask for a user input, and the choices will be listed on screen. The default value will be white

import matplotlib.pyplot as plot
import networkx as nx
# import scipy
# We install scipy, but we don't need to import it explicitly, you can if you want but its not important
# All we require the scipy library is to be able to run these function on a larger # of nodes :)

# Take CSV -> Graph
def make_graph(iterations):
    # Open file
    print("Starting CSV Parsing")
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

        if len(delim_1) == 3:  # No related_ids
            parts = line.split(',')
            graph.add_node(parts[1])
            continue

        names = delim_1[3].split(',')
        curr_id = delim_1[0].split(',')[0]

        for x in range(0, len(names), 2):
            graph.add_edge(curr_id, names[x], edge_weight=(float(names[x + 1]) * 0.01))

    csv.close()

    # Make pretty
    print("CSV has been parsed, starting graph creation")
    deg = dict(graph.degree)
    vals = list(deg.values())
    cols = []

    color_map = {
        0: "blue",
        1: "grey",
        2: "brown",
        3: "yellow",
        4: "orange",
        5: "pink",
        6: "green",
        7: "red"
    }

    vals.sort()

    for v in vals:
        num = int(float(v) / 20.0)
        if num > 7:
            num = 7

        cols.append(color_map[num])

    print("Graph has been created")
    return [vals, cols, graph]


# Display for 364 nodes to show connected components
# This type of display maxes out at 364 nodes, hence the value
val, col, g = make_graph(1000)

plot.figure(figsize=(15, 15))
print("Drawing graph")
nx.draw(g, node_size=[(v + 1) * .75 for v in val], node_color=[c for c in col])
print("Completed :)")
plot.savefig("connected.png")
plot.clf()

# # Display for ALL the nodes at random to show strongest shows
# rval, rcol, rg = make_graph(4000)
#
# e_c = input("Edge Color: ['white' / 'black' ]:")
# if e_c == 'white' or e_c == 'black':
#     pass
# else:
#     print("Bad edge color, defaulting to white")
#     e_c = 'white'
#
# plot.figure(figsize=(25, 25))
# print("Drawing graph")
# nx.draw_random(rg, node_size=[2 * (rv + 1) for rv in rval], node_color=[rc for rc in rcol], edge_color=e_c)
# print("Completed :)")
# plot.savefig("jumbo.png")
# plot.clf()
