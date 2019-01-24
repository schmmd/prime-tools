/* File: isprime.c */

/* Copyright (c) 2005 Michael Schmitz
 *
 * LICENSE
 */

/* Program Summary:
 * The program determines whether the input number x is prime by
 * dividing x by all numbers less than sqrt(x) and making sure the
 * remainder is non-zero.
 *
 * An input of 0 will terminate the program.
 */

#include "../primes.h"

// Functions
long isprime(unsigned long number_to_test);

// Public varibles
bool prime;

int main()
{
  unsigned long inputnumber;
  double duration = 0.0;
  
  printf("Welcome to isprime.exe - By Michael Schmitz\n\n");

  while(true)
  {
    prime = true;

    printf("Please enter a number you wish to determine as prime. ");
    printf("Enter 0 or less to exit.\n");
    printf("(Number must be less than 4,000,000,000)\n");
    scanf("%i", &inputnumber);

    if (inputnumber <= 0)
      break;

    clock_t start = clock(); 
    long factor = isprime(inputnumber);
    clock_t finish = clock(); 
    
    /* Get the tics (finish-start) then divide by CLOCKS_PER_SEC to get the time
     * in seconds.
     */
    duration = (double)(finish - start)/CLOCKS_PER_SEC; 

    if (prime)
      printf("Is prime in %.2f seconds\n\n\n\n\n", duration);
    else
      printf("Is not prime in %.2f seconds (divisible by %i)\n\n\n\n\n");
  }

  return 0;
}

long isprime(unsigned long i)
{
  unsigned long maxfactor = (long)sqrt((double) i);
  
  /* start dividing it by 2 - a half of itself */
  unsigned long n;
  for (n = 2; n <= maxfactor && prime; n++) 
  {
    // If there is no remainder (modules is faster than division)
    if (i % n == 0) 
      // Number is not prime, loop will terminate because prime = false
      prime = false; 
  }

  if (i < 2)
    prime = false;

  if (prime == false)
    return 0;
  else
    return n - 1; // The for statement puts n up one to far
}
