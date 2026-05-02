#include<iostream>
using namespace std;

#define INF 99999
#define V 4

// Floyd Warshall Algorithm
void floydWarshall(int dist[V][V]){

    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                
                if(dist[i][k] != INF && dist[k][j] != INF &&
                   dist[i][k] + dist[k][j] < dist[i][j]) {
                    
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

// Print in readable table format
void printMatrix(int dist[V][V]){
    cout << "\nAll-Pairs Shortest Path Matrix:\n\n";

    // Column headers
    cout << "\t";
    for(int i = 0; i < V; i++){
        cout << i << "\t";
    }
    cout << endl;

    for(int i = 0; i < V; i++){
        cout << i << "\t";  // Row header
        for(int j = 0; j < V; j++){
            if(dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

// Check negative cycle
void checkNegativeCycle(int dist[V][V]){
    for(int i = 0; i < V; i++){
        if(dist[i][i] < 0){
            cout << "\nNegative cycle detected!\n";
            return;
        }
    }
    cout << "\nNo negative cycle detected.\n";
}

int main(){

    int dist[V][V] = {
        {0,   3,   INF, 7},
        {8,   0,   2,   INF},
        {5,   INF, 0,   1},
        {2,   INF, INF, 0}
    };

    floydWarshall(dist);
    printMatrix(dist);
    checkNegativeCycle(dist);

    return 0;
}