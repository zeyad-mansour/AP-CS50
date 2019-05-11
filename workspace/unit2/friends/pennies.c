#include <math.h>
#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (atoi(argv[1]) > 31 || atoi(argv[1]) < 28 || atoi(argv[2]) < 0 || argc != 3 ) {
        //checking if de inputt is in de requirements, if not den return error
        printf("Requirements Not Met\n");
        return 1;
    }
    int days = atoi(argv[1]);
    int pennies = atoi(argv[2]);
    long long total_amount = pennies;

    for(int i = 1; i < days; i++)
    {
        total_amount += pennies;
	    pennies *= 2;
		//have to use pow() for exponents unlike x**y in python :(
    }
    printf("$%.2f\n",((double) total_amount) / 100);
}