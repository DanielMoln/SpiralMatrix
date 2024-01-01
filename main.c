#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

int handleChoice(char choice);

int main()
{
    bool isRunning = true;

    do
    {
        system("cls");
        puts("\n");
        puts("\t---------------");
        puts("");
        puts("\tSpiralMatrix");
        puts("");
        puts("\t---------------");
        puts("a - Give a short introduction about the program.");
        puts("b - Create a new spiral matrix.");
        puts("c - Save an existing matrix.");
        puts("d - Load an existing matrix.");
        puts("e - Show the current matrix.");
        puts("x - Quit.");
        puts("\n");

        char choice;
        scanf("%c", &choice);
        printf("\n");

        isRunning = (handleChoice(choice) == 1 ? true : false);
    } while (isRunning);

    return 0;
}

int handleChoice(char choice)
{
    switch (choice)
    {
        case 'a':
            system("cls"); //clear screen
            puts("\n");
            puts("This program creates a spiral matrix.");
            puts("\n");
            return 1;
        case 'b':
            system("cls"); //clear screen
            puts("Create a new spiral matrix.");

            int dimension;
            char direction;
            int rotation;

            printf("Dimension: ");
            scanf("%d", &dimension);

            printf("Starting direction: ");
            scanf(" %c", &direction);

            printf("cw (0)/ccw (1): ");
            scanf("%d", &rotation);

            if (direction == 'r' && rotation == 0)
            {
                system("cls"); //clear screen
                generateMatrix(dimension);
            }
            return 1;
        case 'c':
            system("cls"); //clear screen
            puts("Save an existing matrix:\n");
            saveCurrentMatrix();
            printf("\n");
            printf("Quit? Press any number...\n");
            int e;
            scanf("%d", &e);
            return 1;
        case 'd':
            system("cls"); //clear screen
            puts("Load an existing matrix.\n");
            printf("Enter file path:");
            char filePath[200];
            scanf("%s", filePath);
            loadNewMatrix(filePath);
            return 1;
        case 'e':
            system("cls"); //clear screen
            puts("Current matrix:\n");
            printCurrentMatrix();
            printf("\n");
            printf("Quit? Press any number...\n");
            int c;
            scanf("%d", &c);
            return 1;
        case 'x':
            system("cls"); //clear screen
            puts("\n");
            puts("Bye!");
            puts("\n");
            remove("temp_matrix.txt");
            return 0;
        default:
            system("cls"); //clear screen
            puts("Invalid choice.");
            return 1;
    }
}

