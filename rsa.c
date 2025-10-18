#include <stdio.h>

long long mdc(long long m, long long n)
{
    if (n==0) return m;
    return mdc (n, m % n);
}

int main() {

    long a = mdc(1500,2001);
    printf("%d\n", a);


}