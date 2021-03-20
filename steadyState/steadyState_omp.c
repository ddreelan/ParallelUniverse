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
  double startTime =  omp_get_wtime();
  printf("startTime: %g\n",startTime);

  int i,j,nThreads;
  int nrows = atoi(argv[2]);
  int ncols = atoi(argv[1]);
    
  int midRow = (int) nrows/2;
  int midCol = (int) ncols/2;
    
  double tol = 1e-4;
  double res = 1e6; // something big (starting value of residual)
  int iter = 0;
  int iterMax = 1e9;

  // Using an unrolled array, so that entire loop can be parallelised
  double *w = (double *) malloc(nrows*ncols *sizeof(double*));
  double *wNew = (double *) malloc(nrows*ncols *sizeof(double*));
  

#pragma omp parallel
  {
#pragma omp single
    nThreads = omp_get_num_threads();
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

    /*    // #pragma omp barrier
#pragma omp single
    {   
      // Print field
      printf("Initial State of Field:\n\n");
      for (i=(nrows-1); i>=0; --i) { // Rows printed in reverse so that output is correct
	for (j=0; j<ncols; ++j) {
	  printf("%.2f\t",w[i*nrows+j]);
	}
	printf("\n");
      }
      printf("\n\n");
      } // omp single */
    //  } // END OF OMP


    printf("Start of finite difference loop. From thread %i\tTotal: %i\n",omp_get_thread_num(),omp_get_num_threads());
  // FINITE DIFFERENCE LOOP
  // Update field
    //#pragma omp parallel
      // {
  while ( (res >= tol) && (iter < iterMax)){

#pragma omp barrier
#pragma omp single
      {
    res = 0.0;
    ++iter;	
      }

    // Solve for wNew, using w from the previous timestep
    //    printf("Number of threads: %i\n", omp_get_num_threads());
    //#pragma omp parallel
    //{
#pragma omp for private(j) reduction(max:res)
    for (i=1; i<(nrows-1); ++i) {
      for (j=1; j<(ncols-1); ++j) {
        //  wNew[i][j] = ( w[i+1][j] + w[i-1][j] + w[i][j+1] + w[i][j-1] )/4.0; OLD METHOD
        //                
	wNew[i*nrows+j] = ( w[(i+1)*nrows+j] + w[(i-1)*nrows+j] + w[i*nrows+(j+1)] + w[i*nrows+(j-1)] )/4.0;
	double delta = fabs(wNew[i*nrows+j] - w[i*nrows+j]);
	//	printf("Hello from thread num\t%i\n",omp_get_thread_num());
	res = fmax(res,delta);

      } // j loop
    } // i loop ALL

    // CONVERGENCE CHECK

    //    printf("tid: %i\tres: %g\n",omp_get_thread_num(),res );	
    //#pragma omp single
    //	{

#pragma omp for private(j)
    for (i=1; i<(nrows-1); ++i) {
      for (j=1; j<(ncols-1); ++j) {
	w[i*nrows+j] = wNew[i*nrows+j];
      }
    }
 } // End omp parallel
    //printf("iter %i\tresidual: %g\tmid val: %f\n",iter,res,w[midRow*nrows+midCol]);
} // WHILE

    // } // single

  double runTime = omp_get_wtime() - startTime;
  /*    
  printf("Final state of Field, res = %g\ttol = %g\n\n",res,tol);
  for (i=(nrows-1); i>=0; --i) {
    for (j=0; j<ncols; ++j) {
      printf("%.2f\t",w[i*nrows+j]);
    }
    printf("\n");
  }
  */
  printf("Program complete. Time taken: %g\tnThreads: %i\n",runTime,nThreads);
    
  return 0;
}
