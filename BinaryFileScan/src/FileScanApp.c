/**
 * @file FileScanApp.c
 * @author Abigail Goodwin (abigailgoodwin@mail.weber.edu)
 * @brief The driver for the File Scanner App. Will fork and execute FileScanner.c.
 * @version 0.1
 * @date 2022-02-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief Takes in user input and forks "n" number of times to scan the given file.
 * 
 * @param argc Argument count.
 * @param argv User-passed args. argv[0] is the executable name. argv[1] is the number of forks. argv[2] is the file to scan.
 * @return int 0 on success, 1 on failure
 * @TODO: Implement time.
 */
int main(int argc, char* argv[])
{
    /* Step 0: Start Timer */
    clock_t runtime;
    runtime = clock();

    /* Step 1: Validate User Input */
    if (argc < 3 || atoi(argv[1]) > 4 || atoi(argv[1]) < 1)
    {
        printf("Usage: hw3 <numForks> <file>\n");
        return 1;
    }

    // Going to assume, at this point, that the user input is fine...
    const char* inFile = argv[2];
    int numForks = atoi(argv[1]);

    /* Step 2: Print Name */
    printf("Author: Abigail Goodwin\n");

    /* Step 3: Prepare for Forking */
    int p[2];

    if(pipe(p) < 0)
    {
        printf("Error: pipe could not be created.\n");
        return 1;
    }

    int pid = -1;

    /* Step 4: Start Forking */
    if (numForks == 1)
    {
        execl("./fileScanner", "fileScanner", inFile, (char *)0);
    }
    else
    {
        for (int currentForks = 1; currentForks <= numForks; currentForks++)
        {
            printf("(%d/%d) forks created.\n", currentForks, numForks);
            pid = fork();
            if (pid == 0)
            {
                break;
            }
        }
    }
    
    /* Step 5: Fork Code */
    if (pid == 0)
    {
        close(p[0]);   //close pipe read end
        close(1); // close stdout
        dup2(p[1], 1); //move stdout to pipe of cp[1]
	    close(0);       //close stdin 
        execl("./fileScanner", "fileScanner", inFile, (char *)0);
    }
    else
    {
        wait(NULL);
        char pipeReturn;
        close(p[1]);
        while (read(p[0], &pipeReturn, 1) == 1)
        {
            printf("%c", pipeReturn);
        }
        
        /* Last Step: Report Time */
        runtime = clock() - runtime;
        printf("\nTotal Runtime: %f seconds.\n", (((double)runtime)/CLOCKS_PER_SEC));
    }

    return 0;
}