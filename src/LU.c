/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
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
                tmp = add(tmp ,(L->values[i][k] * U->values[k][j]) % p,p);
            }
            
            U->values[i][j] = sub(A->values[i][j],tmp,p);
        }
 
        for (int j = i; j < n; j++)
        {
            tmp = 0;

            for (int k = 0; k < i; k++)
            {
                tmp = add(tmp,(L->values[j][k] * U->values[k][i]) % p,p); 
            }

            L->values[j][i] = (sub(A->values[j][i],tmp,p) * inv(U->values[i][i],p)) % p;
        }
    }
}

int assertLU(const Matrix* A, const Matrix* L, const Matrix* U, int p)
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
                tmp = add(tmp,(L->values[i][k] * U->values[k][j]) % p,p);
            }

            if(tmp != A->values[i][j])
            {
                printf("LU decomposition failed the assertion A = LU\n");
		        return 0;
            }
        }
    }

    return 1;
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
            tmp = sub(tmp,(L->values[i][j] * x[j]) % p,p);
        }

        x[i] = (tmp * inv(L->values[i][i],p)) % p;
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
            tmp = sub(tmp,(U->values[i][j] * x[j]) % p,p);
        }

        x[i] = (tmp * inv(U->values[i][i],p)) % p;
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

int assertLinearSolveLU(const Matrix* A, const int* x, const int* b, int p)
{
    int n = A->n;
    int tmp;

    for(int i = 0; i < n; ++i)
    {
        tmp = 0;

        for (int j = 0; j < n; ++j)
        {
            tmp = add(tmp,(A->values[i][j] * x[j]) % p,p);
        }

        if(tmp != b[i])
        {
            printf("Linear system solving using LU decomposition failed\n");
            return 0;
        }
    }

    return 1;
}

Matrix* invertLU(const Matrix* A, const Matrix* L, const Matrix* U, int p)
{
    int* tmp;
    int check;
    int n = L->n;
    Matrix* I = newIdentity(n);
    Matrix* A_ = newIdentity(n); 

    for(int i = 0; i < n; i++)
    {
        tmp = linearSolveLU(L,U,I->values[i],p);
        check = assertLinearSolveLU(A,tmp,I->values[i],p);

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

int assertInvertLU(const Matrix* A, const Matrix* A_, int p)
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
                    printf("LU inversion failed the assertion A*A-1 = I\n");
		            return 0;
                }
            }

            else
            {
                if(tmp != 0)
                {
                    printf("LU inversion failed the assertion A*A-1 = I\n");
		            return 0;
                }
            }
        }
    }

    return 1;
}