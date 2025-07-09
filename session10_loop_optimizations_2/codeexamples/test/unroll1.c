//example to show unrolling after inlining: insert as prefix: __attribute__((always_inline)) inline at the beginning of line 3 
void bar();
int foo(int n){
    for(int i = 0; i < n; ++i) {
        bar();
    }
    return 0;
}

int main(int argc, char **argv) {
    foo(3);
}
