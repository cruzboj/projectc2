#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prog2_ex1.h"
//prog2
//#define MAX_WORKERS 100
//#define DAYS_IN_WEEK 7
//#define MAX_LEN 256
//#define MAX_WORKERS 100
//#define HOURS_PER_SHIFT 8

typedef struct worker_t {
    char name[100];
    long int id;
    double hour_wage;
    char role[100]; //change later to enum with prog2
    int number_of_shifts;
} worker;

/*terminal
     end command
    ./new_hr4 < test1 >! test1

     for testing
    ./new_hr4 -i< test1
*/

void error(const char *msg){
    printf("%s\n",msg);
    exit(1);
}

void replaceSpaces(char *str) {
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[0] != ' ') {
            str[j++] = str[i]; // Copy non-space characters
        }
    }
    str[j] = '\0'; // Add null terminator at the end of the modified string
}


int main(int argc, char *argv[]){

    worker wo_arr[MAX_WORKERS];
    char line[MAX_LEN];
    char err_msg[32];

    FILE *input_file = stdin;  // Default to standard input
    FILE *output_file = stdout; // Default to standard output

     if (argc == 3) {
        if (strcmp(argv[1], "-i") == 0) {
            input_file = fopen(argv[2], "r");
            //
            if (!input_file) {
                error("Error opening input file");
            }
        } else if (strcmp(argv[1], "-o") == 0) {
            output_file = fopen(argv[2], "w");

            if (!output_file) {
                error("Error opening output file");
            }
        } else {
            //scanf user
            error("Invalid arguments");
        }
    } else if (argc != 1) {
        //scanf user
        error("Invalid number of arguments");
    }

    // while (scanf("%s",line) != EOF)
    // {
    //     printf("%s",line);
    // }

    // Read input data
    while (fgets(line, sizeof(line), input_file) != NULL) {
        if (line[0] == '#') {
            continue;
        }
    replaceSpaces(line);

    fprintf(output_file,"%s", line);

 
//
        
//       
    }

    // Close files if necessary
    if (input_file != stdin) {
        fclose(input_file);
    }
    if (output_file != stdout) {
        fclose(output_file);
    }

printf("\n");
return 0;
}