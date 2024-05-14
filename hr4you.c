#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog2_ex1.h"

/*#define DAYS_IN_WEEK 7
#define MAX_LEN 256
#define MAX_WORKERS 100
#define HOURS_PER_SHIFT 8*/
char *print_role(int role);

typedef struct worker_t {
    char name[100];
    int id;
    double hour_wage;
    worker_role role;
    int current_number_of_shifts;
    int max_number_of_shifts;
    shift_day shift_week[DAYS_IN_WEEK];
    shift_type shift_time[DAYS_IN_WEEK];
} worker;


void swap(worker *arr,int i,int j){
    worker temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void swap_type(shift_type *arr,int i,int j){
    shift_type temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void swap_day(shift_day *arr,int i,int j){
    shift_day temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void copy(worker *arr,worker *copy_arr,int size){/*return original worker array*/ 
    int i;
    for (i = 0; i < size; i++)
    {
        copy_arr[i] = arr[i];
    }
    
}
void copy_day(shift_day *arr,shift_day *copy_arr,int size){/*return original worker array*/ 
    int i;
    for (i = 0; i < size; i++)
    {
        copy_arr[i] = arr[i];
    }
    
}
void copy_type(shift_type *arr,shift_type *copy_arr,int size){/*return original worker array*/ 
    int i;
    for (i = 0; i < size; i++)
    {
        copy_arr[i] = arr[i];
    }
    
}

void sort_array(worker *arr,int size){
    int i , j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if(arr[i].id < arr[j].id)
                swap(arr,i,j);
        }
    }
    
}
void sort_array_special(shift_type *type_arr,shift_day *day_arr,int size){
    int i , j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if(day_arr[i] < day_arr[j]){
                swap_day(day_arr,i,j);
                swap_type(type_arr,i,j);
            }
                
        }
    }
    
}
/*REMOVE WORKER (wo_arr,*wo_num,id);*/
void Remove_worker(worker *wo_arr, int *wo_num, int id) {
    int i, j;
    int found = 0;
    if (id < 0) {
        prog2_report_error_message(INVALID_WORKER_ID);
    }
    for (i = 0; i < *wo_num; i++) {
        if (wo_arr[i].id == id) {
            found = 1;
            for (j = i; j < *wo_num - 1; j++) {
                wo_arr[j] = wo_arr[j + 1];
            }
            (*wo_num)--;
            break; /* Exit loop once worker is removed*/
        }
    }

    if (!found) {
        prog2_report_error_message(WORKER_DOESNT_EXIST);
    }
}

/*ADD WORKER (wo_arr,*wo_num,str3,id,hw,role,shift);*/
void Add_worker(worker *wo_arr,int *wo_num,char *name,int id,float hw,int role,int shift) {
    int i;
    
    /* Check if the number of workers exceeds the maximum limit*/
    if (*wo_num > MAX_WORKERS) {
        prog2_report_error_message(WORKERS_OVERFLOW);
        return;
    }

    /* Check if the ID is valid*/
    if (id < 0) {
        prog2_report_error_message(INVALID_WORKER_ID);
        return;
    }
    
    /* Check if the hourly wage is valid need to add not more then  ".00 "*/
    if (hw < 0 ) { 
        prog2_report_error_message(INVALID_WAGE);
        return;
    }

    if (role < 0 || role > 5) {
        prog2_report_error_message(INVALID_ROLE);
        return;
    }

    /* Check if the number of shifts is valid*/
    if (shift < 0 || shift > 7) {
        prog2_report_error_message(INVALID_NUM_OF_SHIFTS);
        return;
    }

    /*Check if the worker already exists*/
    for (i = 0; i < *wo_num; i++) {
      if (wo_arr[i].id == id) {
        prog2_report_error_message(WORKER_ALREADY_EXISTS);
        return;
        }
    }

    strcpy(wo_arr[*wo_num].name, name);
    wo_arr[*wo_num].id=id;
    wo_arr[*wo_num].hour_wage=hw;
    wo_arr[*wo_num].role=role;
    wo_arr[*wo_num].max_number_of_shifts=shift;
    wo_arr[*wo_num].current_number_of_shifts = 0 ;

    *wo_num = *wo_num+1 ;
}

