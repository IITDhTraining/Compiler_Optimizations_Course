void use(int); 
void test(int j) { 
    int i=1; 
    int max;
    L: max=j;
    if(i<max){
    	i=i+i;
	goto L;
    }
    use(i); 
}
