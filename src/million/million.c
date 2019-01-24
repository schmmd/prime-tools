/* File: prime.c */

/* Copyright (c) 2005 Michael Schmitz
 *
 * LICENSE
 */

/* Program Summary:
 * The program accepts a number n and then solves for all of the
 * primes less than n-million in batches.  Primes are computed using
 * the same strategy employed in prime.c, but they are outputted into
 * files with name structure "outputxx.txt" where xx equals the lower
 * bound of the prime range divided by 1M (in other words,
 * output00.txt contains the primes between 0 and 1M, output01.txt
 * contains the primes between 1M and 2M).  Feedback is sent to the
 * terminal at the completion of each 1M range.
 */


#include "../primes.h"

int main() 
{
  bool prime;
  long factor, factorindex;
  FILE* fout;

  long min, max, maxfactor, factorsfound = 0;
  long maximum;

  double duration;

  int filenumber = 0;

  // Setup variables
  min = 1;
  max = 1000000;

  // Prompt welcome message and request number of millions to search
  printf("Welcome to Millions.exe - By Michael Schmitz\n\n");
  printf("Please enter the number of millions you would like to reach: ");
  scanf("%i", &maximum);
  printf("\n");

  // End if maximum is less than 1
  if (maximum < min)
  {
    printf("Value less than minimum (%i)\nExiting...", min);
    return true;
  }

  // Convert maximum to millions by '*= 1 million'
  maximum *= 1000000; 

  // Record the highest prime that needs to be stored
  long maxprime  = (long)sqrt((double)maximum);

  // Find max array bounds (will always fit primes up to maxprime)
  long ArraySize = (long)maxprime / 3 + 1;
  
  // Create the prime array
  // double duration;
  long* primes = (long*)malloc(sizeof(long) * ArraySize);
  //primes = new long[ArraySize];

  // Fill primes array with 0
  memset(primes, 0, 4 * ArraySize);

  long number = 0;
  long totalprimesfound = 0;

  // Store program start_time time
  clock_t program_start_time = clock();
  while (number <= maximum)
  {
    // Reset number of primes found
    long primesfound = 0; 

    // Build file string
    char filename[81];
    sprintf  (filename, "output%i.txt", filenumber);
    fopen(filename, "w");

    // Handle "2"
    if (filenumber == 0)
    {
      output(fout, 2);
      primesfound = 1;
      min = 3;
    }

    // Store start_time time
    clock_t start_time = clock();
    for (number = min; number <= max; number += 2)
    {
      // The number is prime until it is proven unprime
      prime = true;
      
      /* A number is prime as long as it is not divisible by any primes less 
       * than maxfactor 
       */
      maxfactor = (int)sqrt((double)number);  
      for (factor = primes[0], factorindex = 0; 
           factor <= maxfactor && prime && factor; 
	   factor = primes[++factorindex])
      {
        /* if there is no remainder (modules if faster than division) then the
	 * number is prime and the loop will terminate.
	 */
        if (number % factor == 0) 
          prime = false; 
      }

      if (prime)
      {
	/* If the [prime]number is less than maxprime, it must be stored in the
	 * prime array because it will be later used test whether another
	 * number is prime.
	 */
        if (number <= maxprime) 
          primes[factorsfound++] = number; 

        output(fout, number); //print the prime number to the file
        ++primesfound;  //Increment the number of primes
      }
    }
    
    // Store the finish time
    clock_t finish_time = clock();

    // Append summary to file
    duration = (double)(finish_time - start_time)/CLOCKS_PER_SEC;
    write_summary_to_file(fout, (double)(finish_time - start_time), 
		          primesfound);

    // Close the file stream
    fclose(fout);

    // Display on screen summary
    printf("%s (%i - %i million) Completed!\n",
           filename,
           (min-1) / 1000000,
           max     / 1000000);
    
    double duration = (double)(finish_time - start_time)/CLOCKS_PER_SEC;
    printf(" ->time %.2f seconds\n", duration);
    printf(" ->number of primes: %i\n\n", primesfound);

    //Calculate new min and max for next million
    min = filenumber * 1000000 + 1000000 + 1;
    max = min + 1000000 - 1;

    //Add primes in current million to total
    totalprimesfound += primesfound;

    //Increment file name
    ++filenumber;
  }
  clock_t program_finish_time = clock(); //eq time loop finished

  /* Get the tics (finish_time-start_time) then divide by CLOCKS_PER_SEC to 
   * get the time in seconds.
   */
  duration = (double)(program_finish_time - program_start_time)/CLOCKS_PER_SEC;

  //Create status file and store overall summary
  fout = fopen("stats.txt", "w");
  fprintf(fout, "Total time taken: %.2f seconds\n", duration);
  fprintf(fout, "Total number of primes: %i\n");
  fclose(fout);

  //Send overall summary to screen
  printf("Action complete.\n");
  printf("Total time taken: %.2f seconds\n", duration);
  printf("Total number of primes: %i\n", totalprimesfound);

  free(primes);
  //delete [] primes;

  return true;
} 
