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
    worker_role role; //[6] enum
    int number_of_shifts;
} worker;

/*terminal
     end command
    ./new_hr4 < test1 >! test1

     for testing
    ./new_hr4 -i test1
*/

void error(const char *msg){
    printf("%s\n",msg);
    exit(1);
}

/* //maybe we dont need this
void replaceSpaces(char *str) {
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i]; // Copy non-space characters
        }
    }
    str[j] = '\0'; // Add null terminator at the end of the modified string
}
*/
//Add Worker <name> <id> <hourly wage> <role> <number of shifts>
void Add_worker(worker *wo_arr,int wo_num,char *name,int id,double hw,worker_role role,int shift){
    strcpy(wo_arr[wo_num].name, name);
    wo_arr[wo_num].id = id;
}

void control_pannel(char *line){
   const char s[2] = " ";
   char *token;
  
    char str1[128],   str2[128],   str3[128],   str4[128],  str5[128],  str6[128],  str7[128];
    int i = 0;
   /* get the first token */
   token = strtok(line, s);
   
   /* walk through other tokens */
   while(token != NULL ) {
    if(i == 0)
        strcpy(str1,token);
    if(i == 1)
        strcpy(str2,token);
    if(i == 2)
        strcpy(str3,token);
    if(i == 3)
        strcpy(str4,token);
    if(i == 4)
        strcpy(str5,token);
    if(i == 5)
        strcpy(str6,token);
    if(i == 6)
        strcpy(str7,token);
        //printf("%s\n", token); //tester
    
      token = strtok(NULL, s);
      i++;
   }
   
    if(strcmp(str1,"Add") == 0 && strcmp(str2,"Worker") == 0){
        //printf("*to function add_worker*\n");
        printf("NAME : %s ",str3);
        printf("ID : %s ",str4);
        printf("Hour Wage : %s ",str5);
        printf("Role : %s ",str6);
        printf("Shift : %s \n",str7);

    }
    if(strcmp(str1,"Add") == 0 && strcmp(str2,"Shift") == 0){
        //printf("*to function add_shift*\n");
        printf("ID : %s ",str3);
        printf("Day : %s ",str4);
        printf("Shift : %s \n",str5);

    }
    if(strcmp(str1,"Remove") == 0 && strcmp(str2,"Worker") == 0){
        //printf("*to function Remove_shift*\n");
        printf("ID : %s\n",str3);

    }
    if(strcmp(str1,"Report") == 0 && strcmp(str2,"Worker") == 0){
        //printf("*to function Report_Worker*\n");
        printf("Role : %s\n",str3);


    }
    if(strcmp(str1,"Report") == 0 && strcmp(str2,"Shift") == 0){
        //printf("*to function Report_shift*\n");
        printf("ID : %s\n",str3);


    }
    if(strcmp(str1,"Report") == 0 && strcmp(str2,"Shift") == 0 && strcmp(str3,"Details") == 0) {
        //printf("*to function Report_Shift_Details*\n");
        printf("%s ",str3);
        printf("%s ",str4);
        printf("%s \n",str5);

    }
}

int main(int argc, char *argv[]){

    worker wo_arr[MAX_WORKERS];
    char line[MAX_LEN];
    char err_msg[32];

    FILE *input_file = stdin;  // Default to standard input
    FILE *output_file = stdout; // Default to standard output
   if(argc == 3 || argc == 5){
    if (argc == 3) {
        if (strcmp(argv[1], "-i") == 0) { 
            input_file = fopen(argv[2], "r"); // ./new_hr4 -i test1.in
            //
            if (!input_file) {
                error("Error opening input file");
            }
        } else {
            //scanf user
            error("Invalid arguments");
        }
    }
    else if (argc == 5) {
        if (strcmp(argv[1], "-i") == 0) { 
            input_file = fopen(argv[2], "r"); // ./new_hr4 -i test1.in
            //
                if (!input_file) {
                    error("Error opening input file");
                }
            }if (strcmp(argv[3], "-o") == 0){ // ./new_hr4 -i test1.in -o test1.out
                output_file = fopen(argv[4], "w");
                //
                if (!output_file || !input_file) {
                    error("Error opening output file");
                }
            } else {
                //scanf user
                error("Invalid arguments");
            }
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
    //functions ==============================================================================
    //replaceSpaces(line); //maybe we dont need it
    control_pannel(line);
    //Add_worker(line);
    // Remove_Worker();
    // Add_Shift();
    // Report_Workers();
    // Report_Shifts();
    // Report_Shift_Details();
    
    //for now its just a tester.
    //fprintf(output_file,"%s", line); //what will come in the output.

 
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