### Maze Solver Documentation

#### Overview
This program solves a maze using Depth-First Search (DFS) and Breadth-First Search (BFS) algorithms to find the shortest path from a source cell to a destination cell.

#### Features
- **DFS Algorithm** for pathfinding.
- **BFS Algorithm** for pathfinding.
- **Console Visualization** of the maze and path.

#### Requirements
- C++11 or higher.
- Standard libraries: `iostream`, `vector`, `queue`, `stack`, `ctime`, `cstdlib`.

#### Compilation
```bash
g++ maze_solver.cpp -o maze_solver
```

#### Execution
```bash
./maze_solver
```

#### Input
- The maze is defined as a 2D vector `mat` in the `main` function.
- Source (`src`) and destination (`dest`) coordinates are specified in the `main` function.

#### Output
- Shortest path length and computation time.
- Visual representation of the maze with the path marked with `*`.
- Message if no path exists.

#### Usage Instructions
1. **Run the program** and choose the algorithm:
   - Enter `1` for DFS.
   - Enter `2` for BFS.
2. **View the output** for the shortest path and time taken. If no path exists, a message will be displayed.

#### Example
- Source: (0, 0)
- Destination: (9, 9)
- Choose algorithm: `1` or `2` based on preference.
