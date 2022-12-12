# Final Project for CS 225

We aim to create a graph from [Anime Recommendations Database](https://www.kaggle.com/datasets/CooperUnion/anime-recommendations-database) that you can use to recommend anime similiar to a provide name, id, or other criteria. A video presentation of our project can be found [here](https://www.youtube.com/watch?v=V6yvvtxJ_vg).

## Instructions

### Main program

1. Make the build directory and create the make file

    ```bash
    mkdir build
    cd build
    cmake ..
    ```

2. Run the make command to compile the program and then run the program.

    ```bash
    make main
    ./main
    ```

3. Once everything is loaded in the program, you will be prompted if you want to search for an anime.

4. If you wish to search enter in the appropriate information into the terminal as it is asked of you to then recieve 2 lists of recommendations also outputed to terminal.

### Graphical output

1. Install Dependencies

    ```bash
    python3 -m pip install mayplotlib scipy networkx
    ```

2. You must run the main program at least once to create output-graph.csv

3. Then run the program from the projects root folder.

    ```bash
    python3 ./data/csv_grapher.py
    ```

### Tests

1. Follow the build instructions as described above.

2. Make the tests and run it with the following command:

    ```bash
    make test
    ./test
    ```

## Test Suite

We wrote test cases to test each main function in our code. We used a smaller CSV to test our code at first so it was easier to debug and find problems in our code. We had a test case that made sure that the CSV for ratings and animes was read and traslated into nodes and edges correctly. We made sure to test edge cases like handling empty strings correctly. We then tested that our make graph created the graph correctly by making sure that select edges had the correct weight and that edges were formed between the right nodes. There are also test cases that test that our adjacency list was populated correctly and some cases that ensured that we implemented our modified version of Prim's Algorithm correctly to find the 10 closest related animes when provided an anime. Our find nearest neighbor algorithm used different ways of calculating distance for each dimension, and our test cases accounted for this when determining which node to return. We then have test cases to make sure that our graph is traversed in the right way using DFS.

## Organization

Main C++ file is in the `entry` directory

C++ header and source files are in the `src` directory

Test source file is in the `tests` directory

Our data sets and python graphing scripts are in the `data` directory
