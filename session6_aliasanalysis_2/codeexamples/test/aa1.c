#ifdef ALIAS_TEST
int foo() {
  int a, b;
  return a + b;
}
#endif

#ifdef MODREF_TEST1
void bar(int *p);

void foo() {
    int a = 0;
    bar(&a);
}
#endif

#ifdef MODREF_TEST2
void write_mem(int *p) { *p = 42; }
int read_mem(int *p) { return *p; }

void foo() {
    int x = 0;
    write_mem(&x);
    read_mem(&x);
}
#endif