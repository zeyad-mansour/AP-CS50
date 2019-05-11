#include <stdio.h>
#include <string.h>
int main(){

    char name[1000];
    //printf("Enter name: ");
    scanf("%[^\n]",name);
    int len = strlen(name);


     if(name[0] != ' ')
        printf("%c", toupper(name[0]));
    for(int i = 0; i < len; i++) {
       if(name[i] == ' ' && name[i+1] != ' ') {
        printf("%c", toupper(name[i + 1]));
        }
    }
    printf("\n");
}
