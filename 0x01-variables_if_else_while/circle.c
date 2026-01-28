#include <stdio.h>


int main(){
    float radius, area;
    const float π = 3.142;
    printf("Kindly provide the radius you would like\n");
    scanf("%f", &radius);
    area = π * radius * radius;
    printf("Calculating the area ...\n");
    printf("The area is %f\n", area);
    return 0;
}
