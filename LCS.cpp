/*
 * Longest Common Subsequence (LCS) - Dynamic Programming
 * Time Complexity: O(m * n)
 * Space Complexity: O(m * n)
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Trace back through dp table to find the actual LCS string
string traceLCS(vector<vector<int>>& dp, string& X, string& Y, int m, int n) {
    string lcs = "";
    int i = m, j = n;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs = X[i - 1] + lcs; // Prepend character
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return lcs;
}

int lcs(string X, string Y) {
    int m = X.length();
    int n = Y.length();

    // dp[i][j] = LCS length of X[0..i-1] and Y[0..j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill dp table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Print the DP table
    cout << "\nDP Table (LCS lengths):\n";
    cout << "    ";
    for (char c : Y) cout << " " << c;
    cout << "\n";

    for (int i = 0; i <= m; i++) {
        if (i == 0) cout << "  ";
        else cout << X[i - 1] << " ";
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }

    // Trace back actual LCS string
    string lcsStr = traceLCS(dp, X, Y, m, n);
    cout << "\nLCS String: " << lcsStr << "\n";
    cout << "LCS Length: " << dp[m][n] << "\n";

    return dp[m][n];
}

int main() {
    string X, Y;

    cout << "Enter first string:  ";
    cin >> X;
    cout << "Enter second string: ";
    cin >> Y;

    lcs(X, Y);

    return 0;
}