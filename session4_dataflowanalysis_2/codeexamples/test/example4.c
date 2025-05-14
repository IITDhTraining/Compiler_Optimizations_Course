int testhelper(int x);

int test(_Bool cond){
	int a,b,c;
	a=47;
	b=42;
	if(cond){
		b=1;
		c=5;
	} else {
		a=2;
		c=10;
	}	
	return testhelper(a-c);
}
