#include <stdlib.h>
#include <stdio.h>

int Gcd(int a, int b);

int main(int argc, char * argv[])
{
   int a = atoi(argv[1]);
   int b = atoi(argv[2]);
   printf("in child");
   int gcd = Gcd(a,b);

    return gcd;
}

int Gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return Gcd(b, a % b);
}
