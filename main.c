/*gcc main.c -o prog*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{

    char file_crypt[256];
    char file_decrypt[256];
    char letter_1[8] = {0};
    char letter_2[8] = {0};
    char letter_final[8] = {0};
    char final_letter;
    int i;
    int lettre;
    int check_word = 0;
    int choice = 0;

    printf("\n What do you want to do ? :\n 0 : Decrypt a file\n Any other number : Crypt a file\n Your answer : ");

    scanf("%d", &choice);

    fflush(stdin);

    if(choice == 0){
    
        printf("choose the file to decrypt : ");

        fgets(file_crypt, 255, stdin);

            if(file_crypt[strlen(file_crypt) - 1] == '\n')
                file_crypt[strlen(file_crypt) - 1] = '\0';

    
        for(i = 0; i < strlen(file_crypt) - 1; i++){

            file_decrypt[i] = file_crypt[i];
        }

        FILE *fic = fopen(file_crypt, "rb");

        FILE *fic2 = fopen(file_decrypt, "wb");

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
    
                    letter_1[i] = 0;

                    letter_2[i] = 0;

                }

                fputc(final_letter, fic2);

                final_letter = 0;

                i = 7;

            }   
        }

        fclose(fic);
        fclose(fic2);

    }else{

        printf("choose the file to crypt : ");

        fgets(file_decrypt, 255, stdin);

        if(file_decrypt[strlen(file_decrypt) - 1] == '\n')
            file_decrypt[strlen(file_decrypt) - 1] = '\0';

        strcpy(file_crypt, file_decrypt);
        strcat(file_crypt, "c");

        FILE *fic = fopen(file_decrypt, "rb");

        FILE *fic2 = fopen(file_crypt, "wb");

        i = 7;

        while((lettre = fgetc(fic)) != EOF){

            while(lettre != 0){

                letter_final[i] = lettre % 2;

                lettre = lettre / 2;

                i--;

            }

            letter_1[0] = rand() % 2;
            letter_1[1] = letter_final[1];
            letter_1[2] = letter_final[2];
            letter_1[3] = letter_final[3];
            letter_1[4] = letter_final[0];
            letter_1[5] = rand() % 2;
            letter_1[6] = rand() % 2;
            letter_1[7] = rand() % 2;

            letter_2[0] = rand() % 2;
            letter_2[1] = letter_final[5];
            letter_2[2] = letter_final[6];
            letter_2[3] = letter_final[7];
            letter_2[4] = letter_final[4];
            letter_2[5] = rand() % 2;
            letter_2[6] = rand() % 2;
            letter_2[7] = rand() % 2;


                if(letter_1[0] == 1)
                    final_letter = final_letter + 128;
            
                if(letter_1[1] == 1)
                    final_letter = final_letter + 64;
            
                if(letter_1[2] == 1)
                    final_letter = final_letter + 32;
                
                if(letter_1[3] == 1)
                    final_letter = final_letter + 16;
                
                if(letter_1[4] == 1)
                    final_letter = final_letter + 8;

                if(letter_1[5] == 1)
                    final_letter = final_letter + 4;

                if(letter_1[6] == 1)
                    final_letter = final_letter + 2;

                if(letter_1[7] == 1)
                    final_letter = final_letter + 1;

                fputc(final_letter, fic2);

                final_letter = 0;

                if(letter_2[0] == 1)
                    final_letter = final_letter + 128;
            
                if(letter_2[1] == 1)
                    final_letter = final_letter + 64;
            
                if(letter_2[2] == 1)
                    final_letter = final_letter + 32;
                
                if(letter_2[3] == 1)
                    final_letter = final_letter + 16;
                
                if(letter_2[4] == 1)
                    final_letter = final_letter + 8;

                if(letter_2[5] == 1)
                    final_letter = final_letter + 4;

                if(letter_2[6] == 1)
                    final_letter = final_letter + 2;

                if(letter_2[7] == 1)
                    final_letter = final_letter + 1;

                fputc(final_letter, fic2);

                final_letter = 0;

                for(i = 0; i < 8; i++){
    
                    letter_final[i] = 0;

                }
                
            i = 7;
            
        }
    }
}