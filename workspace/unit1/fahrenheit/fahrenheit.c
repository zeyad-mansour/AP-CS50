
#include <cs50.h>
#include <stdio.h>

int main(void)
{

    printf("Temperature in Celsius: ");

    float c = GetFloat();


    float f = (c * 9.0/5.0) + 32.0

    printf("The Temperature in Fahrenheit is:", f);
    return 0;
}