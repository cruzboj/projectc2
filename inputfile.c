#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prog2_ex1.h"

typedef struct worker_t
{
    char name[128];
    int id;
    double hour_wage;
    //worker_role role; //[6] enum

} worker;

void error(hr_result *error){
    //for now we need :
    //SUCCESS           error[0]
    //INVALID_ARGUMENTS error[1]
    //CANNOT_OPEN_FILE  error[2]
    //fprintf(stderr, "ERROR: %s\n",msg);
    exit(1);

}

//14:30 fopen

int main(int argc, char *argv[]) {  // terminal = ./inputfile.exe -i test.txt //need to find the commend for test1.in cuz we get error
    /*DATA ====================================================================================================================*/
    worker arr[MAX_WORKERS];


    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    if (strcmp(filename, "-i") == 0) {
        // If the first argument is an option like "-i", use the next argument as the filename
        if (argc < 3) {
            printf("Option -i requires a filename argument.\n");
            return 1;
        }
        filename = argv[2];
    }

    FILE *pF = fopen(filename, "r");
    //FILE *pF = fopen(argv[1], "r"); search about it will not work with -i in the terminal
    char buffer[255];

    if (pF == NULL) {
        //error()
        printf("Error opening file.\n");
        return 1;
    }
    else {
        while (fgets(buffer, sizeof(buffer), pF) != NULL) {
            printf("%s", buffer);
        }
    }

    fclose(pF);
    

    printf("\n");
    return 0;
}