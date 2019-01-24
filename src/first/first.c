/* File: first.c */

/* Copyright (c) 2005 Michael Schmitz
 *
 * LICENSE
 */

/* Program Summary:
 * This program accepts a number n, solves for the first n primes, and
 * then outputes those primes to the file output.txt.
 *
 * first.c check if a number x is prime using a method similar to
 * prime.c.  It divides the (odd) number by all of the primes from 3
 * to sqrt(x) to determine whether a factor exists.
 */

#include "../primes.h"

int main() 
{
  long factor, factorIndex;
  FILE* fout;

  long maxfactor;

  long numprimes, Numfactors = 0;

  long double duration = 0;

  char* filename = "output.txt";

  /* Print welcome screen and get input. */
  printf("Welcome to prime.exe - By Michael S.\n\n");
  printf("Enter the number of primes to find: ");
  scanf("%i", numprimes);
  printf("\n");
  if (numprimes < 2)
  {
    printf("Value less than minimum (2)\nExiting...\n");
    return 0;
  }

  /* Find max array bounds (will always fit primes up to numprimes)
   * create the array, and initialize the array with zero values.
   */
  long ArraySize = (long)numprimes / 3 + 1;
  
  long* primes = (long*)malloc(sizeof(long) * ArraySize);
  memset(primes, 0, 4 * ArraySize);
  
  long* arraynode = primes;

  fopen(filename, "w");

  // Handle number==2
  long min = 3;
  output(fout, 2);
  long primesfound = 1;

  printf("starting program...");
  clock_t start = clock();

  long number;
  for (number = min; primesfound < numprimes; number += 2)
  {
    // The number is prime until it is proven unprime
    bool prime = true; 
    
    /* A number is prime as long as it is not divisible 
     * by any primes less than maxfactor
     */
    maxfactor = (long)sqrt((double)number);  

    long* factor;
    for (factor = primes; *factor && *factor <= maxfactor; factor++) 
    {
      /* if there is no remainder (modules if faster than division) */
      if (number % *factor == 0) 
      {
        /* number is not prime, loop will terminate because prime = false */
        prime = false; 
        break;
      }
    }

    if (prime)
    {
      if (number <= numprimes)
        /* Add 1 after because it first sets 0 to 3 */
        *arraynode++ = number; 

      /* output prime */
      output(fout, number); 
      ++primesfound;
    }
  }

  /* Record stop time, calculate the duration, and output to the screen. */
  clock_t finish = clock();
  duration = (double)(finish - start)/CLOCKS_PER_SEC;

  // output number of primes found
  printf("%i primes found in %.2f seconds.\n\n\n", primesfound, duration);

  // Append summary to file
  write_summary_to_file(fout, duration, primesfound);

  fclose(fout);
  free(primes);

  return 0;
} 
