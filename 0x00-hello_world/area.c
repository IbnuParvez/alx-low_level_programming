#include <stdio.h>

int main(){
    int length;
    int width;
    int area;
    printf("Provide the desired length: \n");
    scanf("%d", &length);
    printf("Provide the desired width: \n");
    scanf("%d", &width);
    printf("Calculating area...\n");
    area= length * width;
    printf("The area is %d\n", area);
    return 0;
}
