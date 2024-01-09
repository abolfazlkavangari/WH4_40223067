#include <stdio.h>
#include <stdlib.h>

// تابع allocateMatrix
void allocateMatrix(int rows, int cols, int *matrix) {
    *matrix = (int )malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        (*matrix)[i] = (int *)malloc(cols * sizeof(int));
    }
}

// تابع fillToeplitz
void fillToeplitz(int matrix, int n, int *ptr) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ptr[abs(i - j)];
        }
    }
}

// تابع printMatrix
void printMatrix(int matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// تابع checkMatrix
int checkMatrix(int matrix, int row, int col) {
    return matrix[row][col];
}

// تابع freeMatrix
void freeMatrix(int matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// تابع determinantMatrix
int determinantMatrix(int n, int matrix) {
    if (n == 1) { // اگر ماتریس ۱x۱ باشد، دترمینان آن خود عدد است.
        return matrix[0][0];
    } else if (n == 2) { // اگر ماتریس ۲x۲ باشد، دترمینان آن را با فرمول خاص محاسبه کنید.
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else { // در غیر این صورت، از روش expansion laplace استفاده کنید.
        int det = 0;
        for (int k = 0; k < n; k++) { // حلقه بروی سطر اول ماتریس
            // ساختن زیرماتریس بدون سطر و ستون فعلی
            int submatrix;
            allocateMatrix(n - 1, n - 1, &submatrix);
            for (int i = 1; i < n; i++) { // حلقه بروی سطور دیگر ماتریس
                int j2 = 0;
                for (int j = 0; j < n; j++) { // حلقه بروی ستون های دیگر ماتریس
                    if (j == k)
                        continue;
                    submatrix[i - 1][j2] = matrix[i][j];
                    j2++;
                }
            }
            det += ((k % 2 == 0) ? 1 : -1) * matrix[0][k] * determinantMatrix(n - 1, submatrix);
            freeMatrix(submatrix, n - 1);
        }
