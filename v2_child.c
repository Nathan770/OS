#include <stdlib.h>
#include <stdio.h>
#include <io.h>

int Gcd(int a, int b);

int main(int argc, char *argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int fd = atoi(argv[3]);
    int gcd = Gcd(a, b);

    if (write(fd, &gcd, sizeof(int)) < 0) {
        perror("write to parent failed");
    }
    return 0;
}

int Gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return Gcd(b, a % b);
}
