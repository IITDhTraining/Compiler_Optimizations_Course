#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[]){
	int sum=100;
	if(argc == 2)
		sum=atoi(argv[1]);
	printf("%d",sum+2);
}
