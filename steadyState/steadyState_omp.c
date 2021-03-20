//
//  Steady state diffusion code 
//  
//
//  Created by Danny Dreelan on 10/03/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


int main(int argc, const char * argv[]) {
  // insert code here...
    
  int i,j;
  int nrows = atoi(argv[2]);
  int ncols = atoi(argv[1]);
    
  int midRow = (int) nrows/2;
  int midCol = (int) ncols/2;
    
  double tol = 1e-4;

  // Using an unrolled array, so that entire loop can be parallelised
  double *w = (double *) malloc(nrows*ncols *sizeof(double*));
  double *wNew = (double *) malloc(nrows*ncols *sizeof(double*));
  

#pragma omp parallel
{
  // All in one loop, not sure which is better
#pragma omp for schedule(static) private(j)
  for (i=0; i<nrows; ++i) {
    for (j=0; j<ncols; ++j) {
      // BOTTOM
      if (
	  (i==0) // Bottom row
	  &&  (j!=0) // Not at left edge
	  &&  (j!=(ncols-1)) // Not at right edge
	  )
	{
	  w[i*nrows+j]=0.0;
	}            
      // Left and Right cols
      else if (
	       (j == 0)
	       ||  (j == (ncols-1))
	       ) {
	w[i*nrows+j] = 100.0;
      }
      // Top row
      else if (i== (nrows-1)){
	w[i*nrows+j] =100.0;
      }              
      else{ // Internal field
	w[i*nrows+j]=75.0;
      }
    }
  }
}    
  // Print field
  printf("Initial State of Field:\n\n");
  for (i=(nrows-1); i>=0; --i) { // Rows printed in reverse so that output is correct
    for (j=0; j<ncols; ++j) {
      printf("%.2f\t",w[i*nrows+j]);
    }
    printf("\n");
  }
  printf("\n\n");

  // FINITE DIFFERENCE LOOP
  // Update field
  double res = 0.0;
  int iter = 0;
  int iterMax = 1e9;
  do {
    res = 0.0;
    for (i=1; i<(nrows-1); ++i) {
      for (j=1; j<(ncols-1); ++j) {
	wNew[i*nrows+j] = ( w[(i+1)*nrows+j] + w[(i-1)*nrows+j] + w[i*nrows+(j+1)] + w[i*nrows+(j-1)] )/4.0;
	double delta = fabs(wNew[i*nrows+j] - w[i*nrows+j]);
	//                printf("delta: %f\n",delta );
	if (delta > res) {
	  res = delta;
	}
      }
    }
    for (i=1; i<(nrows-1); ++i) {
      for (j=1; j<(ncols-1); ++j) {
	w[i*nrows+j] = wNew[i*nrows+j];
      }
    }
    iter++;
    printf("iter %i\tresidual: %g\tw[midRow][midCol]: %f\n",iter,res,w[midRow*nrows+midCol]);
  } while ( (res >= tol) && (iter < iterMax));
    
    printf("Final state of Field, res = %f:\n\n",res);
    for (i=(nrows-1); i>=0; --i) {
        for (j=0; j<ncols; ++j) {
            printf("%.2f\t",w[i*nrows+j]);
        }
        printf("\n");
    }
  printf("Program complete\n");
    
  return 0;
}
