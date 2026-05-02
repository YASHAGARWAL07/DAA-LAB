/*
 * Fractional Knapsack Problem - Greedy Approach
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(1)
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Item {
    int weight, value;
    double ratio; // value per unit weight
};

// Comparator to sort items by value/weight ratio (descending)
bool cmp(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(int capacity, vector<Item>& items) {
    // Sort items by value/weight ratio
    sort(items.begin(), items.end(), cmp);

    double totalValue = 0.0;
    int currentWeight = 0;

    for (auto& item : items) {
        if (currentWeight + item.weight <= capacity) {
            // Take the whole item
            currentWeight += item.weight;
            totalValue += item.value;
            cout << "Took full item | Weight: " << item.weight
                 << " | Value: " << item.value << "\n";
        } else {
            // Take the fraction of the remaining capacity
            int remaining = capacity - currentWeight;
            double fraction = (double)remaining / item.weight;
            totalValue += item.value * fraction;
            cout << "Took fraction (" << fraction << ") of item | Weight: "
                 << item.weight << " | Value: " << item.value << "\n";
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);
    cout << "Enter weight and value for each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " -> Weight: ";
        cin >> items[i].weight;
        cout << "         Value:  ";
        cin >> items[i].value;
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    cout << "\n--- Selection Process ---\n";
    double maxValue = fractionalKnapsack(capacity, items);

    cout << "\nMaximum value in knapsack = " << maxValue << "\n";

    return 0;
}
