/*gcc main.c -o prog*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void Binary_to_Decimal(int *array, char final_letter, FILE *fic2, int number);
void Close_File(FILE *fic, FILE *fic2);
int Check_Matrix(char *check_matrix, FILE *fic, int j, char *check, int position);
int Check_bits_Matrix(char *check_matrix, FILE *fic, int i, int j, int position);

void Binary_to_Decimal(int *array, char final_letter, FILE *fic2, int number){

    int i;

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
    int letter_1[8] = {0};
    int letter_2[8] = {0};
    int letter_final[8] = {0};
    char matrix[4][255];
    char matrix_2[8][9];
    char matrix_search[4][255] =  {
                                    {"1000"},
                                    {"0100"},
                                    {"0010"},
                                    {"0001"}
                                };
    int matrix_result[4] = {0};
    char final_letter = 0;
    int i;
    int k;
    int j;
    int letter;
    int check_word = 0;
    int choice;
    int check;
    FILE *fic;
    FILE *fic2;

    while(j != 51){

        j = 0;

        check = 0;

        printf("\n Choose the matrix file : ");

        fgets(file, 255, stdin);

        if(file[strlen(file) - 1] == '\n')

            file[strlen(file) - 1] = '\0';

        fic = fopen(file, "rb");

        fgets(file, 255, fic);

//------ Check matrix architecture ------//

        if(strlen(file) == 41)

            j++;

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

//---------------------------------------//

        if(j != 38)

            printf("\n The matrix architecture is wrong");

        rewind(fic);

//------ Take the matrix ------//

        fscanf(fic, "%s %s %s %s", matrix[0], matrix[1], matrix[2], matrix[3]);

        strncpy(matrix[0], matrix[0] + 5, 255);

        matrix[3][strlen(matrix[3]) - 1] = '\0';

        for(i = 0; i < 4; i++){

            matrix_2[0][i] = matrix[i][0];
            matrix_2[1][i] = matrix[i][1];
            matrix_2[2][i] = matrix[i][2];
            matrix_2[3][i] = matrix[i][3];
            matrix_2[4][i] = matrix[i][4];
            matrix_2[5][i] = matrix[i][5];
            matrix_2[6][i] = matrix[i][6];
            matrix_2[7][i] = matrix[i][7];
        
        }

        for(i = 0; i < 8; i++){

            for(k = 0; k < 4; k++){

                if(strcmp(matrix_2[i], matrix_search[k]) == 0){

                    matrix_result[k] = i;

                    check++;

                }
            }
        }

//-----------------------------//

//------ Check the matrix ------//

        if(check == 4)

            j++;

        for(i = 0; i < 4; i++){

            for(k = 0; k < 4; k++){

                if((i != k) && (matrix_result[i] != matrix_result[k]))

                    j++;

            }
        }

//------------------------------//
            
        if(j != 51)

            printf("\n The matrix is wrong");

    }

    printf("\n The matrix is correct");

    fclose(fic);

    printf("\n The key is ");

    for(i = 0; i < 4; i++)

        printf("%d", matrix_result[i]);

    printf("\n\n What do you want to do ? :\n 0 : Decrypt a file\n Any other number : Crypt a file\n Your answer : ");

    scanf("%d", &choice);

    fflush(stdin);

    if(choice == 0){

        printf("\n Choose the file to decrypt : ");

        fgets(file, 255, stdin);

        if(file[strlen(file) - 1] == '\n')

            file[strlen(file) - 1] = '\0';

        fic = fopen(file, "rb");

        file[strlen(file) - 1] = '\0';

        fic2 = fopen(file, "wb");

        while((letter = fgetc(fic)) != EOF){

            i = 7;

            if(check_word == 0){

                
//------ Decimal -> Binary ------//

                while(letter != 0){

                    letter_1[i] = letter % 2;

                    letter = letter / 2;

                    i--;

                }

//-------------------------------//

                check_word = 1;

            }else{

//------ Decimal -> Binary ------//

                while(letter != 0){

                    letter_2[i] = letter % 2;

                    letter = letter / 2;

                    i--;

                }

//-------------------------------//

                check_word = 0;

//------ Insert data with matrix ------//

                for(i = 0; i < 4; i++){

                    letter_final[i] = letter_1[matrix_result[i]];

                    letter_final[i + 4] = letter_2[matrix_result[i]];

                }

//-------------------------------------//

                Binary_to_Decimal(letter_final, final_letter, fic2, 128);

                for(i = 0; i < 4; i++){

                    letter_1[matrix_result[i]] = 0;

                    letter_2[matrix_result[i]] = 0;

                }
            }
        }

    }else{

        printf("\n Choose the file to crypt : ");

        fgets(file, 255, stdin);

        if(file[strlen(file) - 1] == '\n')

            file[strlen(file) - 1] = '\0';

        fic = fopen(file, "rb");

        strcat(file, "c");

        fic2 = fopen(file, "wb");

        while((letter = fgetc(fic)) != EOF){

            i = 7;

//------ Decimal -> Binary ------//

            while(letter != 0){

                letter_final[i] = letter % 2;

                letter = letter / 2;

                i--;

            }

//-------------------------------//

//------ Insert data with matrix ------//

            for(i = 0; i < 4; i++){

                letter_1[matrix_result[i]] = letter_final[i];

                letter_2[matrix_result[i]] = letter_final[i + 4];

            }

//-------------------------------------//

            Binary_to_Decimal(letter_1, final_letter, fic2, 128);

            Binary_to_Decimal(letter_2, final_letter, fic2, 128);

            for(i = 0; i < 8; i++)

                letter_final[i] = 0;

        }
    }

    Close_File(fic, fic2);

    return 0;

}