void foo(int n, int* restrict  A, int* restrict B, int* restrict C){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A[i*n+j] = B[i*n+j] * C[i*n+j];
        }  
    }
}

/*Exercise: How many regions can you identify with the help of scop-analysis in the above code?
 *Why are those regions showing up as 'Invalid SCoP'?
 */

