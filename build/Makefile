CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic
LIBS = -I../include

MAIN = ../entry/main.cpp
# Add src files here
_SRC = ../src/anime_graph.cpp
SRC = $(patsubst %,../src/%,$(_SRC))

all: main

main: $(MAIN) $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f main

.DEFAULT_GOAL := all
.PHONY := all clean