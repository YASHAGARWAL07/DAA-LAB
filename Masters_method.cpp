#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    double a, b;

    // k → power of n (like in n^k)
    // p → power of log n (like in (log n)^p)
    double k = 0, p = 0;

    string str;

    cout << "Master's Theorem Solver\n";
    cout << "T(n) = aT(n/b) + f(n)\n\n";

    cout << "Enter value of a: ";
    cin >> a;

    cout << "Enter value of b: ";
    cin >> b;

    cout << "Enter function f(n) (e.g., 1, logn, n, n^2, nlogn, n^2logn): ";
    cin >> str;

    // -------- Step 1: Identify type of function --------

    // if f(n) = 1 (constant)
    if (str == "1")
    {
        k = 0;
        p = 0;
    }

    // if f(n) = log n
    else if (str == "logn")
    {
        k = 0;  // no n term
        p = 1;  // log^1 n
    }

    else
    {
        // -------- Step 2: Extract power of n --------
        // Example: n^2 → k = 2
        //          n   → k = 1

        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == 'n')
            {
                if (i + 1 < str.length() && str[i + 1] == '^')
                    k = str[i + 2] - '0';  // assuming single digit power
                else
                    k = 1;

                break;
            }
        }

        // -------- Step 3: Extract power of log --------
        // Example: logn → p = 1
        //          log^2 n → p = 2

        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == 'l') // detecting "log"
            {
                if (i + 3 < str.length() && str[i + 3] == '^')
                    p = str[i + 4] - '0';
                else
                    p = 1;

                break;
            }
        }
    }

    // -------- Step 4: Calculate log_b(a) --------
    double logba = log(a) / log(b);

    cout << "\nlog_b(a) = " << logba << endl;
    cout << "Detected form: n^" << k << " * (log n)^" << p << endl;

    // -------- Step 5: Compare growth --------
    // We compare:
    // n^k (log n)^p  vs  n^(log_b(a))

    // IMPORTANT:
    // Comparison mainly depends on k (power of n)
    // log terms are secondary

    if (k > logba)
    {
        // f(n) grows faster → Case 3
        cout << "\nCase 3 applies (f(n) dominates).\n";
        cout << "T(n) = Theta(n^" << k;

        if (p > 0)
            cout << " (log n)^" << p;

        cout << ")\n";
    }
    else if (abs(k - logba) < 0.0001)
    {
        // equal growth → Case 2
        cout << "\nCase 2 applies.\n";
        cout << "T(n) = Theta(n^" << k << " (log n)^" << (p + 1) << ")\n";
    }
    else
    {
        // recursion dominates → Case 1
        cout << "\nCase 1 applies.\n";
        cout << "T(n) = Theta(n^" << logba << ")\n";
    }

    return 0;
}
