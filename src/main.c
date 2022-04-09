/* 
 - Tahar AMAIRI & Hamza RAIS
 - MAIN4 Polytech Sorbonne
 - FLAG : [Implementation project]

 USAGE: 
    $ ./project.out --prime 293 --size 2
*/

#include <time.h>
#include <getopt.h>
#include <math.h>
#include <err.h>

#include "Matrix.h"

int p = 293;
int n = 2;

int isPrime(int p)
{
    if(p <= 1 || p % 2 == 0) return 0;
    if(p == 2) return 1;

    int boundary = (int) floor(sqrt(p)); 

    for(int i = 3; i <= boundary; i += 2)
    {
        if(p % i == 0) return 0;
    }

    return 1;
}

void usage(char ** argv)
{
	printf("%s [OPTIONS]\n\n", argv[0]);
	printf("Options:\n");
	printf("--prime p               compute in the prime finite field ℤ/pℤ [default 293]\n");
	printf("--size n                size of the square matrix [default 2]\n");
	exit(0);
}

void process_command_line_options(int argc, char ** argv)
{
    struct option opts[3] = 
    {
		{"prime", required_argument, NULL, 'p'},
		{"size", required_argument, NULL, 's'},
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
            default:
                errx(1, "Unknown option\n");
		}
	}

	if(p > 0x3fffffff || !isPrime(p))
    {
        errx(1, "p have to be a prime number of size at most 30 bits.\n");
		exit(1);
	}
}

int main(int argc, char ** argv)
{
    process_command_line_options(argc, argv);

    srand(time(NULL));
    
    Matrix* matrix = newMatrix(n,p);
    printMatrix(matrix);
    freeMatrix(matrix);

    return 0;
}