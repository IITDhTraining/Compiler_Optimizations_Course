//example to show peeling of first two iterations of the loop to avoid branching.
void foo();
void bar();
void baz();
int main(int argc, char **argv) {
    for(int i=0;i<argc;i++){
        if (i < 2) {
            foo();
        } else {
            bar();
            baz();
        }
    }
}