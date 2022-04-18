/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
*/

#include "Benchmark.h"

Matrix* getInvertibleMatrix(int n, int p)
{
    Matrix* A;
    Matrix* AsT_;
    bool tmp = false;

    while(!tmp)
    {
        A = newMatrixModP(n,p);
        AsT_ = StrassenInversion(A,p,true);
        tmp = assertMatrixInversion(A,AsT_,p);

        if(tmp == 0)
        {
            freeMatrix(A);
            freeMatrix(AsT_);
        }
    }

    freeMatrix(AsT_);
    return A;
}

double getExecTimeProduct(const Matrix* A, const Matrix* B, int p, bool ifStrassenProduct)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    Matrix* C = ifStrassenProduct ? StrassenMultiplication(A,B,p) : naiveMultiplication(A,B,p);
    
    gettimeofday(&end, NULL);

    freeMatrix(C);
    return end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6;
}

double getExecTimeInversion_LU(const Matrix* A, int p)
{
    int n = A->n;
    Matrix* L = newMatrix(n);
    Matrix* U = newMatrix(n);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    LU(A,L,U,p);
    Matrix* A_ = LUInversion(A,L,U,p);
    
    gettimeofday(&end, NULL);

    freeMatrix(L);
    freeMatrix(U);
    freeMatrix(A_);
    
    return end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6;
}

double getExecTimeInversion_Strassen(const Matrix* A, int p, bool ifStrassenProduct)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    Matrix* A_ = StrassenInversion(A,p,ifStrassenProduct);
    
    gettimeofday(&end, NULL);

    freeMatrix(A_);
    
    return end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6;
}

void exportResults(int l, int p)
{
    FILE *fLU;
    FILE *fInvStr_str;
    FILE *fInvStr_naive;
    FILE *fProd_naive;
    FILE *fProd_str;

    fLU = fopen("./benchmark/LU.csv","w");
    fInvStr_str = fopen("./benchmark/InvStr_str.csv","w");
    fInvStr_naive = fopen("./benchmark/InvStr_naive.csv","w");
    fProd_naive = fopen("./benchmark/Prod_naive.csv","w");
    fProd_str = fopen("./benchmark/Prod_str.csv","w");

    Matrix* A;
    Matrix* B;

    for(int i = 0; i < l; i++)
    {
        int n = pow(2,i+1);

        printf("Computing for n = %d\n",n);

        printf("    Finding an invertible matrix...");
        A = getInvertibleMatrix(n,p);
        printf(" done\n");

        B = newMatrixModP(n,p);

        fprintf(fLU,"%d;%f\n",n,getExecTimeInversion_LU(A,p));
        printf("    LU inversion : done\n");

        fprintf(fInvStr_str,"%d;%f\n",n,getExecTimeInversion_Strassen(A,p,true));
        printf("    Strassen inversion (Strassen product): done\n");

        fprintf(fInvStr_naive,"%d;%f\n",n,getExecTimeInversion_Strassen(A,p,false));
        printf("    Strassen inversion (naive product): done\n");

        fprintf(fProd_naive,"%d;%f\n",n,getExecTimeProduct(A,B,p,false));
        printf("    Naive matrix product : done\n");

        fprintf(fProd_str,"%d;%f\n",n,getExecTimeProduct(A,B,p,true));
        printf("    Strassen matrix product : done\n");

        freeMatrix(A);
        freeMatrix(B);

        printf("\n");        
    }

    fclose(fLU);
    fclose(fInvStr_str);
    fclose(fInvStr_naive); 
    fclose(fProd_naive);
    fclose(fProd_str);

    printf("Finished measurements : results in the benchmark folder.\n");
}