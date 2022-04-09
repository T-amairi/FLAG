/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
*/

#include "Matrix.h"

int getRandomValue(int p)
{
    return rand() % (p + 1);
}

Matrix* newMatrix(int n, int p)
{
    Matrix* matrix = malloc(sizeof(Matrix));

    if(!matrix)
    {
        printf("Can not allocate memory for the Matrix"); 
        return NULL;
    }

    matrix->n = n;
    matrix->values = malloc(n*sizeof(int*));

    if(!matrix->values) 
    {
        printf("Can not allocate memory to fill the Matrix"); 
        return NULL;
    }

    for(size_t i = 0; i < n; i++)
    {
        matrix->values[i] = malloc(n*sizeof(int));

        if(!matrix->values[i]) 
        {
            printf("Can not allocate memory to fill the Matrix"); 
            return NULL;
        }

        for(size_t j = 0; j < n; j++)
        {
            matrix->values[i][j] = getRandomValue(p);
        }
    }

    return matrix;
}

void freeMatrix(Matrix* matrix)
{
    for(size_t i = 0; i < matrix->n; i++)
    {
        free(matrix->values[i]);
    }

    free(matrix->values);
    free(matrix);
}

void printMatrix(Matrix* matrix)
{
    for(size_t i = 0; i < matrix->n; i++)
    {
        for(size_t j = 0; j < matrix->n; j++)
        {
            printf("%d ",matrix->values[i][j]);
        }

        printf("\n");
    }
}