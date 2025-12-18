#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

const double EPS = 1e-9; // Small value to handle floating-point precision issues

class LinearSystem {
private:
    vector<vector<double>> matrix; // Augmented matrix
    int n; // Number of equations

public:
    // Constructor to initialize the system
    LinearSystem(const vector<vector<double>> &augmentedMatrix) {
        matrix = augmentedMatrix;
        n = matrix.size();
    }

    // Function to perform Gaussian elimination
    vector<double> solve() {
        // Forward elimination
        for (int i = 0; i < n; i++) {
            // Find the row with the maximum element in the current column
            int maxRow = i;
            for (int k = i + 1; k < n; k++) {
                if (abs(matrix[k][i]) > abs(matrix[maxRow][i])) {
                    maxRow = k;
                }
            }

            // Swap the current row with the max row
            swap(matrix[i], matrix[maxRow]);

            // If the pivot element is zero, the system may have no unique solution
            if (abs(matrix[i][i]) < EPS) {
                throw runtime_error("No unique solution exists.");
            }

            // Make all rows below this one 0 in the current column
            for (int k = i + 1; k < n; k++) {
                double factor = matrix[k][i] / matrix[i][i];
                for (int j = i; j <= n; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }

        // Back substitution
        vector<double> solution(n);
        for (int i = n - 1; i >= 0; i--) {
            solution[i] = matrix[i][n] / matrix[i][i];
            for (int k = i - 1; k >= 0; k--) {
                matrix[k][n] -= matrix[k][i] * solution[i];
            }
        }

        return solution;
    }

    // Function to display the augmented matrix
    void displayMatrix() const {
        for (const auto &row : matrix) {
            for (double val : row) {
                cout << val << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    // Example system of equations:
    // 3x + 2y - 4z = 3
    // 2x + 3y + 3z = 15
    // 5x - 3y + z = 14
    vector<vector<double>> augmentedMatrix = {
        {3, 2, -4, 3},
        {2, 3, 3, 15},
        {5, -3, 1, 14}
    };
}
