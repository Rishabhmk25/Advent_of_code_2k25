#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ifstream inputFile("d4.txt");
  int ans = 0;
  vector<vector<int>> map;
  if (inputFile.is_open()) {
    string l;
    while (getline(inputFile, l)) {
      vector<int> line;
      for (char c : l) {
        if (c == '@') {
          line.push_back(1);
        } else {
          line.push_back(0);
        }
      }
      map.push_back(line);
    }
    int length = map.size();
    int width = map[0].size();
    for (int i = 0; i < length - 1; i++) {
      for (int j = 1; j < width - 1; j++) {
        if (map[i][j] >= 1) {
          if (map[i][j + 1] >= 1) {
            map[i][j]++;
            map[i][j + 1]++;
          }
          if (map[i + 1][j] >= 1) {
            map[i][j]++;
            map[i + 1][j]++;
          }
          if (map[i + 1][j + 1] >= 1) {
            map[i][j]++;
            map[i + 1][j + 1]++;
          }
          if (map[i + 1][j - 1] >= 1) {
            map[i][j]++;
            map[i + 1][j - 1]++;
          }

          // FIX 1: Skip checking column 1 (j=1) here.
          // It hasn't received updates from column 0 yet.
          if (j != 1 && map[i][j] < 5) {
            ans++;
            // cout << i << ' ' << j << endl;
          }
        } else {
          continue;
        }
      }
      if (map[i][0] >= 1) {
        if (map[i + 1][0] >= 1) {
          map[i][0]++;
          map[i + 1][0]++;
        }
        if (map[i + 1][1] >= 1) {
          map[i][0]++;
          map[i + 1][1]++;
        }
        if (map[i][1] >= 1) {
          map[i][0]++;
          map[i][1]++;
        }
        if (map[i][0] < 5) {
          ans++;
          // cout << i << ' ' << 0 << endl;
        }
      }

      // FIX 2: Check column 1 (j=1) here, after it has been updated by column
      // 0.
      if (map[i][1] >= 1 && map[i][1] < 5) {
        ans++;
      }

      if (map[i][width - 1] >= 1) {
        if (map[i + 1][width - 1] >= 1) {
          map[i][width - 1]++;
          map[i + 1][width - 1]++;
        }
        if (map[i + 1][width - 2] >= 1) {
          map[i][width - 1]++;
          map[i + 1][width - 2]++;
        }
        if (map[i][width - 1] < 5) {
          ans++;
          // cout << i << ' ' << width - 1 << endl;
        }
      }
    }
    for (int j = 0; j < width - 1; j++) {
      if (map[length - 1][j] >= 1) {
        if (map[length - 1][j + 1] >= 1) {
          map[length - 1][j]++;
          map[length - 1][j + 1]++;
        }
        if (map[length - 1][j] < 5) {
          ans++;
          // cout << length - 1 << ' ' << j << endl;
        }
      }
    }

    // FIX 3: Check the bottom-right corner, which was previously skipped.
    if (map[length - 1][width - 1] >= 1 && map[length - 1][width - 1] < 5) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}