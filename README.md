# COO_and_CSR_formats_using_OpenMP_and_CUDA

The two formats of Sparse matrix Vector Multiplication COO and CSR were implemented on CPU , GPU and also parallelized using Open MP.

The code was tested with matrices with various sizes N=4, 8,10,16,32,64,128, 256,512 

We found that the CUDA implementation is the most efficient for both COO and CSR as it takes the least execution time.

Only when matrix size was huge(N=512) we found a significant decrease in execution time when parallelized with Open MP for both COO and CSR formats.

For the remaining sizes of the matrices no significant decrease in execution time was observed after parallelization with Open MP.


