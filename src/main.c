/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]

 USAGE: 
    $ ./project.out --prime 293 --size 2
*/

#include <getopt.h>
#include <err.h>
#include <time.h>
#include "Benchmark.h"

int p = 293;
int n = 4;
bool isDemo = true;
bool isBench = false;
int l = 10;

bool isPrime(int p)
{
    if(p <= 1 || p % 2 == 0) return 0;
    if(p == 2) return 1;

    int boundary = (int) floor(sqrt(p)); 

    for(int i = 3; i <= boundary; i += 2)
    {
        if(p % i == 0) return false;
    }

    return true;
}

void usage(char ** argv)
{
	printf("%s [OPTIONS]\n\n", argv[0]);
	printf("Options:\n");
	printf("--prime p               compute in the prime finite field ℤ/pℤ. [default 293]\n");
	printf("--size n                size of the square matrix (have to be a power of 2). [default 4]\n");
    printf("--demo d                execute a demo using all the functions : 0 (false). [default true, i.e, != 0]\n");
	printf("--test t                measure the execution time and export the result into a CSV format : 0 (false). [default 0, i.e, == 0]\n");
    printf("--limit l               to set the maximum size of n during the benchmark test such as n = 2^l (have to be greater than 0). [default 10]\n\n");
}

void basicDemo(int n, int p)
{
    printf("Modulus p: %d, size: %dx%d\n\n",p,n,n);

    Matrix* A = getInvertibleMatrix(n,p);
    
    printf("|********* The randomly generated matrix A *********|\n");
    printf("Matrix A:\n");
    printMatrix(A);

    printf("|********* LU decomposition *********|\n");

    Matrix* L = newMatrix(n);
    Matrix* U = newMatrix(n);
    LU(A,L,U,p);

    printf("Matrix L:\n");
    printMatrix(L);
    printf("Matrix U:\n");
    printMatrix(U);

    printf("Assertion of A = LU : %d\n\n",assertLU(A,L,U,p));

    printf("|********* Linear system solving using the LU decomposition *********|\n");
    printf("System: Ax = b\n");

    int* b = getRandomVector(n,p);
    int* x = linearSolveLU(L,U,b,p);

    printf("Vector b : "); printVector(b,n);
    printf("Solution x : "); printVector(x,n);
    printf("\nAssertion of Ax = b : %d\n\n",assertLinearSolveLU(A,x,b,p));

    printf("|********* Matrix inversion using the LU decomposition *********|\n");
    printf("Inverse of A:\n");

    Matrix* A_ = LUInversion(A,L,U,p);
    printMatrix(A_);
    printf("Assertion of A*A-1 = I (LU): %d\n\n",assertMatrixInversion(A,A_,p));

    printf("|********* Matrix inversion via the Strassen algorithm with naive product *********|\n");
    printf("Inverse of A:\n");

    Matrix* AsF_ = StrassenInversion(A,p,false);
    printMatrix(AsF_);
    printf("Assertion of A*A-1 = I (Strassen + naive product): %d\n\n",assertMatrixInversion(A,AsF_,p));

    printf("|********* Matrix inversion via the Strassen algorithm with Strassen product *********|\n");
    printf("Inverse of A:\n");

    Matrix* AsT_ = StrassenInversion(A,p,true);
    printMatrix(AsT_);    
    printf("Assertion of A*A-1 = I (Strassen + Strassen product): %d\n\n",assertMatrixInversion(A,AsT_,p));

    freeMatrix(A);
    freeMatrix(L);
    freeMatrix(U);
    freeMatrix(A_);
    freeMatrix(AsF_);
    freeMatrix(AsT_);
    free(b);
    free(x);
}

void processCommandLine(int argc, char ** argv)
{
    struct option opts[6] = 
    {
		{"prime", required_argument, NULL, 'p'},
		{"size", required_argument, NULL, 's'},
        {"demo", required_argument, NULL, 'd'},
        {"test", required_argument, NULL, 't'},
        {"limit", required_argument, NULL, 'l'},
		{NULL, 0, NULL, 0}
	};

	char ch;

	while((ch = getopt_long(argc, argv, "", opts, NULL)) != -1)
    {
		switch(ch)
        {
            case 'p':
                p = atoi(optarg);
                break;
            case 's':
                n = atoi(optarg);
                break;
            case 'd':
                isDemo = atoi(optarg);
                break;
            case 't':
                isBench = atoi(optarg);
                break;
            case 'l':
                l = atoi(optarg);
                break;
            default:
                errx(1, "Unknown option\n");
		}
	}

	if(p > 0x3fffffff || !isPrime(p))
    {
        errx(1, "p have to be a prime number of size at most 30 bits.\n");
		exit(1);
	}

    if(n <= 0 || !isPowerOfTwo(n))
    {
        errx(1, "n have to be a power of 2 and greater than 0.\n");
		exit(1);
	}

    if(l <= 0)
    {
        errx(1, "l have to be  greater than 0.\n");
		exit(1);
	}
}

int main(int argc, char ** argv)
{
    srand(time(NULL));

    argc > 1 ? processCommandLine(argc, argv) : usage(argv);

    if(isDemo) basicDemo(n,p);
    if(isBench) exportResults(l,p); 

    return 0;
}