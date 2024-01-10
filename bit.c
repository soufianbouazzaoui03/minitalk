#include <stdio.h>

void tobit(int n)
{
    int i =8;
    while(i)
    {
        i--;
        printf("%d", n % 2);
        n /= 2;
    }
}

int main()
{
    //10000000
    unsigned char c = 127;
    int i = 7;
    while(i >= 0)
    {
        printf("%d\n", (c >> i) & 1);
        i--;
    }
    // c = c | 1;
}