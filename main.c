/*gcc main.c -o prog*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void Binary_to_Decimal(int *array, char final_letter, FILE *fic2){

    int i;
    int number = 128;

    for(i = 0; i < 8; i++){

        if(array[i] == 1)
            
            final_letter = final_letter + number;

        number = number / 2;

    }

    fputc(final_letter, fic2);

    final_letter = 0;

}

void Close_File_and_Free_table(FILE *fic, FILE *fic2, int *letter_1, int *letter_2){

    fclose(fic);
    fclose(fic2);

    free(letter_1);
    free(letter_2);

}

int Check_Matrix(char *check_matrix, FILE *fic, int j, char *check, int position){

    fgets(check_matrix, position, fic);
    
    if(strcmp(check_matrix, check) == 0){

        j++;

    }

    return j;

}
  
int Check_bits_Matrix(char *check_matrix, FILE *fic, int i, int j, int position){

    fgets(check_matrix, 9, fic);
        
        for(i = 0; i < 8; i++){
        
            if(check_matrix[i] == '1')
        
                j++;
        
            if(check_matrix[i] == '0')
        
                j++;
        
        }
        
    return j;

}

int *Decimal_to_Binary(int i, int lettre){

    int *tab = malloc(sizeof(int) * 8);

    while(lettre != 0){

        tab[i] = lettre % 2;

        lettre = lettre / 2;

        i--;

    }

    return tab;

}


int main(int argc, char *argv[])
{


    char file_crypt[256];
    char file_decrypt[256];
    char check_matrix[256];
    int *letter_1;
    int *letter_2;
    int letter_final[8];
    char final_letter = 0;
    int i;
    int j = 0;
    int lettre;
    int check_word = 0;
    int choice;

    while(j != 38){

        printf("\n Choose the matrix file : ");

        fgets(check_matrix, 255, stdin);
        
        if(check_matrix[strlen(check_matrix) - 1] == '\n')
            check_matrix[strlen(check_matrix) - 1] = '\0';

        FILE *fic = fopen(check_matrix, "rb");

        fgets(check_matrix, 255, fic);
        
        if(strlen(check_matrix) == 41){

            j++;

        }
        
        rewind(fic);

        j = Check_Matrix(check_matrix, fic, j, "G4C=[", 6);

        j = Check_bits_Matrix(check_matrix, fic, i, j, 9);
    
        j = Check_Matrix(check_matrix, fic, j, " ", 2);
        
        j = Check_bits_Matrix(check_matrix, fic, i, j, 9);
    
        j = Check_Matrix(check_matrix, fic, j, " ", 2);
        
        j = Check_bits_Matrix(check_matrix, fic, i, j, 9);
    
        j = Check_Matrix(check_matrix, fic, j, " ", 2);
     
        j = Check_bits_Matrix(check_matrix, fic, i, j, 9);
    
        j = Check_Matrix(check_matrix, fic, j, "]", 2);
    
        if(j != 38){

            printf("\n The matrix is wrong");

        }

    }
    
    printf("\n\n The matrix is correct \n\n What do you want to do ? :\n 0 : Decrypt a file\n Any other number : Crypt a file\n Your answer : ");

    scanf("%d", &choice);

    fflush(stdin);

    if(choice == 0){
    
        printf("\n Choose the file to decrypt : ");

        fgets(file_crypt, 255, stdin);

            if(file_crypt[strlen(file_crypt) - 1] == '\n')
                file_crypt[strlen(file_crypt) - 1] = '\0';

    
        for(i = 0; i < strlen(file_crypt) - 1; i++){

            file_decrypt[i] = file_crypt[i];

        }

        FILE *fic = fopen(file_crypt, "rb");

        FILE *fic2 = fopen(file_decrypt, "wb");

        while((lettre = fgetc(fic)) != EOF){

            i = 7;

            if(check_word == 0){

                letter_1 = Decimal_to_Binary(i, lettre);
    
                check_word = 1;

            }else{
  
               letter_2 = Decimal_to_Binary(i, lettre); 
        
                check_word = 0;

                letter_final[0] = letter_1[4];
                letter_final[1] = letter_1[1];
                letter_final[2] = letter_1[2];
                letter_final[3] = letter_1[3];
            
                letter_final[4] = letter_2[4];
                letter_final[5] = letter_2[1];
                letter_final[6] = letter_2[2];
                letter_final[7] = letter_2[3];

                Binary_to_Decimal(letter_final, final_letter, fic2);

                for(i = 0; i < 8; i++){
    
                    letter_1[i] = 0;

                    letter_2[i] = 0;

                }
            }
        }

        Close_File_and_Free_table(fic, fic2, letter_1, letter_2);
    
    }else{

        printf("\n Choose the file to crypt : ");

        fgets(file_decrypt, 255, stdin);

        if(file_decrypt[strlen(file_decrypt) - 1] == '\n')
            file_decrypt[strlen(file_decrypt) - 1] = '\0';

        strcpy(file_crypt, file_decrypt);
        strcat(file_crypt, "c");

        FILE *fic = fopen(file_decrypt, "rb");

        FILE *fic2 = fopen(file_crypt, "wb");

        

        while((lettre = fgetc(fic)) != EOF){

            i = 7;

            letter_1 = Decimal_to_Binary(i, lettre);

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

            Binary_to_Decimal(letter_1, final_letter, fic2);

            Binary_to_Decimal(letter_2, final_letter, fic2);

            for(i = 0; i < 8; i++){
    
                letter_final[i] = 0;
                
            }
        }

        Close_File_and_Free_table(fic, fic2, letter_1, letter_2);

    }

    return 0;

}