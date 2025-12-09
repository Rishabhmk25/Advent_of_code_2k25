#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<long long int> split(string line, char delimeter) {
  vector<long long int> nums;
  string s;
  istringstream sStream(line);
  while (getline(sStream, s, delimeter)) {
    if (!line.empty()) {
      long long a = stoll(s);
      nums.push_back(a);
    }
  }
  return nums;
}

int main() {
  ifstream inputFile("d5.txt");
  int ans_1 = 0;
  long long ans_2 = 0;
  vector<pair<long long, long long>> ranges;
  vector<long long int> ids;
  if (inputFile.is_open()) {
    string line;
    while (getline(inputFile, line)) {
      if (line.empty())
        continue;
      if (line.find('-') != string::npos) {
        vector<long long int> v = split(line, '-');
        ranges.push_back({v[0], v[1]});
      } else {
        long long id = stoll(line);
        ids.push_back(id);
      }
    }
    for (long long int id : ids) {
      for (const auto &range : ranges) {
        if (id >= range.first && id <= range.second) {
          ans_1++;
          break;
        }
      }
    }
    sort(ranges.begin(), ranges.end());
    vector<pair<long long, long long>> merged_ranges;
    if (!ranges.empty()) {
      merged_ranges.push_back(ranges[0]);
      for (size_t i = 1; i < ranges.size(); ++i) {
        if (ranges[i].first <= merged_ranges.back().second + 1) {
          merged_ranges.back().second =
              max(merged_ranges.back().second, ranges[i].second);
        } else {
          merged_ranges.push_back(ranges[i]);
        }
      }
    }

    for (const auto &range : merged_ranges) {
      ans_2 += (range.second - range.first + 1);
    }
  }
  cout << ans_1 << endl;
  cout << ans_2 << endl;
  return 0;
}
