#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prog2_ex1.h"
//prog2
#define MAX_WORKERS 100
//#define DAYS_IN_WEEK 7
//#define MAX_LEN 256
//#define MAX_WORKERS 100
//#define HOURS_PER_SHIFT 8

typedef struct worker_t {
    char name[100];
    int id;
    double hour_wage;
    worker_role role; //[6] enum
    int number_of_shifts;
} worker;

void prog2_report_error_message(hr_result result){
    //we need to change the printf() to fprintf() but not now.
    switch(result) {
        case SUCCESS:
            printf("SUCCESS\n");
            break;
        case INVALID_ARGUMENTS:
            printf("INVALID_ARGUMENTS\n");
            break;
        case CANNOT_OPEN_FILE:
            printf("CANNOT_OPEN_FILE\n");
            break;
        case WORKERS_OVERFLOW:
            printf("WORKERS_OVERFLOW\n");
            break;
        case INVALID_WORKER_ID:
            printf("INVALID_WORKER_ID\n");
            break;
        case INVALID_WAGE:
            printf("INVALID_WAGE\n");
            break;
        case INVALID_ROLE:
            printf("INVALID_ROLE\n");
            break;
        case INVALID_NUM_OF_SHIFTS:
            printf("INVALID_NUM_OF_SHIFTS\n");
            break;
        case WORKER_ALREADY_EXISTS:
            printf("WORKER_ALREADY_EXISTS\n");
            break;
        case INVALID_SHIFT_DAY:
            printf("INVALID_SHIFT_DAY\n");
            break;
        case INVALID_SHIFT_TYPE:
            printf("INVALID_SHIFT_TYPE\n");
            break;
        case WORKER_DOESNT_EXIST:
            printf("WORKER_DOESNT_EXIST\n");
            break;
        case SHIFTS_OVERFLOW:
            printf("SHIFTS_OVERFLOW\n");
            break;
        case SHIFT_ALREADY_EXISTS:
            printf("SHIFT_ALREADY_EXISTS\n");
            break;
        case NO_WORKERS:
            printf("NO_WORKERS\n");
            break;
        case NO_SHIFTS:
            printf("NO_SHIFTS\n");
            break;
        default:
            printf("Unknown choice\n");
            break;
    }
    //exit(1);
}

/*terminal
     end command
    ./new_hr4 < test1 >! test1

     for testing
    ./new_hr4 -i test1
*/

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

int sort_role(char *role){
    if(strcmp(role,"Bartender")==0){
      return  0;
    }
    else if(strcmp(role,"Waiter")==0){
      return  1;
    }
    else if(strcmp(role,"Manager")==0){
      return  2;
    }
    else if(strcmp(role,"Cashier")==0){
       return 3;
    }
    else if(strcmp(role,"Chef")==0){
       return 4;
    }
    else if(strcmp(role,"Dishwasher")==0){
       return 5;
    }
    else
        prog2_report_error_message(INVALID_ROLE);
}

char *print_role(int role){
    switch(role){
        case 0:
            return "BARTENDER";
            break;
        
        case 1:
            return "WAITER";
            break;

        case 2:
            return "MANAGER";
            break;

        case 3:
            return "CASHIER";
            break;

        case 4:
            return "CHEF";
            break;

        case 5:
            return "DISHWASHER";
            break;

        default:
            prog2_report_error_message(INVALID_ROLE);
    }
}
//char* addWorker(char* name, long int id, double hour_wage, worker_role role, int numShifts)
void Add_worker(worker *wo_arr,int wo_num,char *name,int id,float hw,int role,int shift) {
    
    // Check if the number of workers exceeds the maximum limit
    if (wo_num > MAX_WORKERS) {
        prog2_report_error_message(WORKERS_OVERFLOW);
    }

    // Check if the ID is valid
    if (id <0 || id>1000000000 || id/100000000 == 0) {
        prog2_report_error_message(INVALID_WORKER_ID);
    }
    
    // Check if the hourly wage is valid
    if (hw < 0 || hw > 99.99 ) {
        prog2_report_error_message(INVALID_WAGE);
    }

    if (role < 0 || role > 5) {
        prog2_report_error_message(INVALID_ROLE);
    }

    // // Check if the number of shifts is valid
    if (shift < 0 || shift > 7) {
        prog2_report_error_message(INVALID_NUM_OF_SHIFTS);
    }

    //Check if the worker already exists
    for (int i = 0; i < wo_num; i++) {
      if (wo_arr[i].id == id) {
        prog2_report_error_message(WORKER_ALREADY_EXISTS);
        }
    }

    strcpy(wo_arr[wo_num].name, name);
    wo_arr[wo_num].id=id;
    wo_arr[wo_num].hour_wage=hw;
    wo_arr[wo_num].role=role;
    wo_arr[wo_num].number_of_shifts=shift;
//printf("%s\n",wo_arr[0].name);
    

}

