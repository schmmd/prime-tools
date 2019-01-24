/* File: prime.c */

/* Copyright (c) 2005 Michael Schmitz
 * under the GNU General Public License
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * Please see the file LICENSE for more details.
 */

/* Program Summary:
 * The program accepts a number n, solves for all primes less than n
 * and then outputs those primes to the file output.txt. 
 *
 * primes.c checks if a number x is prime by dividing by all of the
 * primes less than sqrt(x).  If the number is prime, it stores it in
 * an array if it is less than sqrt(n) so that it can be recalled and
 * used in future calculations.  elimination.c provides a faster
 * method, but prime.c's method is much more memory efficient.
 */

#include "../primes.h"

int main() 
{
  /* Initialize variables */
  long count, min, max, maxfactor;
  FILE* fout;
  // ofstream fout;
  char* filename = "output.txt";

  /* Prompt welcome message and request input. */
  printf("Welcome to prime.exe - By Michael Schmitz\n");
  printf("Get all of the primes less than: ");
  scanf("%i", &max);
  min  =  3;
  if (max < 2)
  {
    printf("Value less than minimum (2)\nExiting...\n");
    return 0;
  }

  // Record the highest prime that needs to be stored
  long maxprime  = (long)sqrt((double)max);

  // Find max array bounds (will always fit primes up to maxprime)
  long ArraySize = (long)maxprime / 3 + 1;

  /* Make primes an array */
  long* primes = (long*)malloc(sizeof(long) * ArraySize);

  /* Fill primes array with 0 */
  memset(primes, 0, 4 * ArraySize);

  /* Open a handle to the output filename */
  fout = fopen(filename, "w");

  /* Handle prime number==2 */
  count = 1;
  output(fout, 2);

  /* Output start message and record start time */
  printf("\nSolving for primes... ");
  clock_t start = clock();

  /* Move position to begining of prime array */
  long* arraynode = primes;

  long number;
  for (number = min; number <= max; number += 2)
  {
    /* The number is prime until it is proven unprime */
    bool prime = true;
    
    /* A number is prime as long as it is not divisible 
     * by any primes less than maxfactor
     */
    maxfactor = (long)sqrt((double)number);  

    long* factor;
    for (factor = primes; *factor && *factor <= maxfactor; factor++)
    {
      //if there is no remainder (modulus is faster than division)
      if (number % *factor == 0) 
      {
        //number is not prime, loop will terminate because prime = false
        prime = false; 
        break;
      }
    }

    if (prime)
    {
      /* if the [prime]number <= maxprime we must store it in the
       * array of primes so that it can be recalled later. If it
       * is greater than maxprime it will never be called.
       */
	    
      if (number <= maxprime) 
        // Store the prime and increment array position
        *arraynode++ = number; 

      output(fout, number); 
      ++count;
    }
  }

  /* Record the stop time, calculate the duration, and then 
   * output the duration to the term
   */
  clock_t finish = clock();
  double duration = (double)(finish - start)/CLOCKS_PER_SEC;
  printf("(%.2f seconds)\n", duration);

  // Output operation summary
  printf("%i primes found in %.2f seconds.\n", count, duration);

  // Append summary to filename
  write_summary_to_file(fout, duration, count);

  fclose(fout);
  free(primes);

  return 0;
} 