void generateMatrix(int dimension)
{
    int** matrix;

    matrix = (int**) malloc(dimension * sizeof(int*));

    for (int i = 0; i < dimension; i++) {
      matrix[i] = (int*) malloc(dimension * sizeof(int));
    }

    // Fill the matrix with zeros
    for (int i = 0; i < dimension; i++) {
      for (int j = 0; j < dimension; j++) {
        matrix[i][j] = 0;
      }
    }

    int centerPointX = dimension % 2 == 0 ? ((dimension / 2 - 1)) : (dimension - 1) / 2;
    int centerPointY = dimension % 2 == 0 ? ((dimension / 2 - 1)) : (dimension - 1) / 2;

    int currentNumber = 4;

    matrix[centerPointY][centerPointX] = 1; // 1
    matrix[centerPointY][centerPointX + 1] = 2; // 2
    matrix[centerPointY + 1][centerPointX + 1] = 3; // 3

    int row = centerPointY + 1;
    int col = centerPointX + 1;

    int direction = 2; // 0= TOP,
                           // 1= BOTTOM
                           // 2= LEFT,
                           // 3= RIGHT

    matrix[row][--col] = 4; // put 4 to the matrix

    while (currentNumber < (dimension * dimension)) {
        // next element
        int leftNumber = (col - 1) >= 0 ? matrix[row][col - 1] : -3;
        int topNumber = (row - 1) >= 0 ? matrix[row - 1][col] : -3;
        int bottomNumber = (row + 1) < dimension ? matrix[row + 1][col] : -3;
        int rightNumber = (col + 1) < dimension ? matrix[row][col + 1] : -3;

        switch (direction) {
          case 2:
            if (leftNumber == 0) {
              direction = 2;
            }

            if (topNumber == 0) {
              direction = 0;
            }
            break;
          case 0:
            if (topNumber == 0) {
              direction = 0;
            }
            if (rightNumber == 0) {
              direction = 3;
            }
            break;
          case 3:
            if (rightNumber == 0) {
              direction = 3;
            }

            if (bottomNumber == 0) {
              direction = 1;
            }
            break;
          case 1:
            if (bottomNumber == 0) {
              direction = 1;
            }

            if (leftNumber == 0) {
              direction = 2;
            }
            break;
        }

        switch (direction) {
          case 2:
            matrix[row][--col] = ++currentNumber;
            break;
          case 0:
            matrix[--row][col] = ++currentNumber;
            break;
          case 3:
            matrix[row][++col] = ++currentNumber;
            break;
          case 1:
            matrix[++row][col] = ++currentNumber;
            break;
        }

        system("cls"); //clear screen
        for (int i = 0; i < dimension; i++)
        {
            for (int j = 0; j < dimension; j++)
            {
                printf("%d\t", matrix[i][j]);
            }
            printf("\n");
        }
    }

    // Open the file for writing
    FILE* file = fopen("temp_matrix.txt", "w");

    // Print out the dimension
    fprintf(file, "%d\n", dimension);

    // Print the matrix to the file
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
          fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
     }

    // Close the file
    fclose(file);

    for (int i = 0; i < dimension; i++) {
      free(matrix[i]);
    }
    free(matrix);
}


void printCurrentMatrix()
{
    // Open the file for writing
    FILE* file = fopen("temp_matrix.txt", "r");
    int dimension = 0;
    fscanf(file, "%d", &dimension);

    int** matrix;
    matrix = (int**) malloc(dimension * sizeof(int*));

    for (int i = 0; i < dimension; i++) {
        matrix[i] = (int*) malloc(dimension * sizeof(int));
    }

    if (file == NULL) {
        printf("Matrix does not exists.\n");
        return;
    }

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
          fscanf(file, "%d", &matrix[i][j]);
        }
    }

    // Print the matrix to the console
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
          printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    fclose(file);
}

void saveCurrentMatrix()
{
    // Open the file for writing
    FILE* file = fopen("temp_matrix.txt", "r");
    int dimension = 0;
    fscanf(file, "%d", &dimension);

    if (file == NULL) {
        printf("Matrix does not created yet.\n");
        return;
    }

    fclose(file);

    char result[100];

    sprintf(result, "spiral%dcw.txt", dimension);

    if (rename("temp_matrix.txt", result) == 0)
    {
        printf("\nSuccessfully created!");
    }
    else
    {
        printf("Something went wrong during saving the matrix.");
    }
}


void loadNewMatrix(char fileName[200])
{
    FILE* file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Matrix not found :/");
        return;
    }

    // reading data from file and create a new matrix
    int dimension = 0;
    fscanf(file, "%d", &dimension);

    int** matrix;
    matrix = (int**) malloc(dimension * sizeof(int*));

    for (int i = 0; i < dimension; i++) {
        matrix[i] = (int*) malloc(dimension * sizeof(int));
    }

    if (file == NULL) {
        printf("Matrix does not exists.\n");
        return;
    }

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
          fscanf(file, "%d", &matrix[i][j]);
        }
    }

    // close file
    fclose(file);

    // loop through & override temp_matrix
    FILE* file2 = fopen("temp_matrix.txt", "w");

    // Print out the dimension
    fprintf(file2, "%d\n", dimension);

    // Print the matrix to the file
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
          fprintf(file2, "%d ", matrix[i][j]);
        }
        fprintf(file2, "\n");
     }

    // Close the file
    fclose(file2);

    // free memory space
    for (int i = 0; i < dimension; i++) {
      free(matrix[i]);
    }
    free(matrix);
}
