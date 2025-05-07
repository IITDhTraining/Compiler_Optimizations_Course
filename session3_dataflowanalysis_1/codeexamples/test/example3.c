int test(int a, int b, _Bool c) {
    int res;
    if (c)
        res = a;
    else
        res = b;
    return res;
}