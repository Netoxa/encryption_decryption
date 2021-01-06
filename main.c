/*gcc main.c -o prog*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void Binary_to_Decimal(int *array, char final_letter, FILE *fic2);
void Close_File(FILE *fic, FILE *fic2);
int Check_Matrix(char *check_matrix, FILE *fic, int j, char *check, int position);
int Check_bits_Matrix(char *check_matrix, FILE *fic, int i, int j, int position);

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

void Close_File(FILE *fic, FILE *fic2){

    fclose(fic);
    fclose(fic2);

}

int Check_Matrix(char *file, FILE *fic, int j, char *check, int position){

    fgets(file, position, fic);

    if(strcmp(file, check) == 0)

        j++;



    return j;

}

int Check_bits_Matrix(char *file, FILE *fic, int i, int j, int position){

    fgets(file, 9, fic);

        for(i = 0; i < 8; i++){

            if(file[i] == '1')

                j++;

            if(file[i] == '0')

                j++;

        }

    return j;

}



int main(int argc, char *argv[])
{

    char file[256];
    int letter_1[8];
    int letter_2[8];
    int letter_final[8];
    char final_letter = 0;
    int i;
    int j = 0;
    int letter;
    int check_word = 0;
    int choice;

    while(j != 38){

        printf("\n Choose the matrix file : ");

        fgets(file, 255, stdin);

        if(file[strlen(file) - 1] == '\n')

            file[strlen(file) - 1] = '\0';

        FILE *fic = fopen(file, "rb");

        fgets(file, 255, fic);

        if(strlen(file) == 41){

            j++;

        }

        rewind(fic);

        j = Check_Matrix(file, fic, j, "G4C=[", 6);

        j = Check_bits_Matrix(file, fic, i, j, 9);

        j = Check_Matrix(file, fic, j, " ", 2);

        j = Check_bits_Matrix(file, fic, i, j, 9);

        j = Check_Matrix(file, fic, j, " ", 2);

        j = Check_bits_Matrix(file, fic, i, j, 9);

        j = Check_Matrix(file, fic, j, " ", 2);

        j = Check_bits_Matrix(file, fic, i, j, 9);

        j = Check_Matrix(file, fic, j, "]", 2);

        if(j != 38)

            printf("\n The matrix is wrong");

    }

    printf("\n The matrix is correct \n\n What do you want to do ? :\n 0 : Decrypt a file\n Any other number : Crypt a file\n Your answer : ");

    scanf("%d", &choice);

    fflush(stdin);

    if(choice == 0){

        printf("\n Choose the file to decrypt : ");

        fgets(file, 255, stdin);

        if(file[strlen(file) - 1] == '\n')

            file[strlen(file) - 1] = '\0';

        FILE *fic = fopen(file, "rb");

        file[strlen(file) - 1] = '\0';

        FILE *fic2 = fopen(file, "wb");

        while((letter = fgetc(fic)) != EOF){

            i = 7;

            if(check_word == 0){

                while(letter != 0){

                    letter_1[i] = letter % 2;

                    letter = letter / 2;

                    i--;

                }

                check_word = 1;

            }else{

                while(letter != 0){

                    letter_2[i] = letter % 2;

                    letter = letter / 2;

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

                Binary_to_Decimal(letter_final, final_letter, fic2);

                for(i = 0; i < 8; i++){

                    letter_1[i] = 0;

                    letter_2[i] = 0;

                }
            }
        }

        Close_File(fic, fic2);

    }else{

        printf("\n Choose the file to crypt : ");

        fgets(file, 255, stdin);

        if(file[strlen(file) - 1] == '\n')
            file[strlen(file) - 1] = '\0';

        FILE *fic = fopen(file, "rb");

        strcat(file, "c");

        FILE *fic2 = fopen(file, "wb");

        while((letter = fgetc(fic)) != EOF){

            i = 7;

            while(letter != 0){

                letter_final[i] = letter % 2;

                letter = letter / 2;

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

            Binary_to_Decimal(letter_1, final_letter, fic2);

            Binary_to_Decimal(letter_2, final_letter, fic2);

            for(i = 0; i < 8; i++){

                letter_final[i] = 0;

            }
        }

        Close_File(fic, fic2);

    }

    return 0;

}
