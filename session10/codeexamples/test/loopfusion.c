//example to show loop fusion
#include <stdio.h>

int main() {
    int a[4] = {1, 2, 3, 4};
    int b[4] = {2, 3, 4, 5};

    for (int i = 0; i < 4; i++) {
        a[i] += 1;
    }

    for (int i = 0; i < 4; i++) {
        b[i] += 2;
    }

    return 0;
}
