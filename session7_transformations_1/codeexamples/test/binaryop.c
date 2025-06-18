#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[]){
	int sum=100;
	if(argc == 2)
		sum=atoi(argv[1]);
	//some computation here.  
	int x=sum+2;
	int y=x+x;
	int z=y-10;
	//With default (no) arguments: 100 is printed if no transformation is applied. 
	//If transformation of replacing all binary ops with mul is applied, 16000 (100*2*8*10) should be printed.
	printf("%d",z);
}
