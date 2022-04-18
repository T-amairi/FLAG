/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
*/

#pragma once
#include <string.h>
#include "Matrix.h"

bool isPowerOfTwo(int x);

Matrix* naiveMultiplication(const Matrix* A, const Matrix* B, int p);
Matrix* StrassenMultiplication(const Matrix* A, const Matrix* B, int p);

void decomposeMatrix(const Matrix* M, Matrix* A, Matrix* B, Matrix* C, Matrix* D);
void mergeMatrix(Matrix* M, const Matrix* A, const Matrix* B, const Matrix* C, const Matrix* D);

Matrix* StrassenInversion(const Matrix* M, int p, bool ifStrassenProduct);