/*Add Shift <worker id> <day> <shift>*/
void Add_Shift(worker *wo_arr, int wo_num, int id, int day, int shift) {
    int i;
    for (i = 0; i < wo_num; i++) {
        if (wo_arr[i].id == id) {
            if (wo_arr[i].current_number_of_shifts < wo_arr[i].max_number_of_shifts) {
                wo_arr[i].shift_week[wo_arr[i].current_number_of_shifts] = day;
                wo_arr[i].shift_time[wo_arr[i].current_number_of_shifts] = shift; 
                wo_arr[i].current_number_of_shifts = wo_arr[i].current_number_of_shifts + 1;
            } else {
                prog2_report_error_message(SHIFTS_OVERFLOW); /* Report error if worker exceeds maximum shifts*/
            }
            return; /* Exit function after adding shift*/
        }
    }
    prog2_report_error_message(WORKER_DOESNT_EXIST); /* Report error if worker ID is not found*/
}

void control_panel(char *line,worker *wo_arr,int *wo_num,FILE *out){
   const char s[3] = " \n";
   char *token;
  
    char str1[256],   str2[256],   str3[256],   str4[256],  str5[256],  str6[256],  str7[256];
    int i = 0,j = 0;
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
        /*printf("%s\n", token); //tester */
    
      token = strtok(NULL, s);
      i++;
   }

    if(strcmp(str1,"Add") == 0 && strcmp(str2,"Worker") == 0){                                                  /*[x]*/
        
        int id = atoi(str4);
        float hw = atof(str5);
        int shift = atoi(str7);
        int role;
        /*int role = sort_role(str6);*/
        if(strcmp(str6,"Bartender")==0){
            role = 0;
        }
        else if(strcmp(str6,"Waiter")==0){
            role = 1;
        }
        else if(strcmp(str6,"Manager")==0){
            role = 2;
        }
        else if(strcmp(str6,"Cashier")==0){
            role = 3;
        }
        else if(strcmp(str6,"Chef")==0){
        role = 4;
        }
        else if(strcmp(str6,"Dishwasher")==0){
        role = 5;
        }
        else{
            prog2_report_error_message(INVALID_ROLE);
        }
        
        Add_worker(wo_arr,wo_num,str3,id,hw,role,shift);
    }
    else if(strcmp(str1,"Add") == 0 && strcmp(str2,"Shift") == 0){                                              /*[x]*/
        int id = atoi(str3);
        int day = atoi(str4);
        int shift_t;
        /*MORNING = 0x1,
        AFTERNOON = 0x2,
        EVENING = 0x4,
        NIGHT = 0x8*/
        if(strcmp(str5,"Morning")==0){
            shift_t = 0x1;
        }
        else if(strcmp(str5,"Afternoon")==0){
            shift_t = 0x2;
        }
        else if(strcmp(str5,"Evening")==0){
            shift_t = 0x4;
        }
        else if(strcmp(str5,"Night")==0){
            shift_t = 0x8;
        }
        else{
            prog2_report_error_message(INVALID_SHIFT_TYPE);
        }

        Add_Shift(wo_arr,*wo_num,id,day,shift_t);
    }
    else if(strcmp(str1,"Remove") == 0 && strcmp(str2,"Worker") == 0){                                          /*[x]*/

        int id = atoi(str3);
        Remove_worker(wo_arr,wo_num,id);

    }
    else if(strcmp(str1,"Report") == 0 && strcmp(str2,"Workers") == 0){                                         /*[x]*/
        int i;
        worker copy_arr[MAX_WORKERS];
        copy(wo_arr,copy_arr,*wo_num); 
        sort_array(copy_arr,*wo_num);
        
        if(strcmp(str3,"Bartender") == 0){
            for(i = 0 ; i < *wo_num; i++){
            if(copy_arr[i].role == 0){
                worker_role role = copy_arr[i].role;
                long int id = copy_arr[i].id;
                char *name = copy_arr[i].name;
                float hw = copy_arr[i].hour_wage;
                float total_payment = hw * copy_arr[i].current_number_of_shifts * HOURS_PER_SHIFT;
                prog2_report_worker(out, id, name, hw ,role, total_payment);
                }
            }
        }
        else if(strcmp(str3,"Waiter") == 0){
            for(i = 0 ; i < *wo_num; i++){
            if(copy_arr[i].role == 1){
                worker_role role = copy_arr[i].role;
                long int id = copy_arr[i].id;
                char *name = copy_arr[i].name;
                float hw = copy_arr[i].hour_wage;
                float total_payment = hw * copy_arr[i].current_number_of_shifts * HOURS_PER_SHIFT;
                prog2_report_worker(out, id, name, hw ,role,total_payment);
                }
            }
        }
        else if(strcmp(str3,"Manager") == 0){
            for(i = 0 ; i < *wo_num; i++){
            if(copy_arr[i].role == 2){
                worker_role role = copy_arr[i].role;
                long int id = copy_arr[i].id;
                char *name = copy_arr[i].name;
                float hw = copy_arr[i].hour_wage;
                float total_payment = hw * copy_arr[i].current_number_of_shifts * HOURS_PER_SHIFT;
                prog2_report_worker(out, id, name, hw ,role,total_payment);
                }
            }
        }
        else if(strcmp(str3,"Cashier") == 0){
            for(i = 0 ; i < *wo_num; i++){
            if(copy_arr[i].role == 3){
                worker_role role = copy_arr[i].role;
                long int id = copy_arr[i].id;
                char *name = copy_arr[i].name;
                float hw = copy_arr[i].hour_wage;
                float total_payment = hw * copy_arr[i].current_number_of_shifts * HOURS_PER_SHIFT;
                prog2_report_worker(out, id, name, hw ,role,total_payment);
                }
            }
        }
        else if(strcmp(str3,"Chef") == 0){
            for(i = 0 ; i < *wo_num; i++){
            if(copy_arr[i].role == 4){
                worker_role role = copy_arr[i].role;
                long int id = copy_arr[i].id;
                char *name = copy_arr[i].name;
                float hw = copy_arr[i].hour_wage;
                float total_payment = hw * copy_arr[i].current_number_of_shifts * HOURS_PER_SHIFT;
                prog2_report_worker(out, id, name, hw ,role,total_payment);
                }
            }
        }  
        else if(strcmp(str3,"Dishwasher") == 0){
            for(i = 0 ; i < *wo_num; i++){
            if(copy_arr[i].role == 5){
                worker_role role = copy_arr[i].role;
                long int id = copy_arr[i].id;
                char *name = copy_arr[i].name;
                float hw = copy_arr[i].hour_wage;
                float total_payment = hw * copy_arr[i].current_number_of_shifts * HOURS_PER_SHIFT;
                prog2_report_worker(out, id, name, hw ,role,total_payment);
                }
            }
        }
        else{ 
            for(i = 0 ; i < *wo_num; i++){
            long int id = copy_arr[i].id;
            char *name = copy_arr[i].name;
            float hw = copy_arr[i].hour_wage;
            worker_role role = copy_arr[i].role;

            float total_payment = hw * copy_arr[i].current_number_of_shifts * HOURS_PER_SHIFT;
            prog2_report_worker(out, id, name, hw ,role,total_payment);
            }
        }

    }
    else if(strcmp(str1,"Report") == 0 && strcmp(str2,"Shifts") == 0){                                          /*[x]*/
        long int id = atoi(str3);
        shift_day copy_arr_day[DAYS_IN_WEEK];
        shift_type copy_arr_type[DAYS_IN_WEEK];

        for(i = 0 ; i < *wo_num; i++){
            if(wo_arr[i].id == id){
                char *name = wo_arr[i].name;
                float hw = wo_arr[i].hour_wage;
                worker_role role = wo_arr[i].role;
                float total_payment = hw * wo_arr[i].current_number_of_shifts * HOURS_PER_SHIFT;
                prog2_report_worker(out, id, name, hw ,role,total_payment);



                copy_day(wo_arr[i].shift_week,copy_arr_day,DAYS_IN_WEEK);
                copy_type(wo_arr[i].shift_time,copy_arr_type,DAYS_IN_WEEK);
                sort_array_special(copy_arr_type,copy_arr_day,wo_arr[i].current_number_of_shifts);

                for(j = 0 ; j < wo_arr[i].current_number_of_shifts ; j++){
                int day = copy_arr_day[j];
                int shift = copy_arr_type[j];
                prog2_report_shift(out,day,shift);
                }
            }
        }

    }else if(strcmp(str1,"Report") == 0 && strcmp(str2,"Shift") == 0 && strcmp(str3,"Details") == 0) {          /*[x]*/
        int num_of_workers = 0;
        int day = atoi(str4);
        shift_type time;
        float total_payment = 0;
        float hw;

        if(strcmp(str5,"Morning") == 0){
            time = MORNING;
        }
        else if(strcmp(str5,"Afternoon") == 0){
            time = AFTERNOON;
        }
        else if(strcmp(str5,"Evening") == 0){
            time = EVENING;
        }
        else if(strcmp(str5,"Night") == 0){
            time = NIGHT;
        }
        else{
            
        }

        for(i =0 ; i < *wo_num ; i++){
            for(j =0 ; j < wo_arr[i].current_number_of_shifts ; j++){
                if((wo_arr[i].shift_time[j] == time) && (wo_arr[i].shift_week[j] == day)){
                    num_of_workers++;
                    
                    hw = wo_arr[i].hour_wage;
                    total_payment += hw * HOURS_PER_SHIFT;
                }
            }
        }
        if(num_of_workers != 0)
        {
            prog2_report_shift_details(out,day,time,num_of_workers, total_payment);
        }
    }
}

