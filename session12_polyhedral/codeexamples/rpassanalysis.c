//3 point stencil code e.g., pattern appears while solving heat equation
//outer loop is time axis, inner loop is space axis
//observe the polyhedral representation of the SCoPs
void foo(long T, float A[][1024]) {
    for (long t = 0; t < T; t++){
        for (long i = 1; i < 1024 - 1; i++){
            A[t+1][i] += A[t][i+1] + A[t][i-1];
        }
    }
}


















#if 0
#define N 1024
void foo(float A[1024], float B[1024]) {

    for (int i = 0; i < N; i++) {
        /*if (i <= N - 50)
            A[5+i] = A[i] + 1;
        else
            A[3+i] = A[i] + 2;*/

        for (int j = 0; j < N; j++)
            B[j] = B[j] + 3;
    }
}
#endif
