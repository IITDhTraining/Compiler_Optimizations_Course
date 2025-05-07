
int foo(int x){
    return x;
}
int main() {
    int x, i;
    x = 5;
    for(i=0;i<10;i=i+1) {
        if (i < 5)
            x = x+1;
        x = x*2;
    }
    foo(x);
    return 0;
}