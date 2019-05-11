#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[])
{

    if(argc == 1) {
        printf("INVALID!\n");
        return 1;
    }

    else if (argc > 2)  {
        printf("INVALID!\n");
        return 1;
    }

    else {
        int secret_key = atoi(argv[1]);

     string secret_message = get_string("What would you like to encrypt? \n");

        int len_alphabet = 26;
        int uppercase = 65;
        int lowercase = 97;
		//defining where the asci values start at

        printf("ciphertext: ");
        for (int i = 0, n = strlen(secret_message); i < n; i++) {

            if (isupper(secret_message[i]))
                printf("%c", ((secret_message[i] - uppercase + secret_key) % len_alphabet) + uppercase );
            else if (islower(secret_message[i]))
                printf("%c", ((secret_message[i] - lowercase + secret_key) % len_alphabet) + lowercase);

            else

                printf("%c", secret_message[i]);
        }
    }
printf("\n");
}