#include <iostream>
using namespace std;

/*
    Travelling Salesman Problem (TSP) using Bitmask + DP

    Idea:
    - Visit all cities exactly once and return to starting city (0)
    - Use bitmask to track visited cities
    - Use DP to avoid recomputation

    dp[mask][pos] → minimum cost to visit all cities in 'mask'
                    and currently at city 'pos'
*/

#define INF 99999
#define MAXN 10

int n;                          // number of cities
int dist[MAXN][MAXN];           // distance matrix
int dp[1024][MAXN];             // DP table (2^10 masks)

// Recursive TSP function
int tsp(int mask, int pos) {

    // Base case: all cities visited
    if (mask == (1 << n) - 1) {
        if (dist[pos][0] == INF) return INF;  // no path back
        return dist[pos][0];                  // return to start
    }

    // If already computed, return stored value
    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;

    // Try all cities
    for (int city = 0; city < n; city++) {

        // Check if city is not visited
        if ((mask & (1 << city)) == 0) {

            // Skip if no path exists
            if (dist[pos][city] == INF) continue;

            int newCost = dist[pos][city] +
                          tsp(mask | (1 << city), city);

            if (newCost < ans)
                ans = newCost;
        }
    }

    // Store result in DP table
    return dp[mask][pos] = ans;
}

int main() {

    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter distance matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    // Initialize DP table with -1
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }

    // Start from city 0 (mask = 1 means only city 0 is visited)
    int result = tsp(1, 0);

    cout << "\n-----------------------------------\n";

    if (result == INF)
        cout << "No possible tour exists.\n";
    else
        cout << "Minimum travelling cost = " << result << endl;

    cout << "-----------------------------------\n";

    return 0;
}