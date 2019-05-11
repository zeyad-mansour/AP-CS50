#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(int argc, string argv[])
{
    if (argv[2][0] != '-' && argv[2][0] != '/' && argv[2][0] != '+' && argv[2][0] != 'x' && argv[2][0] != '%') {
        printf("INVALID OPERATOR!!!");
        return 1;
    }

    //variables for the numbers in the expression
    float number_one = atof(argv[1]);
    float number_two = atof(argv[3]);
	//only has to be float because problem input is up to 6 decimal points

    //variable for the operator
    string input_numbers = argv[2];
    char Operator_Symbol = input_numbers[0];

    float output;
    int number_for_modulus;

    switch(Operator_Symbol) { //the switch statement is very helpful!
        case 'x' :
            output = number_one * number_two;
            break;
		case '+' :
            output = number_one + number_two;
            break;
        case '/' :
            output = number_one / number_two;
            break;
		case '-' :
            output = number_one - number_two;
            break;
        case '%':
            number_for_modulus = (int)(number_one / number_two);
            output = number_one - (number_for_modulus * number_two);
    }


   if (argc != 4)
   {
        return 1;
    }
    //print the final result for calculator!



    printf("%.6f\n", output);
}