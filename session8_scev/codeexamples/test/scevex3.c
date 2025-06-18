void foo(int *a, int n){
	for(int i=0;i<n;i++)
		a[i] = i*i*i + 2*i*i + 3*i + 7;
}
