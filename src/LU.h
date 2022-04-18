/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
*/

#pragma once
#include <string.h>
#include "Matrix.h"

void LU(const Matrix* A, Matrix* L, Matrix* U, int p);
bool assertLU(const Matrix* A, const Matrix* L, const Matrix* U, int p);

int* forwardSub(const Matrix* L, const int* b, int p);
int* backwardSub(const Matrix* U, const int* b, int p);
int* linearSolveLU(const Matrix* L, const Matrix* U, const int* b, int p);
bool assertLinearSolveLU(const Matrix* A, const int* x, const int* b, int p);

Matrix* LUInversion(const Matrix* A, const Matrix* L, const Matrix* U, int p);