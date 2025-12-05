#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ifstream inputFile("d1.txt");
  if (!inputFile.is_open()) {
    cerr << "Error opening d1.txt" << endl;
    return 1;
  }

  int ans_1 = 0;
  int ans_2 = 0;
  int lock = 50;

  string line;
  while (getline(inputFile, line)) {
    if (line.empty())
      continue;

    char direction = line[0];
    // Parse the number after the direction character
    int distance = stoi(line.substr(1));

    // Part 2: Count 0-crossings from full rotations (100 clicks = 1 full
    // rotation)
    ans_2 += distance / 100;

    int remainder = distance % 100;

    if (direction == 'L') {
      // Check if we cross or land on 0 during the remainder movement.
      // We count if we are currently at a positive position (> 0)
      // and the move takes us to or past 0 (lock - remainder <= 0).
      if (lock > 0 && lock - remainder <= 0) {
        ans_2++;
      }

      lock -= remainder;
      // Handle wrap-around for negative values
      if (lock < 0) {
        lock += 100;
      }
    } else { // direction == 'R'
      lock += remainder;
      // Handle wrap-around for values >= 100
      if (lock >= 100) {
        lock -= 100;
        ans_2++;
      }
    }

    // Part 1: Check if the dial points exactly at 0 after the rotation
    if (lock == 0) {
      ans_1++;
    }
  }

  cout << ans_1 << endl;
  cout << ans_2 << endl;

  return 0;
}
