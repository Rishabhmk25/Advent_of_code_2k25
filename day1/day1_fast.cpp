#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Reopen file as stdin for fast parsing if needed, or just assume input redirection
    // For this task, we'll read from "d1.txt" as per original code
    if (!freopen("d1.txt", "r", stdin)) {
        return 1;
    }

    int ans_1 = 0;
    int ans_2 = 0;
    int lock = 50;
    
    char prefix;
    int num;

    // Parse format: L68, R30, etc.
    // We can read the char, then the integer.
    // Since the input is one per line, we can just loop.
    while (cin >> prefix >> num) {
        ans_2 += num / 100;
        int rem = num % 100;

        if (prefix == 'L') {
            if (lock > 0 && lock - rem <= 0) {
                ans_2++;
            }
            lock -= rem;
            if (lock < 0) {
                lock += 100;
            }
        } else {
            lock += rem;
            if (lock >= 100) {
                lock -= 100;
                ans_2++;
            }
        }

        if (lock == 0) {
            ans_1++;
        }
    }

    cout << ans_1 << endl;
    cout << ans_2 << endl;

    return 0;
}
