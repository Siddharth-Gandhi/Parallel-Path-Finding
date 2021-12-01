/*
 * This is a serial version of bellman_ford algorithm
 * Compile: g++ -std=c++11 -o serial_bellman_ford serial_bellman_ford.cpp
 * Run: ./serial_bellman_ford <input file>, you will find the output file 'output.txt'
 * */
#include <bits/stdc++.h>
#include <sys/time.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using std::cout;
using std::endl;
using std::string;

#define INF 1000000

// translate 2-dimension coordinate to 1-dimension
int convert_dimension_2D_1D(int x, int y, int n) { return x * n + y; }

vector<int> serial_bellman_ford(vector<vector<int>> matrix) {
    // initialize results
    int n = matrix.size();
    vector<int> mat(n * n);
    vector<int> dist(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[convert_dimension_2D_1D(i, j, n)] = matrix[i][j];
        }
    }
    // bool has_negative_cycle = false;
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    // root vertex always has distance 0
    dist[0] = 0;

    // a flag to record if there is any distance change in this iteration
    bool has_change;
    // bellman-ford edge relaxation
    for (int i = 0; i < n - 1; i++) {  // n - 1 iteration
        has_change = false;
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int weight = mat[convert_dimension_2D_1D(u, v, n)];
                if (weight < INF) {  // test if u--v has an edge
                    if (dist[u] + weight < dist[v]) {
                        has_change = true;
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }
        // if there is no change in this iteration, then we have finished
        if (!has_change) {
            return dist;
        }
    }

    // do one more iteration to check negative cycles
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            int weight = mat[convert_dimension_2D_1D(u, v, n)];
            if (weight < INF) {
                if (dist[u] + weight < dist[v]) {  // if we can relax one more step, then we find a negative cycle
                    // has_negative_cycle = true;
                    return dist;
                }
            }
        }
    }
    return dist;
}
