/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
*/

#include "Matrix.h"

int getRandomValue(int p)
{
    return rand() % p;
}

int* getRandomVector(int n, int p)
{
    int* x = malloc(n*sizeof(int));

    if(!x)
    {
        printf("Can not allocate memory for the vector x\n"); 
        return NULL;
    }

    for(int i = 0; i < n; i++)
    {
        x[i] = getRandomValue(p);
    }

    return x;
}

Matrix* newMatrix(int n)
{
    Matrix* matrix = malloc(sizeof(Matrix));

    if(!matrix)
    {
        printf("Can not allocate memory for the Matrix\n"); 
        return NULL;
    }

    matrix->n = n;
    matrix->values = malloc(n*sizeof(int*));

    if(!matrix->values) 
    {
        printf("Can not allocate memory to fill the Matrix\n"); 
        return NULL;
    }

    for(int i = 0; i < n; i++)
    {
        matrix->values[i] = malloc(n*sizeof(int));

        if(!matrix->values[i]) 
        {
            printf("Can not allocate memory to fill the Matrix\n"); 
            return NULL;
        }
    }

    return matrix;
}

Matrix* newIdentity(int n)
{
    Matrix* matrix = malloc(sizeof(Matrix));

    if(!matrix)
    {
        printf("Can not allocate memory for the Matrix\n"); 
        return NULL;
    }

    matrix->n = n;
    matrix->values = malloc(n*sizeof(int*));

    if(!matrix->values) 
    {
        printf("Can not allocate memory to fill the Matrix\n"); 
        return NULL;
    }

    for(int i = 0; i < n; i++)
    {
        matrix->values[i] = malloc(n*sizeof(int));

        if(!matrix->values[i]) 
        {
            printf("Can not allocate memory to fill the Matrix\n"); 
            return NULL;
        }

        for(int j = 0; j < n; j++)
        {
            matrix->values[i][j] = (i == j) ? 1 : 0;
        }
    }

    return matrix;
}

Matrix* newMatrixModP(int n, int p)
{
    Matrix* matrix = malloc(sizeof(Matrix));

    if(!matrix)
    {
        printf("Can not allocate memory for the Matrix\n"); 
        return NULL;
    }

    matrix->n = n;
    matrix->values = malloc(n*sizeof(int*));

    if(!matrix->values) 
    {
        printf("Can not allocate memory to fill the Matrix\n"); 
        return NULL;
    }

    for(int i = 0; i < n; i++)
    {
        matrix->values[i] = malloc(n*sizeof(int));

        if(!matrix->values[i]) 
        {
            printf("Can not allocate memory to fill the Matrix\n"); 
            return NULL;
        }

        for(int j = 0; j < n; j++)
        {
            matrix->values[i][j] = getRandomValue(p);
        }
    }

    return matrix;
}

Matrix* addMatrix(const Matrix* A, const Matrix* B, int p)
{
    int n = A->n;
    Matrix* C = newMatrix(n);
    
    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C->values[i][j] = add(A->values[i][j],B->values[i][j],p);
        }
    }

    return C;
}

Matrix* subMatrix(const Matrix* A, const Matrix* B, int p)
{
    int n = A->n;
    Matrix* C = newMatrix(n);
    
    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C->values[i][j] = sub(A->values[i][j],B->values[i][j],p);
        }
    }

    return C;
}

void negMatrix(Matrix* A, int p)
{
    int n = A->n;

    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            A->values[i][j] = A->values[i][j] ? (A->values[i][j] * -1) + p : 0;
        }
    }
}

void freeMatrix(Matrix* matrix)
{
    if(!matrix) return;
    
    for(int i = 0; i < matrix->n; i++)
    {
        free(matrix->values[i]);
    }

    free(matrix->values);
    free(matrix);
}

void printMatrix(const Matrix* matrix)
{
    for(size_t i = 0; i < matrix->n; i++)
    {
        for(size_t j = 0; j < matrix->n; j++)
        {
            printf("%d ",matrix->values[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

void printVector(const int* x, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ",x[i]);
    }

    printf("\n");
}

bool assertMatrixInversion(const Matrix* A, const Matrix* A_, int p)
{
    int n = A->n;
    int tmp;

    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            tmp = 0;

            for (int k = 0; k < n; ++k)
            {
                tmp = add(tmp,(A->values[i][k] * A_->values[k][j]) % p,p);
            }

            if(i == j)
            {
                if(tmp != 1)
                {
		            return 0;
                }
            }

            else
            {
                if(tmp != 0)
                {
		            return 0;
                }
            }
        }
    }

    return 1;
}
