/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "OperationModP.h"

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

Matrix* addMatrix(const Matrix* A, const Matrix* B, int p);
Matrix* subMatrix(const Matrix* A, const Matrix* B, int p);
void negMatrix(Matrix* A, int p);

void freeMatrix(Matrix* matrix);
void printMatrix(const Matrix* matrix);
void printVector(const int* x, int n);

bool assertMatrixInversion(const Matrix* A, const Matrix* A_, int p);