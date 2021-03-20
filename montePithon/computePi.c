#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "string.h"

#include "ran2.c"

int main(int argc, char **argv){

  double startTime = omp_get_wtime();
  // Read number of points from arguments
  int i,j,N,seedOffset,nThreads;

   if (argc!=3) {
     printf("Wrong number of arguments specified, 1: Npoints, 2: seedOffset\n"); 
     return -1;
   }

    N=atoi(argv[1]);
    seedOffset=atoi(argv[2]);

  
  // Get runtime info for scheduling
  omp_sched_t kind;
  int chunk_size;

  omp_get_schedule(&kind,&chunk_size);

  // Declare empty arrays for x, y points and the seeds that generated them
  double *x = (double *) malloc(N*sizeof(double));
  double *y = (double *) malloc(N*sizeof(double));

  //   long *seedX = (long *) malloc(N*sizeof(long));
  //   long *seedY = (long *) malloc(N*sizeof(long));


   // Open file for writing of the random points and seed information
   FILE *ptsFile;
   ptsFile = fopen("pts.csv","w");
   if(ptsFile == NULL){
     printf("pts.csv could not be opened");
     return 2;
   }
   // Write header
   //   fprintf(ptsFile,"c,X,Y,seedX,seedY,ThreadID,LoopPosition\n");

   
  double loopStartTime = omp_get_wtime();
  int insideCount = 0;

#pragma omp parallel
{

#pragma omp master
  {
  nThreads = omp_get_num_threads();
  //  printf("nThreads: %d\n",nThreads);
  //  return 0;
  }

#pragma for shared(x,y,N) private(i,seedX,seedY,c) reduction(+:insideCount) schedule(runtime)
  for(i=0;i<N;++i){
    double iterStartTime = omp_get_wtime();
    // Initialize seed lists
    long seedX, seedY;
    //    seedX = i+1;
    //    seedY = i+1 + N;


    // Generate points using these seeds.
    // Execute on one thread at time.

    seedX = i+1;
    seedY = i+1 + N;
#pragma omp critical
{
    x[i]=ran2(&seedX);
    y[i]=ran2(&seedY);
}
    // Calculate distance from the origin, and count
    //    int insideTrue = -1;
    double c = sqrt( x[i]*x[i] + y[i]*y[i] );
    if( c <= 1.0 ){
      insideCount++;
    }
    //#pragma omp critical
    fprintf(ptsFile,"%f,%f\n",x[i],y[i]);
    //fprintf(ptsFile,"%f,%f,%f,%i,%i\n",c,x[i],y[i],seedX[i],seedY[i],omp_get_thread_num(),i);
    //    printf("i: %i,\tthread: %i, seed: %i,%i, pt: (%f,%f), c: %f\n",i,omp_get_thread_num(),seedX,seedY,x[i],y[i],c);

    }
}

// printf("End of parallel Region\n");

  double pi = 4.0*(double)insideCount/(double)N;
  double piError = (pi - M_PI)/M_PI;
  double totalTime = omp_get_wtime() - startTime;
  double loopTotalTime = omp_get_wtime() - loopStartTime;
  
  // Append results to file
  FILE *resultsFile;
  resultsFile = fopen("resultsFile.csv","a");
  if(resultsFile == NULL){
    printf("resultsFile.csv could not be opened");
    return 2;
  }
  //  fprintf(resultsFile,"%d,%i,%i,%i,%g,%g,%i,%g,%g\n",kind,chunk_size,nThreads,N,pi,piError,insideCount,totalTime,loopTotalTime);
  printf("%d,%i,%i,%i,%g,%g,%i,%g,%g\n",kind,chunk_size,nThreads,N,pi,piError,insideCount,totalTime,loopTotalTime);

  // Write header to file
  //  fprintf(piFile,"nSample,seedX,seedY,ranX,ranY,distance,insideTrue,nInside,Pi,Error,loopTime,totalTime\n");

  //printf("%i,%i,%d,%i,%g,%g,%g,%g\n",N,insideCount,kind,chunk_size,totalTime,loopTotalTime,pi,piError);

  //  printf("End of program\n");  
      return 0;

}
