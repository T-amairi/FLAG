/**
 * @file Benchmark.h
 * @author Tahar AMAIRI & Hamza RAIS
 * @brief Benchmark function to get the execution time of each implemented methods
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Benchmark.h"

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
    Matrix* A_ = LUInversion(A,L,U,p,false);
    
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

void exportResults(int l, int r, int p)
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

    double sumLU;
    double sumStrStr;
    double sumStrNaive;
    double sumProdNaive;
    double sumProdStr;
    int n;

    for(int i = 0; i < l; i++)
    {
        n = pow(2,i+1);
        sumLU = 0.0;
        sumStrStr = 0.0;
        sumStrNaive = 0.0;
        sumProdNaive = 0.0;
        sumProdStr = 0.0;

        printf("Computing for n = %d\n",n);

        for(int j = 0; j < r; j++)
        {
            printf("    Try count : %d\n",j + 1);

            A = newMatrixModP(n,p);
            B = newMatrixModP(n,p);

            sumLU += getExecTimeInversion_LU(A,p);
            printf("    LU inversion : done\n");

            sumStrStr += getExecTimeInversion_Strassen(A,p,true);
            printf("    Strassen inversion (Strassen product): done\n");

            sumStrNaive += getExecTimeInversion_Strassen(A,p,false);
            printf("    Strassen inversion (naive product): done\n");

            sumProdNaive += getExecTimeProduct(A,B,p,false);
            printf("    Naive matrix product : done\n");

            sumProdStr += getExecTimeProduct(A,B,p,true);
            printf("    Strassen matrix product : done\n\n");

            freeMatrix(A);
            freeMatrix(B);
        }

        fprintf(fLU,"%d;%f\n",n,sumLU / r);
        fprintf(fInvStr_str,"%d;%f\n",n,sumStrStr / r);
        fprintf(fInvStr_naive,"%d;%f\n",n,sumStrNaive / r);
        fprintf(fProd_naive,"%d;%f\n",n,sumProdNaive / r);
        fprintf(fProd_str,"%d;%f\n",n,sumProdStr / r);

        printf("\n");        
    }

    fclose(fLU);
    fclose(fInvStr_str);
    fclose(fInvStr_naive); 
    fclose(fProd_naive);
    fclose(fProd_str);

    printf("Finished measurements : results in the benchmark folder.\n");
}