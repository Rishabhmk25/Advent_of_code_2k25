#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Count how many papers are removable in the current state
int paper_count(vector<vector<int>> map) {
  int ans = 0;
  int length = map.size();
  int width = map[0].size();
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < width; j++) {
      // A paper is represented by a value >= 10.
      // Neighbors add 1 to the value.
      // So a paper with < 4 neighbors will have value 10, 11, 12, or 13.
      if (map[i][j] >= 10 && map[i][j] < 14) {
        ans++;
      }
    }
  }
  return ans;
}

// Remove papers that are accessible and reset the counts for the next round
vector<vector<int>> paper_remove(vector<vector<int>> map) {
  int length = map.size();
  int width = map[0].size();
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < width; j++) {
      // If it's a paper (>= 10) AND has < 4 neighbors (< 14)
      if (map[i][j] >= 10 && map[i][j] < 14) {
        map[i][j] = 0; // Remove it
      }
      // If it's a paper with >= 4 neighbors (>= 14)
      else if (map[i][j] >= 14) {
        map[i][j] = 10; // Keep it, reset to base value 10
      }
      // If it's empty space (0-8), ensure it stays 0
      else {
        map[i][j] = 0;
      }
    }
  }
  return map;
}

// Update the map with neighbor counts
// Papers "push" counts to their neighbors
vector<vector<int>> paper_check(vector<vector<int>> map) {
  int length = map.size();
  int width = map[0].size();

  // We need a copy or we need to be careful.
  // Since we are adding counts, and we only care if the source is a PAPER
  // (>=10), and adding 1 won't change a non-paper to >=10 (max empty is 8), we
  // can modify in place IF we are careful not to use the *new* values to
  // trigger more pushes. But wait, if I increment a neighbor, it might cross a
  // threshold? No, we only check `if (map[i][j] >= 10)`. An empty cell (0) can
  // at most become 8. So it will never trigger the check. A paper (10) can
  // become 18. It still triggers. So in-place modification is SAFE for
  // "pushing", provided we don't double count. BUT, if we iterate and modify,
  // the `map[i][j]` we check is the *current* value. That value might have been
  // incremented by a previous neighbor. That's fine! We just need to know if it
  // IS a paper. `if (map[i][j] >= 10)` is stable because papers stay >= 10 and
  // empty stays < 10.

  // However, we must use a temporary grid for the *increments* if we want to be
  // purely safe, or just iterate and add to a copy. Let's use a copy to be
  // perfectly safe and clear.

  vector<vector<int>> next_map = map;

  for (int i = 0; i < length; i++) {
    for (int j = 1; j < width - 1; j++) {
      // Check if CURRENT cell is a paper
      if (map[i][j] >= 10) {
        // Increment all 8 neighbors in next_map
        // Top row
        if (i > 0) {
          next_map[i - 1][j - 1]++;
          next_map[i - 1][j]++;
          next_map[i - 1][j + 1]++;
        }
        // Middle row
        next_map[i][j - 1]++;
        next_map[i][j + 1]++;
        // Bottom row
        if (i < length - 1) {
          next_map[i + 1][j - 1]++;
          next_map[i + 1][j]++;
          next_map[i + 1][j + 1]++;
        }
      }
    }
    // Handle edges (Column 0)
    if (map[i][0] >= 10) {
      if (i > 0) {
        next_map[i - 1][0]++;
        next_map[i - 1][1]++;
      }
      next_map[i][1]++;
      if (i < length - 1) {
        next_map[i + 1][0]++;
        next_map[i + 1][1]++;
      }
    }
    // Handle edges (Last Column)
    if (map[i][width - 1] >= 10) {
      if (i > 0) {
        next_map[i - 1][width - 1]++;
        next_map[i - 1][width - 2]++;
      }
      next_map[i][width - 2]++;
      if (i < length - 1) {
        next_map[i + 1][width - 1]++;
        next_map[i + 1][width - 2]++;
      }
    }
  }
  return next_map;
}

int main() {
  ifstream inputFile("d4.txt"); // Using real input
  // ifstream inputFile("exd4.txt");

  long long ans_2 = 0; // Use long long for safety
  vector<vector<int>> map;

  if (inputFile.is_open()) {
    string l;
    while (getline(inputFile, l)) {
      vector<int> line;
      for (char c : l) {
        if (c == '@') {
          line.push_back(10); // Use 10 for Paper
        } else {
          line.push_back(0); // Use 0 for Empty
        }
      }
      map.push_back(line);
    }

    // Initial check to populate neighbor counts
    map = paper_check(map);

    while (true) {
      int removed_this_round = paper_count(map);
      if (removed_this_round == 0) {
        break;
      }
      ans_2 += removed_this_round;

      // Remove papers and reset counts
      map = paper_remove(map);

      // Recalculate counts for the new state
      map = paper_check(map);

      // cout << "Removed: " << removed_this_round << ", Total: " << ans_2 <<
      // endl;
    }
  }
  cout << ans_2 << endl;
  return 0;
}
