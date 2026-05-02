#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std;

class Solution {
public:
    int count = 0;

    void solve(int n, int cols, int diag1, int diag2) {
        if (cols == (1 << n) - 1) {
            count++;
            return;
        }

        int available = ((1 << n) - 1) & ~(cols | diag1 | diag2);

        while (available) {
            int bit = available & -available;
            available -= bit;

            solve(n,
                  cols | bit,
                  (diag1 | bit) << 1,
                  (diag2 | bit) >> 1);
        }
    }

    int totalNQueens(int n) {
        count = 0;
        solve(n, 0, 0, 0);
        return count;
    }
};

int main() {
    int n;
    cout << "Enter value of n: ";
    cin >> n;

    Solution obj;

    // Start time
    auto start = chrono::high_resolution_clock::now();

    int result = obj.totalNQueens(n);

    // End time
    auto end = chrono::high_resolution_clock::now();

    // Time calculation (microseconds)
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Total Solutions: " << result << endl;
    cout << "Time Taken: " << duration.count() << " microseconds" << endl;

    return 0;
}