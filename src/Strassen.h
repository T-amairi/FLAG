/**
 * @file Strassen.h
 * @author Tahar AMAIRI & Hamza RAIS
 * @brief Implementation of Strassen inversion and multiplication
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include "Matrix.h"

/**
 * @brief check if an int is a power of two
 * 
 * @param x the value to be checked
 * @return true : x is a power of two 
 * @return false : x is not a power of two
 */
bool isPowerOfTwo(int x);

/**
 * @brief compute the naive product between two matrices mod p
 * 
 * @param A first matrix
 * @param B second matrix
 * @param p the modulus
 * @return Matrix* : return the result of A*B
 */
Matrix* naiveMultiplication(const Matrix* A, const Matrix* B, int p);

/**
 * @brief compute the product between two matrices using the Strassen algorithm
 * 
 * @param A first matrix
 * @param B second matrix
 * @param p the modulus
 * @return Matrix* : return the result of A*B
 */
Matrix* StrassenMultiplication(const Matrix* A, const Matrix* B, int p);

/**
 * @brief decompose the matrix M into 4 equally sized matrices : A,B,C and D
 * 
 * @param M the matrix to be decomposed 
 * @param A the first quarter of the matrix M 
 * @param B the second quarter of the matrix M
 * @param C the third quarter of the matrix M
 * @param D the last quarter of the matrix M
 */
void decomposeMatrix(const Matrix* M, Matrix* A, Matrix* B, Matrix* C, Matrix* D);

/**
 * @brief merge the matrices A,B,C and D into one matrix M
 * 
 * @param M the target matrix
 * @param A the first quarter to be merged
 * @param B the second quarter to be merged
 * @param C the third quarter to be merged
 * @param D the last quarter to be merged
 */
void mergeMatrix(Matrix* M, const Matrix* A, const Matrix* B, const Matrix* C, const Matrix* D);

/**
 * @brief fourth step of the Strassen inversion algorithm, see : https://specfun.inria.fr/bostan/mpri/DenseLinAlg.pdf page 48
 * 
 * @param M the target matrix where the inverse will be saved
 * @param A matrix E in the link 
 * @param B matrix EBTCE in the link 
 * @param C matrix EBT in the link
 * @param D matrix TCE in the link
 * @param E matrix T in the link
 * @param p modulus p
 */
void recoverMatrixInverse(Matrix* M, const Matrix* A, const Matrix* B, const Matrix* C, const Matrix* D, const Matrix* E, int p);

/**
 * @brief compute the inverse of M using the Strassen algorithm mod p
 * 
 * @param M the matrix to be inverted
 * @param p modulus p
 * @param ifStrassenProduct if true, the function will use the Strassen multiplication algorithm instead of the naive one 
 * @return Matrix* : return M^-1
 */
Matrix* StrassenInversion(const Matrix* M, int p, bool ifStrassenProduct);