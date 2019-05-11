#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
 printf("ISBN number: ");
 long long isbn = GetLongLong();
 int tenth = isbn % 10;
 int sum = 0;

 for(int i = 10; i > 1; i--)
 {

 isbn = isbn / 10;

 sum = sum + (i - 1) * (isbn % 10);
 }

 int checkTenth = sum % 11;

 if (checkTenth == tenth)
 {
 printf("YES\n");
 }
 else
 {
 printf("NO\n");
 }

}