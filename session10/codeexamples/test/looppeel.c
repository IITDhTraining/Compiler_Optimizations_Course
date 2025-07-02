//example to show peeling of first 3 iterations of the loop to avoid phi nodes. 
void bar(int);
void foo() {
  int a = 0;  
  int y = 0;
  int x = 0;
  for(int i = 0; i <100; ++i) {
    bar(a);
    x = y;
    y = a + 1;
    a = 5;
  }
  bar(x);
}