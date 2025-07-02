//example to show LICM with module pass
#include "stdio.h"

int main(int argc, char* argv[]){
    int a = 5, b = 10;
    int x, y, sum;
    for (int i = 0; i < 5; i++){
        x = a * b;
        y = x + 5;
        sum = sum + i;
    }
    return sum+y;
}
