/**
 * @file LU.c
 * @author Tahar AMAIRI & Hamza RAIS
 * @brief Implementation of LU decomposition and inversion
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "LU.h"

void LU(const Matrix* A, Matrix* L, Matrix* U, int p)
{
    int n = A->n;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            L->values[i][j] = (i == j ? 1 : 0);
            U->values[i][j] = 0;
        }
    }

    int tmp;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            tmp = 0;

            for (int k = 0; k < i; k++)
            {
                tmp = add(tmp,((long) L->values[i][k] * U->values[k][j]) % p,p);
            }
            
            U->values[i][j] = sub(A->values[i][j],tmp,p);
        }
 
        for (int j = i; j < n; j++)
        {
            tmp = 0;

            for (int k = 0; k < i; k++)
            {
                tmp = add(tmp,((long) L->values[j][k] * U->values[k][i]) % p,p); 
            }

            L->values[j][i] = ((long) sub(A->values[j][i],tmp,p) * inv(U->values[i][i],p)) % p;
        }
    }
}

bool assertLU(const Matrix* A, const Matrix* L, const Matrix* U, int p)
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
                tmp = add(tmp,((long) L->values[i][k] * U->values[k][j]) % p,p);
            }

            if(tmp != A->values[i][j])
            {
                printf("LU decomposition failed the assertion A = LU\n");
		        return false;
            }
        }
    }

    return true;
}

int* forwardSub(const Matrix* L, const int* b, int p)
{
    int n = L->n;
    int* x = malloc(n*sizeof(int));

    if(!x)
    {
        printf("Can not allocate memory for the vector x during the forward substitution\n"); 
        return NULL;
    }

    memset(x,0,n*sizeof(int));
    int tmp;

    for(int i = 0; i < n; i++)
    {
        tmp = b[i];

        for(int j = 0; j < i; j++)
        {
            tmp = sub(tmp,((long) L->values[i][j] * x[j]) % p,p);
        }

        x[i] = ((long) tmp * inv(L->values[i][i],p)) % p;
    }

    return x;
}

int* backwardSub(const Matrix* U, const int* b, int p)
{
    int n = U->n;
    int* x = malloc(n*sizeof(int));

    if(!x)
    {
        printf("Can not allocate memory for the vector x during the backward substitution\n"); 
        return NULL;
    }

    memset(x,0,n*sizeof(int));
    int tmp;

    for(int i = n - 1; i > -1; i--)
    {
        tmp = b[i];

        for(int j = i + 1; j < n; j++)
        {
            tmp = sub(tmp,((long) U->values[i][j] * x[j]) % p,p);
        }

        x[i] = ((long) tmp * inv(U->values[i][i],p)) % p;
    }
    
    return x;
}

int* linearSolveLU(const Matrix* L, const Matrix* U, const int* b, int p)
{
    int* y = forwardSub(L,b,p);
    int* x = backwardSub(U,y,p);
    free(y);
    return x;
}

bool assertLinearSolveLU(const Matrix* A, const int* x, const int* b, int p)
{
    int n = A->n;
    int tmp;

    for(int i = 0; i < n; ++i)
    {
        tmp = 0;

        for (int j = 0; j < n; ++j)
        {
            tmp = add(tmp,((long) A->values[i][j] * x[j]) % p,p);
        }

        if(tmp != b[i])
        {
            printf("Linear system solving using LU decomposition failed\n");
            return false;
        }
    }

    return true;
}

Matrix* LUInversion(const Matrix* A, const Matrix* L, const Matrix* U, int p, bool assert)
{
    int* tmp;
    bool check;
    int n = L->n;
    Matrix* I = newIdentity(n);
    Matrix* A_ = newMatrix(n); 

    for(int i = 0; i < n; i++)
    {
        tmp = linearSolveLU(L,U,I->values[i],p);
        check = !assert ? true : assertLinearSolveLU(A,tmp,I->values[i],p);

        if(!check)
        {
            printf("An assertion failed during the inversion of A using LU decomposition\n");
            freeMatrix(I);
            free(A_);
            free(tmp);
            return NULL;
        }

        for(int j = 0; j < n; j++)
        {
            A_->values[j][i] = tmp[j];
        }

        free(tmp);
    }

    freeMatrix(I);

    return A_;
}
