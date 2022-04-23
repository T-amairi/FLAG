/**
 * @file Benchmark.h
 * @author Tahar AMAIRI & Hamza RAIS
 * @brief Benchmark function to get the execution time of each implemented methods
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include "LU.h"
#include "Strassen.h"

/**
 * @brief get the execution time of the operation A*B mod p
 * 
 * @param A a matrix
 * @param B a matrix 
 * @param p modulus p
 * @param ifStrassenProduct if true, the function uses the Strassen multiplication instead of the naive one 
 * @return double : return the execution time in seconds
 */
double getExecTimeProduct(const Matrix* A, const Matrix* B, int p, bool ifStrassenProduct);

/**
 * @brief get the execution time of the LU inversion mod p
 * 
 * @param A the matrix to be inverted
 * @param p modulus p
 * @return double : return the execution time in seconds
 */
double getExecTimeInversion_LU(const Matrix* A, int p);

/**
 * @brief Get the ExecTimeInversion Strassen object
 * 
 * @param A the matrix to be inverted
 * @param p modulus p
 * @param ifStrassenProduct if true, the function uses the Strassen multiplication instead of the naive one
 * @return double : return the execution time in seconds
 */
double getExecTimeInversion_Strassen(const Matrix* A, int p, bool ifStrassenProduct);

/**
 * @brief export for each implemented methods its execution time in a CSV file 
 * 
 * @param l set the maximum size of matrices during the benchmark test such as n = 2^l
 * @param r number of test repetition for each size 
 * @param p modulus p
 */
void exportResults(int l, int r, int p);