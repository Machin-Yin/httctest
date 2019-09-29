#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>  
#include <time.h>
#include "MathFunctions.h"
#include "TutorialConfig.h"
//this function copy from InvSqrt

#if 0
double mysqrt(double number)  
{  
	
     float new_guess;
     float last_guess;
     
     if (number < 0) {
         printf("Cannot compute the square root of a negative number!\n");
         return -1;
     }
     
     new_guess = 1;
     do {
         last_guess = new_guess;
         new_guess = (last_guess + number / last_guess) / 2;
         printf("%.15e\n", new_guess);
     } while (new_guess != last_guess);
     
     return new_guess;
}  
#endif

double mysqrt(double number)  
{  
	// if we have both log and exp then use them
	#if defined (HAVE_LOG) && defined (HAVE_EXP)
	double result;
	result = exp(log(number)*0.5);
	printf("use log and exp to compute sqrt\n");
	return result;
	#else // otherwise use an iterative approach
	printf("Not use log and exp to compute sqrt\n");
	float new_guess;
	float last_guess;
     
    if (number < 0) {
         printf("Cannot compute the square root of a negative number!\n");
         return -1;
     }
     
     new_guess = 1;
     do {
         last_guess = new_guess;
         new_guess = (last_guess + number / last_guess) / 2;
         printf("new_guess: %.15e\n", new_guess);
     } while (new_guess != last_guess);
     
     return new_guess;
  #endif
}  

