#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream inputFile("d4.txt");
  if (!inputFile.is_open()) {
    cerr << "Error opening file" << endl;
    return 1;
  }

  vector<string> grid;
  string line;
  while (getline(inputFile, line)) {
    if (!line.empty()) {
      grid.push_back(line);
    }
  }

  int rows = grid.size();
  int cols = grid[0].size();
  int ans = 0;

  int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] == '@') {
        int neighbors = 0;
        for (int i = 0; i < 8; ++i) {
          int nr = r + dr[i];
          int nc = c + dc[i];
          if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
              grid[nr][nc] == '@') {
            neighbors++;
          }
        }
        if (neighbors < 4) {
          ans++;
        }
      }
    }
  }

  cout << "Correct Answer: " << ans << endl;
  return 0;
}
