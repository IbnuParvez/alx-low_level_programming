#include <stdio.h>

int main(){
    float a, b, c, sum, average;
    printf("Enter all the three numbers of your liking: \n");
    scanf("%f %f %f", &a, &b, &c);
    sum = a + b + c;
    average = sum / 3;
    printf("Your average is %f\n",average);
    return 0;
}
