float bar(float);
void foo(long T, float A[][1024]) {
    for (long t = 0; t < T; t++){
        for (long i = 1; i < 1024 - 1; i++){
            A[t+1][i] += bar(A[t][i+1] + A[t][i-1]);
        }
    }
}