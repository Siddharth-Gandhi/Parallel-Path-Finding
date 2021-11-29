#include <bits/stdc++.h>

#include <chrono>

#include "parallel_bellman_ford.h"
#include "random_distance_matrix.h"
#include "serial_bellman_ford.h"

using namespace std;
using namespace std::chrono;

const int COUT_PRECISION = 16;
const int START_N = 100;
const int END_N = 1000;
const int STEP_N = 100;
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
    ofstream bellman_ford_time;
    cout << setprecision(COUT_PRECISION);

    bellman_ford_time.open("bellman_ford_time.csv");  // for [500, 25000] with increment of 500
    // bellman_ford_time.open("bellman_ford_time_small.csv"); // for [10,500] with increment of 10

    bellman_ford_time << "Number of nodes (N),Serial Time (us)";
    for (int num_thread : num_threads) {
        bellman_ford_time << ","
                          << "Parallel time with " << num_thread << " threads (us)";
    }
    bellman_ford_time << endl;

    printf(
        "Starting to calculate Bellman Ford's algorithm for number of nodes in the range [%d, %d] "
        "with an increment of %d\n",
        START_N, END_N, STEP_N);

    cout << "Also, testing for the following number of threads: " << num_threads << endl;

    for (int i = START_N; i <= END_N; i += STEP_N) {
        vector<vector<int>> matrix = generate_random_distance_matrix(i);
        // cout << "The randomly generated distance matrix is: \n";
        // print_distance_matrix(matrix);

        auto start = high_resolution_clock::now();
        vector<int> serial_shortest_path = serial_bellman_ford(matrix);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        bellman_ford_time << i << "," << duration.count();
        // cout << "The shortest path with Bellman Ford (Serial) is: " << serial_shortest_path << endl;

        for (int num_thread : num_threads) {
            start = high_resolution_clock::now();
            vector<int> parallel_dijkstra_path = parallel_bellman_ford(matrix, num_thread);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            bellman_ford_time << "," << duration.count();
            // cout << "The shortest path with Bellman Ford (Parallel with " << num_thread << " threads) is: " <<
            // parallel_dijkstra_path << endl;
        }
        bellman_ford_time << endl;
    }
    printf("Finished computations and the results are stored in bellman_ford_time.csv");
    return 0;
}