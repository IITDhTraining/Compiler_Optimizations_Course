int foo(){
	int a, b, c[100], d;
	extern int *q;
	q=&a;
	a=2;
	b=*q+2;
	q=&b;
	for(int i=0;i<100;i++){
		c[i] = c[i] + a;
		*q = i;
	}
	d = *q + a;
	return d;
}
