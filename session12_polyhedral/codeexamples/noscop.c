// No Scop Detected. No work for polly.  
void foo(int *A, int *B, int n) {
    for (int i = 0; i < 8192; i++) {
        A[i] = i *200;
    }
}

//demo. enable -O3 and observe the IR.