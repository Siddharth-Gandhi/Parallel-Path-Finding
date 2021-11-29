#include <bits/stdc++.h>

#include <chrono>

#include "parallel_dijkstra.h"
#include "random_distance_matrix.h"
#include "serial_dijkstra.h"

using namespace std;
using namespace std::chrono;

const int COUT_PRECISION = 16;
const int START_N = 1000;
const int END_N = 10000;
const int STEP_N = 1000;
const vector<int> num_threads = {2, 4, 6, 8, 10, 12};

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
    out << "{";
    size_t last = v.size() - 1;
    for (size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last) out << ", ";
    }
    out << "}";
    return out;
}

int main() {
    // ofstream serial_csv;
    // ofstream parallel_csv;
    ofstream dijkstra_time;
    cout << setprecision(COUT_PRECISION);

    dijkstra_time.open("dijkstra_time.csv");

    // serial_csv.open("dijkstra_csv/serial_time.csv");
    // serial_csv << "N,Time(ms)";

    dijkstra_time << "Number of nodes (N),Serial Time (ms)";
    for (int num_thread : num_threads) {
        // dijkstra_time << "," << num_thread << " Threads Time(ms)";
        dijkstra_time << ","
                      << "Parallel time with " << num_thread << " threads (ms)";
    }
    dijkstra_time << endl;
    printf(
        "Starting to calculate Dijkstra's algorithm for number of nodes in the range [%d, %d] "
        "with an increment of %d\n",
        START_N, END_N, STEP_N);
    cout << "Also, testing for the following number of threads: " << num_threads << endl;
    for (int i = START_N; i <= END_N; i += STEP_N) {
        vector<vector<int>> matrix = generate_random_distance_matrix(i);
        // cout << "The randomly generated distance matrix is: \n";
        // print_distance_matrix(matrix);

        auto start = high_resolution_clock::now();
        vector<int> serial_shortest_path = serial_dijkstra(matrix, 0);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        // serial_csv << i << "," << duration.count() << endl;
        dijkstra_time << i << "," << duration.count();

        for (int num_thread : num_threads) {
            // string csv_path =
            //     "dijkstra_csv/parallel_time_" + to_string(num_thread) + "_threads.csv";
            // parallel_csv.open(csv_path);
            // parallel_csv << "N,Time(ms)" << endl;
            start = high_resolution_clock::now();
            vector<int> parallel_dijkstra_path = parallel_dijkstra(matrix, num_thread);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            // parallel_csv << i << "," << duration.count() << endl;
            dijkstra_time << "," << duration.count();
        }
        dijkstra_time << endl;
    }
    printf("Finished computations and the results are stored in dijkstra_time.csv");
    return 0;
}