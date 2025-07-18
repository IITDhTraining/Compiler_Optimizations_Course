//invalid region but it is profitable to optimize loops
void foo(int *A, int *B, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = A[i] + B[i] * 200;
    }

    for (int j = 0; j < n; j++) {
        B[j] = B[j] + A[j] * 100;
    }
}