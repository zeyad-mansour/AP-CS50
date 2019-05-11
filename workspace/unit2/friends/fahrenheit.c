#include <stdio.h>
#include <cs50.h>
int main(int argc, string argv[])
{
    if (argc != 2) { //2 not 1
        printf("usage: ./fahrenheit <temp>\n");
        return 1;
    }
    float c = atof(argv[1]);
    float f = (c * 9) / 5 + 32;
    printf("F: %.1f\n", f);
}