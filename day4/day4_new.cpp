#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int paper_count(vector<vector<int>> map) {
  int ans = 0;
  int lenght = map.size();
  int width = map[0].size();
  for (int i = 0; i < lenght; i++) {
    for (int j = 0; j < width; j++) {
      if (map[i][j] < 5 && map[i][j] != 0) {
        ans++;
      }
    }
  }
  return ans;
}

vector<vector<int>> paper_remove(vector<vector<int>> map) {
  int length = map.size();
  int width = map[0].size();
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < width; j++) {
      if (map[i][j] >= 5) {
        map[i][j] = 1;
      } else {
        map[i][j] = 0;
      }
    }
  }
  return map;
}

vector<vector<int>> paper_check(vector<vector<int>> map) {
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
    }
  }
  for (int j = 0; j < width - 1; j++) {
    if (map[length - 1][j] >= 1) {
      if (map[length - 1][j + 1] >= 1) {
        map[length - 1][j]++;
        map[length - 1][j + 1]++;
      }
    }
  }
  return map;
}

int main() {
  ifstream inputFile("d4.txt");
  int ans_1 = 0;
  int ans_2 = 0;
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
    map = paper_check(map);
    ans_1 += paper_count(map);
    while(paper_count(map) != 0)
    {
     ans_2 += paper_count(map);
     map = paper_remove(map);
     map = paper_check(map);
     //cout << ans_2 << endl;
    }
  }
  cout << ans_1 << endl;
  cout << ans_2 << endl;
  return 0;
}
