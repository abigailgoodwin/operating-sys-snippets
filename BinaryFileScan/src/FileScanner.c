/**
 * @file FileScanner.c
 * @author Abigail Goodwin (abigailgoodwin@mail.weber.edu)
 * @brief A single FileScanner. Will scan the given binary file and return the min and max integer.
 * @version 0.1
 * @date 2022-02-15
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * @brief 
 * 
 * @param argc Number of parameters. Max 2 are used.
 * @param argv Contains passed parameters. argv[1] should be the binary file name.
 * @return int 0 on success, 1 on failure
 */
int main(int argc, char* argv[])
{
    /* Step 1: Checking Input */
    if (argc < 1)
    {
        printf("Usage: fileScanner <file>\n");
        return 1;
    }

    /* Step 2: Establish Identity */
    int pid = getpid();

    /* Step 3: Establish Vars */
    const char* inFile = argv[1];
    FILE * file = fopen(inFile, "rb");
    long fileSize; // Size in bytes of the file.
    int numInts; // Number of integers in the file.
    int currentNum; // Current integer being read.
    int min; // Minimum number.
    int max; // Maximum number.

    /* Step 4: Process File Size */
    if (file)
    {
        // Step 1: Get File Size
        fseek(file, 0, SEEK_END);
        fileSize = ftell(file);

        // Step 2: Return to File Beginning
        fseek(file, 0, SEEK_SET);

        // Step 3: Do Math to Get Num of Ints
        numInts = (int) (fileSize / (int) sizeof(int));

        // Step 4: Set Min and Max
        fread(&currentNum, sizeof(int), 1, file);
        min = currentNum;
        max = min;

        // Step 5: Begin Parsing the Rest
        for (int currPosition = 1; currPosition < numInts; currPosition++)
        {
            fread(&currentNum, sizeof(int), 1, file);
            if ( currentNum < min )
            {
                min = currentNum;
            }
            if ( currentNum > max )
            {
                max = currentNum;
            }
        }
    }
    else
    {
        printf("Error: file could not be opened.\n");
        return 1;
    }
    
    // Using Printf For Now
    printf("\nPID %d has finished parsing \"%s\".\n", pid, inFile);
    printf("Min: %d\nMax: %d\n", min, max);
    fclose(file);
    return 0;
}