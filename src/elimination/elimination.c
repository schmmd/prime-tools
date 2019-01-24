/* File: elimination.c */

/* Copyright (c) 2005 Michael Schmitz
 *
 * LICENSE
 */

/* Program Summary: 
 * The program accepts a number n, solves for all primes less than n
 * and then outputs those primes to the file output.txt. 
 *
 * This funcitonality is identical the program "prime".  However,
 * elimination.c uses the Sieve of Eratosthenes to solve for primes.
 * This method involves creating an array of all numbers and then
 * crossing off the multiples of primes, leaving only prime numbers
 * behind.  This is a much facter process, but it demands gross amounts
 * of memory as a long value must be allocated numbers 2 to n.
 */

#include "../primes.h"

#define COMPOSITE 1

int main() 
{
  time_t start, finish;
  double duration;

  long max;

  FILE* fout;
  char outputFile[128] = "output.txt";

  /* Output introduction message and prompt for max value.
   * The max value is n where the program solves for all
   * primes less than n.
   */
  printf("Welcome to Elimination.exe - By Michael Schmitz\n\n");
  printf("Get all of the primes less than or equal to: ");
  scanf("%i", &max);
  long min  =  2;

  printf("\n");

  if (max < min)
  {
    printf ("Value less than minimum (%i)\nExiting...\n", min);
    return true;
  }

  fout = fopen(outputFile, "w");

  // Record start time
  clock_t BeginProgram = clock();

  //Message process
  printf("     Filling and creating array... ");

  start = clock();

  /* Solve for the total size of the array. The +1 makes it inclusive with
   * max. Then create the primes array with one extra node that will be set
   * to null so the end can be detected. If insufficient memory exists, output
   * an error message to the terminal.
   */
  long total = max - min + 1; 
  long* primes = (long*)malloc(sizeof(long) * (total + 1));
  //long* primes = new long[total + 1]; //Create primes array
  if (!primes)
  {
    printf("Error!\nNot enough memory to hold %i four-byte integer variables\n",           max);
    printf("%i bytes\n%.2f kb\n%.2f mb\n", 
           max, 
           max*4, 
           max / 256.0, 
           max / 256.0 /1024.0);
	
    return true;
  }

  /* Fill the primes array from 2 to max. Terminate the array with NULL. */
  long index;
  for (index = 0; index < total; ++index)
    primes[index] = index + min;
  primes[total] = 0;

  finish = clock();

  /* Output a summary of the time needed to complete the operations and the
   * memory allocated for the array.
   */

  duration = (double)(finish - start) / CLOCKS_PER_SEC;
  printf("(%.2f seconds) ",  duration);
  printf("%ib %.2fkb %.2fmb\n", max, max*4, max / 256.0, max / 256.0 /1024.0);

  printf("     Eliminating composites...     ");
  
  /* Count for number 1 as a composite. count counts the number of composites
   * until below.
   */
  long count = 1; 
  
  start = clock();
  long root = (long)sqrt((double) max);
 
  long number, factor;
  long *p, *q;
  for (p = primes, number = *p; number <= root; p++, number = *p)
  {
    /* If number is not prime, all of the numbers that would be crossed out 
     * would already have been by its factors. 
     */
    if (number != COMPOSITE) 
    {
      // For each multiple of number
      for (factor = number * 2, q = (primes) + (factor - min);  
           factor <= max; 
	   q += number, factor += number) 
      {
	      // If *q is prime, then cross off multiples
        if (*q != COMPOSITE)
        {
          // Multiple of a prime is not prime
          *q = COMPOSITE; 
          ++count;
        }
      }
    }
  }
  finish = clock(); //eq time loop finished
  duration = (double)(finish - start) / CLOCKS_PER_SEC;
  printf("(%.2f seconds) composites\n", duration);

  printf( "     outputing primes...           ");
  
  /* Count the number of primes and enter it into count. */
  count = 0;
  start = clock();
  for (p = primes; *p != 0; p++)
  {
    if (*p != COMPOSITE)
        {
            fprintf(fout, "%i\n", *p);
            ++count;
        }
  }
  finish = clock();
  duration = (double)(finish - start)/CLOCKS_PER_SEC;
  printf("(%.2f seconds) primes\n", duration);

  clock_t EndProgram = clock();

  duration = (double)(EndProgram - BeginProgram) / CLOCKS_PER_SEC;
  printf("\nOperation Complete (%.2f seconds)\n\n", duration);
 
  duration = (double)(EndProgram - BeginProgram)/CLOCKS_PER_SEC;
  fprintf(fout, 
          "--------------------------Summary---------------------------\n");
  fprintf(fout, "duration: %.2f seconds\n", duration);
  fprintf(fout, "number of primes: %i\n\n\n", count);

  fclose(fout);
  free(primes);

  return 1;
}
