#include <stdio.h>

unsigned long long hanoi(char departure, char changeBuffer, char terminal, int amount)
{
    static unsigned long long times = 0;
    if (amount == 1)
    {
        printf("%c to %c\n", departure, terminal);
        times++;
    }
    else
    {
        hanoi(departure, terminal, changeBuffer, amount - 1);
        printf("%c to %c -%d\n", departure, terminal, amount);
        times++;
        hanoi(changeBuffer, departure, terminal, amount - 1);
    }
    return times;
}

int main(int argc, char const *argv[])
{
    char a = 'A';
    char b = 'B';
    char c = 'C';
    printf("一共移动了%llu次\n", hanoi(a, b, c, 5));
    return 0;
}