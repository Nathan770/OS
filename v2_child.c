#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int Gcd(int a, int b);

int main(int argc, char *argv[]) {
    int a = 0, b = 0, gcd;
    while (read(STDIN_FILENO, &a, sizeof(int)) > 0) {
        if (read(STDIN_FILENO, &b, sizeof(int)) < 0) {
            break;
        }
        gcd = Gcd(a, b);
        if (write(STDOUT_FILENO, &gcd, sizeof(int)) < 0) {
            perror("write to parent failed");
        }
    }
    perror("child1 reading failed");
    return 0;
}

int Gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return Gcd(b, a % b);
}
