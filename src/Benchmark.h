/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]
*/

#pragma once
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include "LU.h"
#include "Strassen.h"

Matrix* getInvertibleMatrix(int n, int p);

double getExecTimeProduct(const Matrix* A, const Matrix* B, int p, bool ifStrassenProduct);
double getExecTimeInversion_LU(const Matrix* A, int p);
double getExecTimeInversion_Strassen(const Matrix* A, int p, bool ifStrassenProduct);

void exportResults(int l, int p);