#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    int starting_point = 0;
	int assign_encrypted_letter;
	int modulus;

    if (argc != 2)
    {
        return 1;
    }

    string key = (argv[1]);
    for (int i = 0; i < strlen(key); i++)
    {
        if (isalpha(key[i]) == false)
        {
            return 1;
        }
    }
    string user_input = get_string("What message would you like to encode?: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(user_input); i++)
    {
        if islower(user_input[i])
        {
            modulus = (starting_point % strlen(key));
            assign_encrypted_letter = (tolower(key[modulus]) - 97);
            printf("%c", (((user_input[i] + assign_encrypted_letter) - 97) % 26) + 97);
            starting_point += 1;
        }
        else if isupper(user_input[i])
        {
            modulus = (starting_point % strlen(key));
            assign_encrypted_letter = (tolower(key[modulus]) - 97);
            printf("%c", (((user_input[i] + assign_encrypted_letter) - 65) % 26) + 65);
            starting_point += 1;
        }
        else
        {
            printf("%c", user_input[i]);
        }
    }
    printf("\n");
    //exit the program nicely

}