void control_pannel(char *line,worker *wo_arr,int wo_num){
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
        // printf("NAME : %s ",str3);
        // printf("ID : %s ",str4);
        // printf("Hour Wage : %s ",str5);
        // printf("Role : %s ",str6);
        // printf("Shift : %s \n",str7);
        
        int id = atoi(str4);
        float hw = atof(str5);
        int shift = atoi(str7);
        int role = sort_role(str6);
        

        Add_worker(wo_arr,wo_num,str3,id,hw,role,shift);
    }
    if(strcmp(str1,"Add") == 0 && strcmp(str2,"Shift") == 0){
        //printf("*to function add_shift*\n");
        // printf("ID : %s ",str3);
        // printf("Day : %s ",str4);
        // printf("Shift : %s \n",str5);

    }
    if(strcmp(str1,"Remove") == 0 && strcmp(str2,"Worker") == 0){
        //printf("*to function Remove_shift*\n");
        //printf("ID : %s\n",str3);

    }
    if(strcmp(str1,"Report") == 0 && strcmp(str2,"Worker") == 0){
        //printf("*to function Report_Worker*\n");
        //printf("Role : %s\n",str3);


    }
    if(strcmp(str1,"Report") == 0 && strcmp(str2,"Shift") == 0){
        //printf("*to function Report_shift*\n");
        //printf("ID : %s\n",str3);


    }
    if(strcmp(str1,"Report") == 0 && strcmp(str2,"Shift") == 0 && strcmp(str3,"Details") == 0) {
        //printf("*to function Report_Shift_Details*\n");
        // printf("%s ",str3);
        // printf("%s ",str4);
        // printf("%s \n",str5);

    }
}


int main(int argc, char *argv[]){

    worker wo_arr[MAX_WORKERS];
    char line[MAX_LEN];
    char err_msg[32];
    int wo_num=0;

    FILE *input_file = stdin;  // Default to standard input
    FILE *output_file = stdout; // Default to standard output
   if(argc == 3 || argc == 5){
    if (argc == 3) {
        if (strcmp(argv[1], "-i") == 0) { 
            input_file = fopen(argv[2], "r"); // ./new_hr4 -i test1.in
            //
            if (!input_file) {
                prog2_report_error_message(CANNOT_OPEN_FILE);
            }
        } else {
            //scanf user
            prog2_report_error_message(INVALID_ARGUMENTS);
        }
    }
    else if (argc == 5) {
        if (strcmp(argv[1], "-i") == 0) { 
            input_file = fopen(argv[2], "r"); // ./new_hr4 -i test1.in
            //
                if (!input_file) {
                    prog2_report_error_message(CANNOT_OPEN_FILE);
                }
            }if (strcmp(argv[3], "-o") == 0){ // ./new_hr4 -i test1.in -o test1.out
                output_file = fopen(argv[4], "w");
                //
                if (!output_file || !input_file) {
                    prog2_report_error_message(CANNOT_OPEN_FILE);
                }
            } else {
                //scanf user
                prog2_report_error_message(INVALID_ARGUMENTS);
            }
        }
    } else if (argc != 1) {
        //scanf user
        prog2_report_error_message(INVALID_ARGUMENTS);
    }

    // while (scanf("%s",line) != EOF)
    // {
    //     printf("%s",line);
    // }

    // Read input data
    while (fgets(line, sizeof(line), input_file) != NULL) {
        if (line[0] == '#'||line[0] == '\n'||line[0] == '\r') {
            continue;
        }
    //functions ==============================================================================
    //replaceSpaces(line); //maybe we dont need it
    control_pannel(line,wo_arr,wo_num);
    wo_num++;
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
printf("name :%s\n",wo_arr[0].name);
printf("id :%d\n",wo_arr[0].id);
printf("hour wage :%f\n",wo_arr[0].hour_wage);
printf("role :%s\n",print_role(wo_arr[0].role));
printf("number of shifts :%d\n",wo_arr[0].number_of_shifts);
//printf("%d",wo_num);

printf("\n");
return 0;
}