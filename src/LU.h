/**
 * @file LU.h
 * @author Tahar AMAIRI & Hamza RAIS
 * @brief Implementation of LU decomposition and inversion
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <string.h>
#include "Matrix.h"

/**
 * @brief compute the LU decomposition of A using Doolittle's method mod p
 * 
 * @param A the matrix to be decomposed 
 * @param L the lower matrix 
 * @param U the upper matrix
 * @param p modulus p
 */
void LU(const Matrix* A, Matrix* L, Matrix* U, int p);

/**
 * @brief check if A = LU mod p
 * 
 * @param A the decomposed matrix
 * @param L the lower matrix 
 * @param U the upper matrix
 * @param p modulus p
 * @return true : A == LU mod p 
 * @return false : A != LU mod p
 */
bool assertLU(const Matrix* A, const Matrix* L, const Matrix* U, int p);

/**
 * @brief forward substitution 
 * 
 * @param L the lower matrix
 * @param b rhs vector
 * @param p modulus p
 * @return int* : return a vector x such as Lx = b mod p 
 */
int* forwardSub(const Matrix* L, const int* b, int p);

/**
 * @brief backward substitution 
 * 
 * @param U the upper matrix
 * @param b rhs vector
 * @param p modulus p
 * @return int* : return a vector x such as Ux = b mod p 
 */
int* backwardSub(const Matrix* U, const int* b, int p);

/**
 * @brief solve the linear system LUx = b mod p using forward and backward substitutions
 * 
 * @param L the lower matrix
 * @param U the upper matrix
 * @param b rhs vector 
 * @param p modulus p
 * @return int* : return a vector x such as LUx = b mod p 
 */
int* linearSolveLU(const Matrix* L, const Matrix* U, const int* b, int p);

/**
 * @brief check if Ax = b mod p 
 * 
 * @param A the matrix of the linear system
 * @param x lhs vector
 * @param b rhs vector
 * @param p modulus p
 * @return true : Ax == b mod p 
 * @return false : Ax != b mod p
 */
bool assertLinearSolveLU(const Matrix* A, const int* x, const int* b, int p);

/**
 * @brief compute the inverse of A using the LU decomposition and by revolving linear system mod p
 * 
 * @param A the matrix to be inverted
 * @param L the lower matrix
 * @param U the upper matrix
 * @param p modulus p
 * @param assert if true, check if the linear system is correct at each step of the inversion otherwise not
 * @return Matrix* : return M^-1
 */
Matrix* LUInversion(const Matrix* A, const Matrix* L, const Matrix* U, int p, bool assert);