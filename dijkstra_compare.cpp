#include <bits/stdc++.h>

#include <chrono>

#include "parallel_dijkstra.h"
#include "random_distance_matrix.h"
#include "serial_dijkstra.h"

using namespace std;
using namespace std::chrono;

const int COUT_PRECISION = 16;
const int START_N = 1000;
const int END_N = 20000;
const int STEP_N = 1000;

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
    out << "{";
    size_t last = v.size() - 1;
    for (size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last)
            out << ", ";
    }
    out << "}";
    return out;
}

int main() {
    // int N = 10000;
    // cout << "Enter the size of distance matrix (N x N): ";
    // cin >> N;
    ofstream serial_csv;
    ofstream parallel_csv2;
    ofstream parallel_csv4;
    ofstream parallel_csv6;
    ofstream parallel_csv8;
    ofstream parallel_csv10;
    ofstream parallel_csv12;

    serial_csv.open("csv/serial_time.csv");
    parallel_csv2.open("csv/parallel_time_2_threads.csv");
    parallel_csv4.open("csv/parallel_time_4_threads.csv");
    parallel_csv6.open("csv/parallel_time_6_threads.csv");
    parallel_csv8.open("csv/parallel_time_8_threads.csv");
    parallel_csv10.open("csv/parallel_time_10_threads.csv");
    parallel_csv12.open("csv/parallel_time_12_threads.csv");

    serial_csv << "N,Time(ms)" << endl;
    parallel_csv2 << "N,Time(ms)" << endl;
    parallel_csv4 << "N,Time(ms)" << endl;
    parallel_csv6 << "N,Time(ms)" << endl;
    parallel_csv8 << "N,Time(ms)" << endl;
    parallel_csv10 << "N,Time(ms)" << endl;
    parallel_csv12 << "N,Time(ms)" << endl;

    // cout << "Time taken by serial Dijkstra's algorithm is: " << endl;
    // cout << "N \t\t"
    //      << "Time taken" << endl;

    for (int i = START_N; i <= END_N; i += STEP_N) {
        vector<vector<int>> matrix = generate_random_distance_matrix(i);
        // cout << "The randomly generated distance matrix is: \n";
        // print_distance_matrix(matrix);

        auto start = high_resolution_clock::now();
        vector<int> serial_shortest_path = serial_dijkstra(matrix, 0);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        serial_csv << i << "," << duration.count() << endl;

        start = high_resolution_clock::now();
        vector<int> parallel_dijkstra_path2 = parallel_dijkstra(matrix, 2);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        parallel_csv2 << i << "," << duration.count() << endl;

        start = high_resolution_clock::now();
        vector<int> parallel_dijkstra_path4 = parallel_dijkstra(matrix, 4);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        parallel_csv4 << i << "," << duration.count() << endl;

        start = high_resolution_clock::now();
        vector<int> parallel_dijkstra_path6 = parallel_dijkstra(matrix, 6);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        parallel_csv6 << i << "," << duration.count() << endl;

        start = high_resolution_clock::now();
        vector<int> parallel_dijkstra_path8 = parallel_dijkstra(matrix, 8);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        parallel_csv8 << i << "," << duration.count() << endl;

        start = high_resolution_clock::now();
        vector<int> parallel_dijkstra_path10 = parallel_dijkstra(matrix, 10);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        parallel_csv10 << i << "," << duration.count() << endl;

        start = high_resolution_clock::now();
        vector<int> parallel_dijkstra_path = parallel_dijkstra(matrix, 12);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        parallel_csv12 << i << "," << duration.count() << endl;
    }
    return 0;
}