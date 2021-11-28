#include <bits/stdc++.h>

#include <chrono>

#include "random_distance_matrix.h"
#include "serial_dijkstra.h"

using namespace std;
using namespace std::chrono;

const int COUT_PRECISION = 16;

int main() {
    int N = 10;
    // cout << "Enter the size of distance matrix (N x N): ";
    // cin >> N;
    cout << "Time taken by serial Dijkstra's algorithm is: " << endl;
    cout << "N \t\t"
         << "Time taken" << endl;
    for (int i = 1; i <= N; ++i) {
        vector<vector<int>> matrix = generate_random_distance_matrix(N);
        // cout << "The randomly generated distance matrix is: \n";
        // print_distance_matrix(matrix);
        auto start = high_resolution_clock::now();
        vector<int> serial_shortest_path = serial_dijkstra(matrix, 0);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start) / 1.0e6;
        // cout.precision(COUT_PRECISION);
        cout << fixed << i << "\t\t" << duration.count() << " seconds" << endl;
    }
    return 0;
}