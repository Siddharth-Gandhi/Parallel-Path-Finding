#include <bits/stdc++.h>
using namespace std;

void print_distance_matrix(vector<vector<int>> matrix) {
    int n = matrix.size();
    assert(n > 0 && (matrix.size() == matrix[0].size()));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> generate_random_distance_matrix(int N) {
    vector<vector<int>> matrix(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (i == j) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = matrix[j][i] = rand() % 100 + 1;
            }
        }
    }
    return matrix;
}

int main() {
    int N = 5;
    cout << "Enter the size of distance matrix (N x N): ";
    cin >> N;
    vector<vector<int>> matrix = generate_random_distance_matrix(N);
    print_distance_matrix(matrix);
}