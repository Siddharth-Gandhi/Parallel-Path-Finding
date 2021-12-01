/*
 * This is a openmp version of bellman_ford algorithm
 * Compile: g++ -std=c++11 -o openmp_bellman_ford openmp_bellman_ford.cpp
 * Run: ./openmp_bellman_ford <input file> <number of threads>, you will find the output file
 * 'output.txt'
 * */
#include <bits/stdc++.h>
#include <sys/time.h>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "omp.h"
// #include "serial_bellman_ford.h"
using namespace std;
using std::cout;
using std::endl;
using std::string;

#define INF 1000000

// translate 2-dimension coordinate to 1-dimension
int convert_dimension_2D_1D_(int x, int y, int n) { return x * n + y; }

/**
 * Bellman-Ford algorithm. Find the shortest path from vertex 0 to other vertices.
 * @param p number of processes
 * @param n input size
 * @param *mat input adjacency matrix
 * @param *dist distance array
 * @param *has_negative_cycle a bool variable to recode if there are negative cycles
 */
vector<int> parallel_bellman_ford(vector<vector<int>> matrix, int p) {
    int n = matrix.size();
    vector<int> mat(n * n);
    vector<int> dist(n);
    int local_start[p], local_end[p];
    // bool has_negative_cycle = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[convert_dimension_2D_1D_(i, j, n)] = matrix[i][j];
        }
    }
    // step 1: set openmp thread number
    omp_set_num_threads(p);

    // step 2: find local task range
    int ave = n / p;
#pragma omp parallel for
    for (int i = 0; i < p; i++) {
        local_start[i] = ave * i;
        local_end[i] = ave * (i + 1);
        if (i == p - 1) {
            local_end[i] = n;
        }
    }

    // step 3: bellman-ford algorithm
    // initialize distances
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    // root vertex always has distance 0
    dist[0] = 0;

    int iter_num = 0;
    bool has_change;
    bool local_has_change[p];
#pragma omp parallel
    {
        int my_rank = omp_get_thread_num();
        // bellman-ford algorithm
        for (int iter = 0; iter < n - 1; iter++) {
            local_has_change[my_rank] = false;
            for (int u = 0; u < n; u++) {
                for (int v = local_start[my_rank]; v < local_end[my_rank]; v++) {
                    int weight = mat[convert_dimension_2D_1D_(u, v, n)];
                    if (weight < INF) {
                        int new_dis = dist[u] + weight;
                        if (new_dis < dist[v]) {
                            local_has_change[my_rank] = true;
                            dist[v] = new_dis;
                        }
                    }
                }
            }
#pragma omp barrier
#pragma omp single
            {
                iter_num++;
                has_change = false;
                for (int rank = 0; rank < p; rank++) {
                    has_change |= local_has_change[rank];
                }
            }
            if (!has_change) {
                break;
                // return dist;
            }
        }
    }

    // do one more iteration to check negative cycles
    if (iter_num == n - 1) {
        has_change = false;
        for (int u = 0; u < n; u++) {
#pragma omp parallel for reduction(| : has_change)
            for (int v = 0; v < n; v++) {
                int weight = mat[u * n + v];
                if (weight < INF) {
                    if (dist[u] + weight < dist[v]) {  // if we can relax one more step, then we find a negative cycle
                        has_change = true;
                        ;  // return dist;
                    }
                }
            }
        }
        // has_negative_cycle = has_change;
    }
    return dist;
    // step 4: free memory (if any)
}
