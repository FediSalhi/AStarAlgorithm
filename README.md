# A* Search Algorithm C++ Implementation
A* is an efficient search algorithm  used in many fields. Learn more about this algorithm on https://en.wikipedia.org/wiki/A*_search_algorithm .
This project is a C++ implementation of the algorithm. Given a 2D grid, start point, and a goal point, the algorithm generates a path connecting the start and the goal points and avoiding the obstacles. The grid should contain exactly one start point and one goal point. `grid1.txt`, `grid2.txt`, and `grid3.txt` files contain examples of 2D grids that can be used for the algorithm. The start point, goal point, and the obstacles are represented on the grid by `S`, `G`, and `|`, respectively. In the generated solution, the path will represented by `*` character.

There are 3 classes in the project:
- `Grid`: This class contains the methods used to read the grid from a text file and check if it's a valid grid (e.g. a grid that doesn't contain a goal point isn't a valid grid).
- `Node`: A node is a point from the grid (i.e. has `x` and `y` coordinates) that has a `g`, `h`, and `f` values. Refer to https://en.wikipedia.org/wiki/A*_search_algorithm to understand what these values are used for.
- `AStarSearch` This class contains the main search algorithm and some helper methods.

## Build and Run (Linux)
The algorithm only uses the STL library. Make sure that you have `cmake` and `g++` installed in your machine before building the project. You can check them using:
```
cmake --version
g++ --version
```
In case you don't have `cmake` and `g++` installed in your machine, you can install them as follows:
1. Refresh apt: `sudo apt update`
2. Install GCC (which contains g++): `sudo apt install build-essential`
3. Install cmake: `sudo apt install cmake`

To build the project, run these commands from within the project folder:
```
mkdir build
cd build
cmake ..
make
```
If the project is successfully built, `A_STAR_SEARCH_ALGORITHM` executable file will be created in the `build` folder. Run the program using this command:
```
./A_STAR_SEARCH_ALGORITHM
```
The program will read the `grid1.txt` file, generate and show the solution, as shown below:
```

=========== Input Grid ===========

S.....|.........................|..................
......|............................................
......|.........................|..................
......|.........................|..................
.|..............................|.............|....
.|.....................|........|.............|....
......|................|........|.............|....
......|................|........|.............|....
......|................|........|.............|....
......|................|........|.............|....
......|................|........|..................
......|...................................G........
......|............................................
......|.........................|..................
......|.........................|..................
......|.........................|..................
......|.........................|..................
......|.........................|.........|........
......|...................................|........


=========== Solution ===========

S*****|.........................|..................
.....*|............................................
.....*|.........................|..................
.....*|.........................|..................
.|...***************************|.............|....
.|.....................|.......*|.............|....
......|................|.......*|.............|....
......|................|.......*|.............|....
......|................|.......*|.............|....
......|................|.......*|.............|....
......|................|.......*|..................
......|........................***********G........
......|............................................
......|.........................|..................
......|.........................|..................
......|.........................|..................
......|.........................|..................
......|.........................|.........|........
......|...................................|........


```

Please contact me if you have any suggestion about the algorithm implementation.

## Authors

* **Fedi Salhi** [FediSalhi](https://github.com/FediSalhi)

