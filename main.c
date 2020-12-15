/*gcc main.c -o prog*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    char file_crypt[256];
    char file_decrypt[256];
    char letter_1[8] = {0};
    char letter_2[8] = {0};
    char letter_final[8];
    char final_letter = 0;
    int i = 7;
    int lettre;
    int check_word = 0;

    printf("choose the file to decrypt : ");

    fgets(file_crypt, 255, stdin);

        if(file_crypt[strlen(file_crypt) - 1] == '\n')
            file_crypt[strlen(file_crypt) - 1] = '\0';

    
    for(i = 0; i < strlen(file_crypt) - 1; i++){

        file_decrypt[i] = file_crypt[i];
    }

    FILE *fic = fopen(file_crypt, "r");

    FILE *fic2 = fopen(file_decrypt, "w");

    i = 7;

    while((lettre = fgetc(fic)) != EOF){

        if(check_word == 0){

            while(lettre != 0){

                letter_1[i] = lettre % 2;

                lettre = lettre / 2;

                i--;

            }
    
       check_word = 1;

       i = 7;

        }else{
  
            while(lettre != 0){

            letter_2[i] = lettre % 2;

            lettre = lettre / 2;

            i--;

            }   
        
            check_word = 0;

            /*for(i = 0; i < 8; i++){

                printf("%d", letter_1[i]);

            }

            printf("\n");

            for(i = 0; i < 8; i++){

                printf("%d", letter_2[i]);

            }
            
            printf("\n");*/

            letter_final[0] = letter_1[4];
            letter_final[1] = letter_1[1];
            letter_final[2] = letter_1[2];
            letter_final[3] = letter_1[3];
            
            letter_final[4] = letter_2[4];
            letter_final[5] = letter_2[1];
            letter_final[6] = letter_2[2];
            letter_final[7] = letter_2[3];

            if(letter_final[0] == 1)
                final_letter = final_letter + 128;
            
            if(letter_final[1] == 1)
                final_letter = final_letter + 64;
            
            if(letter_final[2] == 1)
                final_letter = final_letter + 32;
                
            if(letter_final[3] == 1)
                final_letter = final_letter + 16;
                
            if(letter_final[4] == 1)
                final_letter = final_letter + 8;

            if(letter_final[5] == 1)
                final_letter = final_letter + 4;

            if(letter_final[6] == 1)
                final_letter = final_letter + 2;

            if(letter_final[7] == 1)
                final_letter = final_letter + 1;

            for(i = 0; i < 8; i++){

                //printf("%d", letter_final[i]);
    
                letter_1[i] = 0;

                letter_2[i] = 0;

            }

            //printf("%c", final_letter);

            if(final_letter != 13){

                fputc(final_letter, fic2);

            }

            final_letter = 0;

            i = 7;

            //printf("\n\n");

        }   
    }

    fclose(fic);
    fclose(fic2);

}