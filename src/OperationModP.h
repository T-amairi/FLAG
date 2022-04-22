/**
 * @file OperationModP.h
 * @author Tahar AMAIRI & Hamza RAIS
 * @brief Operation modulus p
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <stdio.h>

/**
 * @brief compute the sum of x and y mod p
 * 
 * @param x an int 
 * @param y an int 
 * @param p modulus p
 * @return int : return x + y mod p
 */
int add(int x, int y, int p);

/**
 * @brief compute the subtraction of x and y mod p
 * 
 * @param x an int 
 * @param y an int 
 * @param p modulus p
 * @return int : return x - y mod p
 */
int sub(int x, int y, int p);

/**
 * @brief compute the inverse of x mod p using extended euclidean algorithm
 * 
 * @param x an int 
 * @param p modulus p
 * @return int : return 1/x mod p
 */
int inv(int x, int p);