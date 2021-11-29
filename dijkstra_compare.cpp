#include <bits/stdc++.h>

#include <chrono>

#include "parallel_dijkstra.h"
#include "random_distance_matrix.h"
#include "serial_dijkstra.h"

using namespace std;
using namespace std::chrono;

const int COUT_PRECISION = 16;
const int START_N = 500;
const int END_N = 10000;
const int STEP_N = 500;

int main() {
    int N = 10000;
    // cout << "Enter the size of distance matrix (N x N): ";
    // cin >> N;
    ofstream serial_csv;
    ofstream parallel_csv;

    serial_csv.open("serial_time.csv");
    parallel_csv.open("parallel_time.csv");

    serial_csv << "N,Time(ms)" << endl;
    parallel_csv << "N,Time(ms)" << endl;

    // cout << "Time taken by serial Dijkstra's algorithm is: " << endl;
    // cout << "N \t\t"
    //      << "Time taken" << endl;

    for (int i = START_N; i <= END_N; i += STEP_N) {
        vector<vector<int>> matrix = generate_random_distance_matrix(N);
        // cout << "The randomly generated distance matrix is: \n";
        // print_distance_matrix(matrix);

        auto start = high_resolution_clock::now();
        vector<int> serial_shortest_path = serial_dijkstra(matrix, 0);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        serial_csv << i << "," << duration.count() << endl;

        start = high_resolution_clock::now();
        vector<int> parallel_dijkstra_path = parallel_dijkstra(matrix);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        parallel_csv << i << "," << duration.count() << endl;
        // cout.precision(COUT_PRECISION);
        // cout << fixed << i << "\t\t" << duration.count() << " ms" << endl;
    }
    return 0;
}