#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib> // for system("clear")

using namespace std;

// Function to clear the console
void clearConsole() {
    system("clear"); // ANSI escape code to clear the console
}

// Check if it is possible to go to (x, y) from the current position. The
// function returns false if the cell has value 0 or is already visited
bool isSafe(vector<vector<int>> &mat, vector<vector<bool>> &visited, int x, int y) {
    return (x >= 0 && x < mat.size() && y >= 0 && y < mat[0].size()) && mat[x][y] == 1 && !visited[x][y];
}

void printMaze(vector<vector<int>> &mat, vector<vector<bool>> &path) {
    clearConsole();  // Clear the console before printing
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            if (path[i][j])
                cout << "* ";
            else
                cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void findShortestPathDFS(vector<vector<int>> &mat, vector<vector<bool>> &visited, vector<vector<bool>> &path, int i, int j, int x, int y, int &min_dist, int dist);

int findShortestPathLengthDFS(vector<vector<int>> &mat, pair<int, int> &src, pair<int, int> &dest) {
    if (mat.size() == 0 || mat[src.first][src.second] == 0 || mat[dest.first][dest.second] == 0)
        return -1;

    int row = mat.size();
    int col = mat[0].size();
    // Construct an M × N matrix to keep track of visited cells
    vector<vector<bool>> visited;
    visited.resize(row, vector<bool>(col));
    vector<vector<bool>> path;
    path.resize(row, vector<bool>(col));

    int dist = INT_MAX;
    findShortestPathDFS(mat, visited, path, src.first, src.second, dest.first, dest.second, dist, 0);

    if (dist != INT_MAX)
        return dist;
    return -1;
}

void findShortestPathDFS(vector<vector<int>> &mat, vector<vector<bool>> &visited, vector<vector<bool>> &path, int i, int j, int x, int y, int &min_dist, int dist) {
    if (i == x && j == y) {
        if (dist < min_dist) {
            min_dist = dist;
            path[i][j] = true; // Mark this cell as part of the shortest path
            printMaze(mat, path); // Print the maze with the shortest path
            path[i][j] = false; // Unmark the cell for backtracking
        }
        return;
    }
    // Set (i, j) cell as visited
    visited[i][j] = true;
    path[i][j] = true;

    // Go to the bottom cell
    if (isSafe(mat, visited, i + 1, j)) {
        findShortestPathDFS(mat, visited, path, i + 1, j, x, y, min_dist, dist + 1);
    }
    // Go to the right cell
    if (isSafe(mat, visited, i, j + 1)) {
        findShortestPathDFS(mat, visited, path, i, j + 1, x, y, min_dist, dist + 1);
    }
    // Go to the top cell
    if (isSafe(mat, visited, i - 1, j)) {
        findShortestPathDFS(mat, visited, path, i - 1, j, x, y, min_dist, dist + 1);
    }
    // Go to the left cell
    if (isSafe(mat, visited, i, j - 1)) {
        findShortestPathDFS(mat, visited, path, i, j - 1, x, y, min_dist, dist + 1);
    }
    // Backtrack: remove (i, j) from the visited matrix and path
    visited[i][j] = false;
    path[i][j] = false;
}

int findShortestPathLengthBFS(vector<vector<int>> &mat, pair<int, int> &src, pair<int, int> &dest) {
    if (mat.size() == 0 || mat[src.first][src.second] == 0 || mat[dest.first][dest.second] == 0)
        return -1;

    int row = mat.size();
    int col = mat[0].size();

    // Create a queue for BFS
    queue<pair<int, int>> q;

    // Create a visited matrix and initialize all cells as not visited
    vector<vector<bool>> visited;
    visited.resize(row, vector<bool>(col, false));
    vector<vector<bool>> path;
    path.resize(row, vector<bool>(col, false));

    // Mark the source cell as visited and enqueue it
    visited[src.first][src.second] = true;
    q.push(src);

    // Arrays to move in all 4 directions (right, left, up, and down)
    int rowMove[] = {1, -1, 0, 0};
    int colMove[] = {0, 0, 1, -1};

    int dist = 0;

    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            pair<int, int> curr = q.front();
            q.pop();

            if (curr.first == dest.first && curr.second == dest.second) {
                // Print the maze when the destination is reached
                printMaze(mat, path);
                return dist;
            }

            // Move in all four directions
            for (int i = 0; i < 4; i++) {
                int newRow = curr.first + rowMove[i];
                int newCol = curr.second + colMove[i];

                // If this cell is a valid move, mark it as visited and enqueue it
                if (newRow >= 0 && newRow < row && newCol >= 0 && newCol < col && mat[newRow][newCol] == 1 && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    path[newRow][newCol] = true;
                    q.push(make_pair(newRow, newCol));
                }
            }
        }
        dist++;
    }

    return -1; // If the destination cannot be reached
}

int main() {
    vector<vector<int>> mat = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    pair<int, int> src = make_pair(0, 0);  // Give Source and destination here
    pair<int, int> dest = make_pair(9, 9);

    cout << "Choose the algorithm (1 for DFS, 2 for BFS): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        // Use DFS
        clock_t start_time = clock();
        int dist = findShortestPathLengthDFS(mat, src, dest);
        clock_t end_time = clock();
        double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

        if (dist != -1)
            cout << "Shortest Path using DFS is " << dist << " (Time taken: " << elapsed_time << " seconds)" << endl;
        else
            cout << "Shortest Path doesn't exist." << endl;
    } else if (choice == 2) {
        // Use BFS
        clock_t start_time = clock();
        int dist = findShortestPathLengthBFS(mat, src, dest);
        clock_t end_time = clock();
        double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

        if (dist != -1)
            cout << "Shortest Path using BFS is " << dist << " (Time taken: " << elapsed_time << " seconds)" << endl;
        else
            cout << "Shortest Path doesn't exist." << endl;
    } else {
        cout << "Invalid choice. Please select 1 for DFS or 2 for BFS." << endl;
    }

    return 0;
}
