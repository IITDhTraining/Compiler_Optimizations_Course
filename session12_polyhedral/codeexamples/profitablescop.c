//valid region and also profitable
void foo(int *A, int *B) {
    int n=8192;

    for (int i = 0; i < n; i++) {
        A[i] = A[i] + B[i] * 200;
    }


    for (int j = 0; j < n; j++) {
        B[j] = B[j] + A[j] * 100;
    }
}