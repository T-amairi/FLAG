/**
 * @file Strassen.c
 * @author Tahar AMAIRI & Hamza RAIS
 * @brief Implementation of Strassen inversion and multiplication
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Strassen.h"
 
//if a size of a matrix is below this value, the StrassenMultiplication function will use the naive multiplication
int fastThreshold = 64;

bool isPowerOfTwo(int x)
{
    return (x != 0) && ((x & (x - 1)) == 0);
}

Matrix* naiveMultiplication(const Matrix* A, const Matrix* B, int p)
{
    int tmp;
    int n = A->n;
    Matrix* C = newMatrix(n);

    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            tmp = 0;

            for (int k = 0; k < n; ++k)
            {
                tmp = add(tmp,((long) A->values[i][k] * B->values[k][j]) % p,p);
            }

            C->values[i][j] = tmp;
        }
    }

    return C;
}

Matrix* StrassenMultiplication(const Matrix* A, const Matrix* B, int p)
{
    int n = A->n;

    if(!isPowerOfTwo(n))
    {
        printf("The size of the matrices is not a power of 2, can not compute the product A*B using Strassen\n");
        return NULL;
    }

    if(n <= fastThreshold)
    {
        return naiveMultiplication(A,B,p);
    }

    if(n == 1)
    {
        Matrix* C = newMatrix(1);
        C->values[0][0] = ((long) A->values[0][0] * B->values[0][0]) % p;
        return C;
    }

    int m = n / 2;

    Matrix* a = newMatrix(m);
    Matrix* b = newMatrix(m);
    Matrix* c = newMatrix(m);
    Matrix* d = newMatrix(m);
    Matrix* x = newMatrix(m);
    Matrix* y = newMatrix(m);
    Matrix* z = newMatrix(m);
    Matrix* t = newMatrix(m);

    decomposeMatrix(B,x,y,z,t);
    decomposeMatrix(A,a,b,c,d);

    Matrix* tmp1 = addMatrix(x,z,p);
    Matrix* q1 = StrassenMultiplication(a,tmp1,p);
    freeMatrix(tmp1);

    Matrix* tmp2 = addMatrix(y,t,p);
    Matrix* q2 = StrassenMultiplication(d,tmp2,p);
    freeMatrix(tmp2);

    tmp1 = subMatrix(d,a,p);
    tmp2 = subMatrix(z,y,p);
    Matrix* q3 = StrassenMultiplication(tmp1,tmp2,p);
    freeMatrix(tmp1);
    freeMatrix(tmp2);

    tmp1 = subMatrix(b,d,p);
    tmp2 = addMatrix(z,t,p);
    Matrix* q4 = StrassenMultiplication(tmp1,tmp2,p);
    freeMatrix(tmp1);
    freeMatrix(tmp2);

    tmp1 = subMatrix(b,a,p);
    Matrix* q5 = StrassenMultiplication(tmp1,z,p);
    freeMatrix(tmp1);
    
    tmp1 = subMatrix(c,a,p);
    tmp2 = addMatrix(x,y,p);
    Matrix* q6 = StrassenMultiplication(tmp1,tmp2,p);
    freeMatrix(tmp1);
    freeMatrix(tmp2);

    tmp1 = subMatrix(c,d,p);
    Matrix* q7 = StrassenMultiplication(tmp1,y,p);
    freeMatrix(tmp1);

    Matrix* r11 = addMatrix(q1,q5,p);
    Matrix* r22 = addMatrix(q2,q7,p);

    tmp1 = addMatrix(q2,q3,p);
    tmp2 = subMatrix(q4,q5,p);
    Matrix* r12 = addMatrix(tmp1,tmp2,p);
    freeMatrix(tmp1);
    freeMatrix(tmp2);

    tmp1 = addMatrix(q1,q3,p);
    tmp2 = subMatrix(q6,q7,p);
    Matrix* r21 = addMatrix(tmp1,tmp2,p);
    freeMatrix(tmp1);
    freeMatrix(tmp2);

   Matrix* C = newMatrix(n);
   mergeMatrix(C,r11,r12,r21,r22);

   freeMatrix(a);
   freeMatrix(b);
   freeMatrix(c);
   freeMatrix(d);
   freeMatrix(x);
   freeMatrix(y);
   freeMatrix(z);
   freeMatrix(t);
   freeMatrix(q1);
   freeMatrix(q2);
   freeMatrix(q3);
   freeMatrix(q4);
   freeMatrix(q5);
   freeMatrix(q6);
   freeMatrix(q7);
   freeMatrix(r11);
   freeMatrix(r12);
   freeMatrix(r21);
   freeMatrix(r22);
   
    return C;
}

void decomposeMatrix(const Matrix* M, Matrix* A, Matrix* B, Matrix* C, Matrix* D)
{
    int n = M->n;

    if(!isPowerOfTwo(n))
    {
        printf("The size of M is not a power of 2, can not decompose it\n");
        return;
    }

    int m = n / 2;

    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if(i < m)
            {
                if(j < m)
                {
                    A->values[i][j] = M->values[i][j];
                }

                else
                {
                    B->values[i][j - m] = M->values[i][j];
                }
            }

            else
            {
                if(j < m)
                {
                    C->values[i - m][j] = M->values[i][j];
                }

                else
                {
                    D->values[i - m][j - m] = M->values[i][j];
                }
            }
        }
    }
}

void mergeMatrix(Matrix* M, const Matrix* A, const Matrix* B, const Matrix* C, const Matrix* D)
{
    int n = M->n;

    if(!isPowerOfTwo(n))
    {
        printf("The size of M is not a power of 2, can not merge it\n");
        return;
    }

    int m = n / 2;

    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if(i < m)
            {
                if(j < m)
                {
                    M->values[i][j] = A->values[i][j];
                }

                else
                {
                    M->values[i][j] = B->values[i][j - m];
                }
            }

            else
            {
                if(j < m)
                {
                    M->values[i][j] = C->values[i - m][j];
                }

                else
                {
                    M->values[i][j] = D->values[i - m][j - m];
                }
            }
        }
    }
}

void recoverMatrixInverse(Matrix* M, const Matrix* A, const Matrix* B, const Matrix* C, const Matrix* D, const Matrix* E, int p)
{
    int n = M->n;

    if(!isPowerOfTwo(n))
    {
        printf("The size of M is not a power of 2, can not merge it\n");
        return;
    }

    int m = n / 2;

    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if(i < m)
            {
                if(j < m)
                {
                    M->values[i][j] = add(A->values[i][j],B->values[i][j],p);
                }

                else
                {                       
                    M->values[i][j] = C->values[i][j - m] ? (C->values[i][j - m] * -1) + p : 0;
                }
            }

            else
            {
                if(j < m)
                {
                    M->values[i][j] = D->values[i - m][j] ? (D->values[i - m][j] * -1) + p : 0;
                }

                else
                {
                    M->values[i][j] = E->values[i - m][j - m];
                }
            }
        }
    }
}

Matrix* StrassenInversion(const Matrix* M, int p, bool ifStrassenProduct)
{
    int n = M->n;

    if(n == 1)
    {
        Matrix* M_ = newMatrix(1);
        M_->values[0][0] = inv(M->values[0][0],p);
        return M_;
    }

    if(!isPowerOfTwo(n))
    {
        printf("The size of M is not a power of two, can not invert M using Strassen\n");
        return NULL;
    }

    int m = n / 2;

    Matrix* A = newMatrix(m);
    Matrix* B = newMatrix(m);
    Matrix* C = newMatrix(m);
    Matrix* D = newMatrix(m);

    decomposeMatrix(M,A,B,C,D);

    Matrix* E = StrassenInversion(A,p,ifStrassenProduct);
    Matrix* TMP1 = ifStrassenProduct ? StrassenMultiplication(C,E,p) : naiveMultiplication(C,E,p); //CE
    Matrix* TMP2 = ifStrassenProduct ? StrassenMultiplication(TMP1,B,p) : naiveMultiplication(TMP1,B,p); //CEB
    subMatrixInPlace(D,TMP2,p,true); //Z

    Matrix* T = StrassenInversion(TMP2,p,ifStrassenProduct);
    Matrix* M_ = newMatrix(n);

    freeMatrix(TMP1);
    freeMatrix(TMP2);

    TMP1 =  ifStrassenProduct ? StrassenMultiplication(E,B,p) : naiveMultiplication(E,B,p); //EB
    TMP2 = ifStrassenProduct ? StrassenMultiplication(TMP1,T,p) : naiveMultiplication(TMP1,T,p); //EBT

    Matrix* TMP3 = ifStrassenProduct ? StrassenMultiplication(T,C,p) : naiveMultiplication(T,C,p); //TC
    Matrix* TMP4 = ifStrassenProduct ? StrassenMultiplication(TMP3,E,p) : naiveMultiplication(TMP3,E,p); //TCE
    
    freeMatrix(TMP3);
    TMP3 = ifStrassenProduct ? StrassenMultiplication(TMP1,TMP4,p) : naiveMultiplication(TMP1,TMP4,p); //EBTCE
   
    recoverMatrixInverse(M_,E,TMP3,TMP2,TMP4,T,p);

    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(C);
    freeMatrix(D);
    freeMatrix(E);
    freeMatrix(T);
    freeMatrix(TMP1);
    freeMatrix(TMP2);
    freeMatrix(TMP3);
    freeMatrix(TMP4);

    return M_;
}
