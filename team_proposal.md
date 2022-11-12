## Leading Question 
The purpose of our code base is to provide a list of anime recommendations.  We will store a collection of anime as nodes in a graph connected by shared viewers.  The user will input the name of a show or a list of desired traits.  Our algorithms will first find the anime that most closely matches the inputs.  It will then generate a list of recommendations by traversing the weighted edges of the graph starting at that anime.  Additionally, printing the graph will allow us to see clusters of anime that are watched by the same people.

## Dataset Acquisition

### Data Format
We will be using the "Anime" and "Ratings" CSV files from the [Anime Recommendations Database](https://www.kaggle.com/datasets/CooperUnion/anime-recommendations-database).  The "Anime" CSV contains 12,294 entries, each consisting of anime id, name, genre, type, episodes, rating, and members.  We will only be using anime of type "TV" (3,804 entries).  The "Ratings" CSV contains 7,813,737 entries, each consisting of user id, anime id, and rating.  We will only be using user id and anime id, and only entries that have corresponding anime ids in the filtered "Anime" CSV by using a script to delete unwanted entries (5,283,600 entries).

### Data Correction
The filtered "Anime" CSV will be parsed line by line.  The data for each anime will be separated using comma delimitation.  Missing data is represented in the CSV as an empty string between commas, and will be replaced by a default value if encountered.  The "Ratings" CSV will also be parsed by line and comma-delimited.  Data that includes an anime id not found in our filtered "Anime" CSV will removed by a script during the acquisition process.  The only other error that can cause issue is a missing user id, which we will handle by ignoring that line.

### Data Storage
The data from both CSVs will be stored in a map of nodes to adjacency list.  Each anime in the "Anime" CSV will be represented by a single node structure.  The node will store the anime id, name, genre, type, episodes, rating, and members.  The data from the "Reviews" CSV will be used to create weighted edges between the nodes.  Nodes will contain an edge if the same person has reviewed both anime, and the weight of the edge will be the number of people who have reviewed both anime.  The adjacency list will be a map from the adjacent node to the weight.  If the number of anime is n, and the number of edges each one has is degree v, then the map will have size O(n) and the adjacency list will have size O(degree v).  The graph as a whole will therefore have size O(n * degree v).

We will also store pointers to the nodes in a KDTree, with each dimension being one of the data pointers stored in the node structure.  The tree has one node for every anime, so will have size O(n).

## Algorithm 
We will find the starting node of our traversal with a Find Nearest Neighbor algorithm.  The algorithm will take as input the current dimension, the current node, and a list of characteristics corresponding to each of the elements in the node structure, with default values being used for blanks.  An overloaded function will also take in vector of nodes to be ignored.  Dimensions containing integers will compare distance, while dimensions containing strings will only look to match the string.  The algorithm will output a pointer to the node that most closely matches the inputted preferences.  The KDTree will be constructed in O(n*logn) time and take up O(n) space.  Find Nearest Neighbor will take on average O(logn) time (at worst O(n*logn)) and will take up O(1) space.

We will create a recommendations list of 10 anime using a modified Dijkstra's Algorithm.  The algorithm will take a starting node as input.  It will traverse the graph using the highest weighted edge from all visited nodes to unvisited nodes, stopping once 10 nodes have been visited.  In the event that there are no more connected nodes, it will call Find Nearest Neighbor on the last node and pass in the visited nodes to be ignored.  The algorithm will output the list of visited nodes, in the order that they were visited.  Since we prematurely stop the algorithm after 10 nodes, the time complexity is O(10*degree v) = O(degree v).  At the worst case, Find Nearest Neighbor is called 10 times for a time complexity of O(10*logn) = O(log n) (or O(n*logn) at the very worst).  The algorithm stores a list of 10 visited nodes, which take up O(10) = O(1) space.

## Timeline
Week 1 - Data acquisition and trimming, outline of graph structure and algorithms

Week 2 - Finish data adjustment, create node structure, revise project proposal

Week 3 - Write adjacency list and KDTree creation - [Mid Project Check-In]

Week 4 - Write Find Nearest Neighbor and Dijkstra's Algorithm

Week 5 - Clean up and optimize code, display the graph

Week 6 - Verify Big-O analysis of code matches target, written report

Week 7 - Prep for presentation
