/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix
{
    int n;
    int** values;
} Matrix;

int getRandomValue(int p);
Matrix* newMatrix(int n, int p);
void freeMatrix(Matrix* matrix);
void printMatrix(Matrix* matrix);