int main(int argc, char *argv[]){

    worker wo_arr[MAX_WORKERS];
    char line[MAX_LEN];
    int wo_num = 0;

    FILE *input_file = stdin;  /* Default to standard input */
    FILE *out = stdout; /* Default to standard output*/
   if(argc == 3 || argc == 5){
    if (argc == 3) {
        if (strcmp(argv[1], "-i") == 0) { 
            input_file = fopen(argv[2], "r"); /* ./hr4you -i test1.in*/
            if (!input_file) {
                prog2_report_error_message(CANNOT_OPEN_FILE);
            }
        } else {
            prog2_report_error_message(INVALID_ARGUMENTS);
        }
    }
    else if (argc == 5) {
        if (strcmp(argv[1], "-i") == 0) { 
            input_file = fopen(argv[2], "r"); /* ./hr4you -i test1.in*/
                if (!input_file) {
                    prog2_report_error_message(CANNOT_OPEN_FILE);
                }
            }if (strcmp(argv[3], "-o") == 0){ /* ./hr4you -i test1.in -o test1.out */
                out = fopen(argv[4], "w");
                if (!out || !input_file) {
                    prog2_report_error_message(CANNOT_OPEN_FILE);
                }
            } else {
                prog2_report_error_message(INVALID_ARGUMENTS);
            }
        }
    } else if (argc != 1) {

        prog2_report_error_message(INVALID_ARGUMENTS);
    }

    /* Read input data*/
    while (fgets(line, sizeof(line), input_file) != NULL) {
        if (line[0] == '#'||line[0] == '\n'||line[0] == '\r') {
            continue;
        }
    control_panel(line,wo_arr,&wo_num,out);


    /*fprintf(out,"%s", line); //test*/
    }
    /* Close files if necessary*/
        if (input_file != stdin) {
            fclose(input_file);
        }
        if (out != stdout) {
            fclose(out);
        }
    return 0;
}

/*terminal
    gcc -o hr4you -ansi -Wall -pedantic-errors *.c prog2_ex1.o

     for testing
    ./hr4you -i test1.in -o new_test1.out
*/