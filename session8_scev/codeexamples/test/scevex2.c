void foo(int *a, int n, int k){
	int sum=0;
	for(int i=0;i<n;i++)
		sum = sum + k;
	*a = sum;
}
