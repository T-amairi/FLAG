/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix
{
    int n;
    int** values;
} Matrix;

int getRandomValue(int p);
int* getRandomVector(int n, int p);

Matrix* newMatrix(int n);
Matrix* newIdentity(int n);
Matrix* newMatrixModP(int n, int p);

void freeMatrix(Matrix* matrix);
void printMatrix(const Matrix* matrix);
void printVector(const int* x, int n);