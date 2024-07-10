#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
void sparse_matrix_vector_multiply_CSR(int rows, int cols, int* matrix, int* vector, int* result) {

    int nnz = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i * cols + j] != 0) {
                nnz++;
            }
        }
    }
    
    int* values = (int*)malloc(nnz * sizeof(int));
    int* col_indices = (int*)malloc(nnz * sizeof(int));
    int* row_pointers = (int*)malloc((rows + 1) * sizeof(int));
    

    int index = 0;
    row_pointers[0] = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i * cols + j] != 0) {
                values[index] = matrix[i * cols + j];
                col_indices[index] = j;
                index++;
            }
        }
        row_pointers[i + 1] = index;
    }
    

    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = row_pointers[i]; j < row_pointers[i + 1]; j++) {
            result[i] += values[j] * vector[col_indices[j]];
        }
    }
    

    free(values);
    free(col_indices);
    free(row_pointers);
}
void shuffle(int array[], int n) {
    if (n > 1) {
        for (int i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            int temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
}

int main() {     
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int matrix[N*N];
    float zeroPercentage = 0.7; 
    int totalElements = N*N;
    int zeroElements = totalElements * zeroPercentage;

    srand(time(NULL));

    // Fill the matrix with at least 70% zeros
    for (int i = 0; i < totalElements; i++) {
        if (i < zeroElements) {
            matrix[i] = 0;
        } else {
            matrix[i] = rand() % 10 + 1; 
        }
    }

   
    shuffle(matrix, totalElements);
     
    int* vector = (int*)malloc(N * sizeof(int));

    if (vector == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        vector[i] = i + 1;
    }
    

    int rows = N;
    int cols = N;
    
    int* result = (int*)malloc(rows * sizeof(int));
    
    sparse_matrix_vector_multiply_CSR(rows, cols, matrix, vector, result);
    
  
    printf("Resultant matrix:\n");
    for (int i = 0; i < rows; i++) {
        printf("%d\n", result[i]);
    }
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    

    printf("Execution time: %10f seconds\n", cpu_time_used);
    

    free(result);
    
    return 0;
}
