/*gcc main.c -o prog*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    char file_crypt[256];
    char file_decrypt[256];
    char letter_1[8] = {0,0,0,0,0,0,0,0};
    char letter_2[8] = {0,0,0,0,0,0,0,0};
    char letter_final[8];
    int i = 7;
    int lettre;
    int check_word = 0;

    /*printf("choose the file to decrypt : ");

    fgets(file_crypt, 255, stdin);

        if(file_crypt[strlen(file_crypt) - 1] == '\n')
            file_crypt[strlen(file_crypt) - 1] = '\0';

    
    /*for(i = 0; i < strlen(file_crypt) - 1; i++){

        file_decrypt[i] = file_crypt[i];
    }

    printf("\n %s", file_decrypt);*/

    FILE *fic = fopen("EPREUVE 1.txtc", "r");

    while((lettre = fgetc(fic)) != EOF){

        if(check_word == 0){

            while(lettre != 0){

                letter_1[i] = lettre % 2;

                lettre = lettre / 2;

                i--;

            }
        
            for(i = 0; i < 8; i++){

                printf("%d", letter_1[i]);

                letter_1[i] = 0;

        }
        
       i = 7;

       printf("\n");
    
       check_word = 1;

        }else{
  
            while(lettre != 0){

            letter_2[i] = lettre % 2;

            lettre = lettre / 2;

            i--;

            }   
        
            for(i = 0; i < 8; i++){

            printf("%d", letter_2[i]);

            letter_2[i] = 0;

        }

        i = 7;

        printf("\n");
    
        check_word = 0;

        }

    }   

}