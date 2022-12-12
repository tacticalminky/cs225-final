# cs225-final

Final Project for CS 225

We aim to create a graph from [Anime Recommendations Database](https://www.kaggle.com/datasets/CooperUnion/anime-recommendations-database) that you can use to recommend anime similiar to a provide name, id, or other criteria.

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

## Organization

Main C++ file is in the `entry` directory

C++ header and source files are in the `src` directory

Test source file is in the `tests` directory

Our data sets and python graphing scripts are in the `data` directory

## Tests Suite

### Test Instructions

1. Follow the build instructions as described above.

2. Make the tests and run it with the following command:

    ```bash
    make test
    ./test
    ```

### Tests
