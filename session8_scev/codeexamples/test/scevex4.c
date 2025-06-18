void foo(int *a, short k, int p, int n){
	for(int i=0;i<n;i++)
		a[i] = (k+i)*p;
}
