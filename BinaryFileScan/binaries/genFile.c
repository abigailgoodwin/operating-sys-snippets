/*
 * This file generates a binary output file containing integers. It
 * requires the output filename as a parameter and will take an 
 * argument indicating the number of values to generate as input.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BIAS 0 // a bias value added to the numbers to "bias" the file 
               // contents to provide an offset to the min and max

 int main(int argc, char * argv[]) {
    const char * filename;   // name of the output file
    FILE * ft;               // file handle for output file
    int numtogen = 1000000;  // default is to generate 1,000,000 numbers
    int randomnum, i; // variables used in the loop generating numbers
   
    if (argc<2) {  // not enough arguments, need output file name
        printf("Usage: gendata <filename> [number of numbers]\n");
        return 1;
    }
    if (argc == 3)  // optional third argument for number of numbers 
        numtogen = atoi(argv[2]);
   
    filename=argv[1];  // use the filename entered to store numbers
    srand(time(NULL)); // seed the random number generator
    ft= fopen(filename, "wb") ;
    if (ft) {
        for (i = 0; i < numtogen; i++){
            randomnum = rand() % numtogen + BIAS;
            fwrite(&randomnum,sizeof(int),1,ft);
        }
        fclose(ft);
	}
	return 0;
}