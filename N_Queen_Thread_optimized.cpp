#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

atomic<long long> solution_count(0);

void nQueensBitPartialCount(int n, int row, int ld, int rd, int queens_placed) {
    if (queens_placed == n) {
        solution_count++;
        return;
    }

    int possible_positions = ((1 << n) - 1) & (~(row | ld | rd));

    while (possible_positions) {
        int p = possible_positions & (-possible_positions);
        possible_positions -= p;
        nQueensBitPartialCount(n, row | p, (ld | p) << 1, (rd | p) >> 1, queens_placed + 1);
    }
}

void solveNQueensThread(int n, int first_queen_col) {
    int initial_row = (1 << first_queen_col);
    nQueensBitPartialCount(n, initial_row, initial_row << 1, initial_row >> 1, 1);
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    int num_threads = thread::hardware_concurrency();
    cout << "Number of available threads: " << num_threads << endl;

    auto start_time = chrono::high_resolution_clock::now();

    vector<thread> threads;
    for (int i = 0; i < n; ++i) {
        threads.emplace_back(solveNQueensThread, n, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    cout << "Execution time : " << duration.count() << " milliseconds" << endl;
    cout << "Number of solutions: " << solution_count << endl;

    return 0;
}