#ifndef _H_PRIMEHEADER
#define _H_PRIMEHEADER

//#include <iostream> 
//#include <fstream> 
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <time.h>

inline void output(FILE* fout, long num)
{
  fprintf(fout, "%i\n", num);
  //fout << num << endl;
}

inline void write_summary_to_file(FILE* f, double duration, long count)
{
  // Append summary to filename
  fprintf(f, "--------------------------Summary---------------------------\n");
  fprintf(f, "duration: %.2f seconds\n", duration);
  fprintf(f, "number of primes: %i\n", count);
  
  //fout << "--------------------------Summary---------------------------" <<endl;
  //fout << "duration: " << duration << " seconds"<<endl;
  //fout << "number of primes: " << count <<"\n\n\n";
}

#define bool unsigned char 
#define true  1
#define false 0

#endif
