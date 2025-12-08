#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Optimization: Use a padded grid to eliminate boundary checks.
// This is a common technique in competitive programming.
// It simplifies the logic and improves performance by removing branches.

int main() {
  // Fast I/O
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ifstream inputFile("d4.txt");
  if (!inputFile.is_open())
    return 1;

  vector<string> raw_grid;
  string line;
  while (getline(inputFile, line)) {
    if (!line.empty()) {
      raw_grid.push_back(line);
    }
  }

  if (raw_grid.empty())
    return 0;

  int R = raw_grid.size();
  int C = raw_grid[0].size();

  // 1. PADDING
  // Create a grid that is 2 larger in both dimensions.
  // Initialize with '.' (empty).
  // This creates a "safe border" around the data.
  vector<string> grid(R + 2, string(C + 2, '.'));

  // Copy the data into the center of the padded grid.
  // Data will be at indices [1..R][1..C]
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      grid[i + 1][j + 1] = raw_grid[i][j];
    }
  }

  int ans = 0;

  // Direction vectors for 8 neighbors
  int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  // 2. PROCESSING
  // Iterate only over the valid data range [1..R][1..C]
  for (int i = 1; i <= R; ++i) {
    for (int j = 1; j <= C; ++j) {
      if (grid[i][j] == '@') {
        int neighbors = 0;

        // Check all 8 neighbors.
        // NO boundary checks needed because of padding!
        for (int k = 0; k < 8; ++k) {
          if (grid[i + dr[k]][j + dc[k]] == '@') {
            neighbors++;
          }
        }

        if (neighbors < 4) {
          ans++;
        }
      }
    }
  }

  cout << ans << endl;
  return 0;
}
