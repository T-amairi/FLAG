/**
 * @file Matrix.h
 * @author Tahar AMAIRI & Hamza RAIS
 * @brief Matrix structure and its functions
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "OperationModP.h"

/**
 * @brief a struct representing a square matrix 
 * 
 */
typedef struct Matrix
{
    int n; //the size 
    int** values; //its values mod p
} Matrix;

/**
 * @brief get a random value in the prime finite field ℤ/pℤ
 * 
 * @param p modulus p 
 * @return int : the random int 
 */
int getRandomValue(int p);

/**
 * @brief get a 1D array with random value mod p
 * 
 * @param n the size of the vector
 * @param p modulus p
 * @return int* : return the random vector
 */
int* getRandomVector(int n, int p);

/**
 * @brief create a new matrix struct with uninitialized value
 * 
 * @param n the size of the matrix
 * @return Matrix* : return the matrix pointer 
 */
Matrix* newMatrix(int n);

/**
 * @brief create a new identity matrix struct 
 * 
 * @param n the size of the matrix
 * @return Matrix* : return the identity matrix pointer  
 */
Matrix* newIdentity(int n);

/**
 * @brief create a new matrix struct with initialized value mod p
 * 
 * @param n the size of the matrix
 * @param p modulus p
 * @return Matrix* : return the matrix pointer 
 */
Matrix* newMatrixModP(int n, int p);

/**
 * @brief sum two matrices mod p
 * 
 * @param A a matrix 
 * @param B a matrix
 * @param p modulus p
 * @return Matrix* : return A + B
 */
Matrix* addMatrix(const Matrix* A, const Matrix* B, int p);

/**
 * @brief sub two matrices mod p
 * 
 * @param A a matrix
 * @param B a matrix
 * @param p modulus p
 * @return Matrix* : return A - B
 */
Matrix* subMatrix(const Matrix* A, const Matrix* B, int p);

/**
 * @brief sub two matrices and save the result in one of them mod p
 * 
 * @param A a matrix 
 * @param B a matrix 
 * @param p modulus p
 * @param invert if true, the result will be saved into B instead of A
 */
void subMatrixInPlace(Matrix* A, Matrix* B, int p, bool invert);

/**
 * @brief free the allocated memory for matrix
 * 
 * @param matrix the struct matrix to be freed 
 */
void freeMatrix(Matrix* matrix);

/**
 * @brief print a matrix
 * 
 * @param matrix the matrix to be printed
 */
void printMatrix(const Matrix* matrix);

/**
 * @brief print out the array x
 * 
 * @param x the vector to be printed
 * @param n the size of x
 */
void printVector(const int* x, int n);

/**
 * @brief check if the matrix A_ is the inverse of A mod p
 * 
 * @param A a matrix
 * @param A_ the inverse of A
 * @param p modulus p
 * @return true : A * A_ == I mod p
 * @return false : A * A_ != mod p
 */
bool assertMatrixInversion(const Matrix* A, const Matrix* A_, int p);