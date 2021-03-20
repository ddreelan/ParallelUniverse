#!/bin/sh

# This script runs computePi.c for various configs

# Read output file name as argv
outputFileName=$1
# Remove old results file if it exists
# rm -f resultFile.csv

# Add header to resultsFile.csv
# kind,chunk_size,nThreads,N,pi,piError,insAideCount,totalTime,loopTotalTime
echo "ScheduleType,ChunkSize,nThreads,N,pi,piError,insideCount,totalTime,loopTotalTime" > $outputFileName


# ------- AMDAHL's LAW (Fixed Problem Size)
# -------- ChunkSize = 1
export OMP_NUM_THREADS=1
# Run 1 - schedule=static,1 nThreads=1, N=1000000
export OMP_SCHEDULE=static,1
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=dynamic,1 nThreads=1, N=1000000
export OMP_SCHEDULE=dynamic,1
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=guided,1 nThreads=1, N=1000000
export OMP_SCHEDULE=guided,1
./computePi.X 1000000 0 >> $outputFileName

export OMP_NUM_THREADS=2
# Run 1 - schedule=static,1 nThreads=2, N=1000000
export OMP_SCHEDULE=static,1
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=dynamic,1 nThreads=2, N=1000000
export OMP_SCHEDULE=dynamic,1
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=guided,1 nThreads=2, N=1000000
export OMP_SCHEDULE=guided,1
./computePi.X 1000000 0 >> $outputFileName

export OMP_NUM_THREADS=4
# Run 1 - schedule=static,1 nThreads=4, N=1000000
export OMP_SCHEDULE=static,1
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=dynamic,1 nThreads=4, N=1000000
export OMP_SCHEDULE=dynamic,1
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=guided,1 nThreads=4, N=1000000
export OMP_SCHEDULE=guided,1
./computePi.X 1000000 0 >> $outputFileName

export OMP_NUM_THREADS=8
# Run 1 - schedule=static,1 nThreads=8, N=1000000
export OMP_SCHEDULE=static,1
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=dynamic,1 nThreads=8, N=1000000
export OMP_SCHEDULE=dynamic,1
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=guided,1 nThreads=8, N=1000000
export OMP_SCHEDULE=dynamic,1
./computePi.X 1000000 0 >> $outputFileName


# -------- ChunkSize = 5
export OMP_NUM_THREADS=1
# Run 1 - schedule=static,1 nThreads=1, N=1000000
export OMP_SCHEDULE=static,5
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=dynamic,1 nThreads=1, N=1000000
export OMP_SCHEDULE=dynamic,5
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=guided,1 nThreads=1, N=1000000
export OMP_SCHEDULE=guided,5
./computePi.X 1000000 0 >> $outputFileName

export OMP_NUM_THREADS=2
# Run 1 - schedule=static,1 nThreads=2, N=1000000
export OMP_SCHEDULE=static,5
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=dynamic,1 nThreads=2, N=1000000
export OMP_SCHEDULE=dynamic,5
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=guided,1 nThreads=2, N=1000000
export OMP_SCHEDULE=guided,5
./computePi.X 1000000 0 >> $outputFileName

export OMP_NUM_THREADS=4
# Run 1 - schedule=static,1 nThreads=4, N=1000000
export OMP_SCHEDULE=static,5
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=dynamic,1 nThreads=4, N=1000000
export OMP_SCHEDULE=dynamic,5
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=guided,1 nThreads=4, N=1000000
export OMP_SCHEDULE=guided,5
./computePi.X 1000000 0 >> $outputFileName

export OMP_NUM_THREADS=8
# Run 1 - schedule=static,1 nThreads=8, N=1000000
export OMP_SCHEDULE=static,5
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=dynamic,1 nThreads=8, N=1000000
export OMP_SCHEDULE=dynamic,5
./computePi.X 1000000 0 >> $outputFileName
# Run 1 - schedule=guided,1 nThreads=8, N=1000000
export OMP_SCHEDULE=dynamic,5
./computePi.X 1000000 0 >> $outputFileName









# -------- ChunkSize = 5
# Run 1 - schedule=static,5 nThreads=1, N=1000000
# Run 1 - schedule=dynamic,5 nThreads=1, N=1000000
# Run 1 - schedule=guided,5 nThreads=1, N=1000000

# Run 1 - schedule=static,5 nThreads=2, N=1000000
# Run 1 - schedule=dynamic,5 nThreads=2, N=1000000
# Run 1 - schedule=guided,5 nThreads=2, N=1000000

# Run 1 - schedule=static,5 nThreads=4, N=1000000
# Run 1 - schedule=dynamic,5 nThreads=4, N=1000000
# Run 1 - schedule=guided,5 nThreads=4, N=1000000

# Run 1 - schedule=static,5 nThreads=8, N=1000000
# Run 1 - schedule=dynamic,5 nThreads=8, N=1000000
# Run 1 - schedule=guided,5 nThreads=8, N=1000000
