/**
 * @file OperationModP.h
 * @author Tahar AMAIRI & Hamza RAIS
 * @brief Operation modulus p
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "OperationModP.h"

int add(int x, int y, int p)
{
    int a = x + y;
    if(a >= p) return a - p;
    if(a < 0) return a + p;
    return a;
}

int sub(int x, int y, int p)
{
    int s = x - y;
    if(s >= p) return s - p;
    if(s < 0) return s + p;
    return s;
}

int inv(int x, int p)
{
    if(x == 1) return 1;

    if(x == 0)
    {
        printf("Can not divide by zero\n");
        exit(1);
        return -1;
    }
    
    int r0 = x, u0 = 1;
    int r1 = p, u1 = 0;
    int q, tmp;

    while(r1 != 0)
    {
        q = r0 / r1;
        
        tmp = u1;
        u1 = u0 - q * u1;
        u0 = tmp;

        tmp = r1;
        r1 = r0 % r1;
        r0 = tmp;
    }

    if(r0 != 1)
    {
        printf("Inverse of %d mod %d doesn't exist\n",x,p);
        exit(1);
        return -1;
    }

    if(u0 < 0) u0 += p;
    return u0;
}