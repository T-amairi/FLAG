/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
*/

#pragma once
#include <string.h>
#include "Matrix.h"
#include "OperationModP.h"

void LU(const Matrix* A, Matrix* L, Matrix* U, int p);
int assertLU(const Matrix* A, const Matrix* L, const Matrix* U, int p);

int* forwardSub(const Matrix* L, const int* b, int p);
int* backwardSub(const Matrix* U, const int* b, int p);
int* linearSolveLU(const Matrix* L, const Matrix* U, const int* b, int p);
int assertLinearSolveLU(const Matrix* A, const int* x, const int* b, int p);

Matrix* invertLU(const Matrix* A, const Matrix* L, const Matrix* U, int p);
int assertInvertLU(const Matrix* A, const Matrix* A_, int p);