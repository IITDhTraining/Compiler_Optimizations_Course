void foo(int *a){
	for(int i=0;i<100;i++)
		a[i] = (i+1)*(i+1)-i*i-2*i; //simplify this.
}
