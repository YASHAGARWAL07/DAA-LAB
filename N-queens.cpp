#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> board;
int solutionCount = 0;

void printBoard() {
    cout << "\n--- Solution " << solutionCount << " ---\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (board[i][j] ? " Q " : " . ");
        }
        cout << "\n";
    }
}

// Check if placing a queen at (row, col) is safe
bool isSafe(int row, int col) {
    // Check column above
    for (int i = 0; i < row; i++)
        if (board[i][col]) return false;

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j]) return false;

    return true;
}

// Backtracking function to solve N-Queens
void solve(int row) {
    if (row == n) {
        solutionCount++;
        printBoard();
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;   // Place queen
            solve(row + 1);        // Recurse to next row
            board[row][col] = 0;   // Backtrack
        }
    }
}

int main() {
    cout << "Enter the value of N (N-Queens): ";
    cin >> n;

    board.assign(n, vector<int>(n, 0));

    solve(0);

    if (solutionCount == 0)
        cout << "No solution exists for N = " << n << "\n";
    else
        cout << "\nTotal solutions found: " << solutionCount << "\n";

    return 0;
}
