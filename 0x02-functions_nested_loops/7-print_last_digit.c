#include "main.h"

int print_last_digit(int n){
    int last;
    last  = n % 10;
    if (last < 0){
        last = -last;
    }
    _putchar(last + '0');
    return (last);
}

int main(void)
{
    int r;

    print_last_digit(98);
    print_last_digit(0);
    r = print_last_digit(-1024);
    _putchar('0' + r);
    _putchar('\n');
    return (0);
}
