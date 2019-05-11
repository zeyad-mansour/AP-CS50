#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
	int days;
	int pennies;
    do
    {
    	int days = get_int("How Many Days in the Month: ");
    }
    while (days < 28 || days > 31);
    do
    {
    int pennies = get_int(" Number of Pennies on First Day: ");
    }
    while (pennies <= 0);
    long long total = 0;
for (int i = 0; i < days; i++);
{
	total += pennies;
	pennies *= 2;
}
double dollars = (double)total / 100;
printf("$%.2f\n", dollars);

}