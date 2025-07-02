//example to show unrolling at runtime.
void foo(int n, int arr[]){
  for(int i = 0; i < n; ++i)
    arr[i] = i + arr[i];
}