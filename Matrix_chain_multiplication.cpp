#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

// Function to print optimal parenthesization
void printOptimal(int i, int j, vector<vector<int>> &split)
{
    if (i == j)
    {
        cout << "A" << i;
        return;
    }

    cout << "(";

    // left part
    printOptimal(i, split[i][j], split);

    // right part
    printOptimal(split[i][j] + 1, j, split);

    cout << ")";
}

// Function to print cost matrix
void printCostMatrix(vector<vector<long long>> &mat, int n)
{
    cout << "\nCost Matrix:\n";

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i > j)
                cout << "-\t";
            else
                cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

// Function to print split matrix
void printSplitMatrix(vector<vector<int>> &mat, int n)
{
    cout << "\nSplit Matrix:\n";

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i >= j)
                cout << "-\t";
            else
                cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

// Matrix Chain Multiplication
void matrixChain(vector<int> &p, int n)
{
    /*
    n = number of matrices

    p[] = dimension array
    Example:
    p = {10, 20, 30, 40}

    A1 = 10×20
    A2 = 20×30
    A3 = 30×40
    */

    vector<vector<long long>> cost(n + 1, vector<long long>(n + 1, 0));
    vector<vector<int>> split(n + 1, vector<int>(n + 1, 0));

    // L = chain length
    for (int L = 2; L <= n; L++)
    {
        for (int i = 1; i <= n - L + 1; i++)
        {
            int j = i + L - 1;
            cost[i][j] = LLONG_MAX;

            // try all split points
            for (int k = i; k < j; k++)
            {
                /*
                cost = left + right + multiplication cost
                multiplication cost = rows × common × columns
                = p[i-1] * p[k] * p[j]
                */

                long long curr = cost[i][k] + cost[k + 1][j]
                                 + (long long)p[i - 1] * p[k] * p[j];

                if (curr < cost[i][j])
                {
                    cost[i][j] = curr;
                    split[i][j] = k;
                }
            }
        }
    }

    cout << "\nMinimum Multiplication Cost: " << cost[1][n] << endl;

    cout << "Optimal Parenthesization: ";
    printOptimal(1, n, split);
    cout << endl;

    printCostMatrix(cost, n);
    printSplitMatrix(split, n);
}

// MAIN FUNCTION
int main()
{
    int n;

    cout << "Enter number of matrices: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Invalid input\n";
        return 0;
    }

    vector<int> p(n + 1);

    cout << "Enter dimensions array (size " << n + 1 << "):\n";

    for (int i = 0; i <= n; i++)
    {
        cin >> p[i];

        if (p[i] <= 0)
        {
            cout << "Invalid dimension\n";
            return 0;
        }
    }

    matrixChain(p, n);

    return 0;
}