#include "main.h"
#include <stdio.h>
void print_alphabet_x10(void){
    int i = 0;
    char a;

    while (i<=9) {
        for (a = 'a'; a <= 'z'; a++){
            putchar(a);
        }
        putchar('\n');
       i++;
    }
}

int main(void)
{
    print_alphabet_x10();
    return (0);
}
