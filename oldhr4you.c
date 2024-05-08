#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prog2_ex1.h"

//Add Worker <name> <id> <hourly wage> <role> <number of shifts>
typedef struct Worker{
    char name[128];
    int id;
    double hour_wage;
    worker_role role; //[6] enum
}Worker;

// void add_worker(Worker **worker_arr,int size,char *name_w ,int id_w ,double hour_wage_w ,worker_role role_w){
//     printf("f1");
//     strcpy(worker_arr[size]->name, name_w);
//     printf("f1");
//     worker_arr[size]->id = id_w;
//     worker_arr[size]->hour_wage = hour_wage_w;
//     worker_arr[size]->role = role_w;

// }
void add_worker(Worker *worker_arr,int size,char *name_w ,int id_w ,double hour_wage_w ,worker_role role_w){
    strcpy(worker_arr[size].name, name_w);
    worker_arr[size].id = id_w;
    worker_arr[size].hour_wage = hour_wage_w;
    worker_arr[size].role = role_w;

}

int main(){
    Worker arr[MAX_WORKERS];
    int size = 0;
    
    int i = 0;

    char name_w[128] ;
    int id_w ;
    double hour_wage_w ;
    worker_role role_w;

    char str1[128], str2[128], str3[128],str4[128], str5[128],str6[128],str7[128];

    FILE * fp;
    FILE * fpline;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("test.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char *token;
    const char s[2] = " ";

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read); // for test
        // printf("%s", line);

    /* get the first token */
    token = strtok(line, s);
    //char *temp = token;
    
    /* walk through other tokens */
    while( token != NULL ) {
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
                
            printf( "*%s\n", token);
            token = strtok(NULL, s);
            i++;
        }

    if(strcmp(str1,"Add") == 0 && strcmp(str2,"Worker") == 0){
        printf("success \n");   
        strcpy(name_w,str3);
        id_w = atoi(str4); //change str to int
        hour_wage_w = atof(str5); //change str to double
        if(strcmp(str6,"Chef") == 0)
             role_w = 4 ;
        add_worker(arr,size,name_w,id_w,hour_wage_w,role_w);
        size++;
        }
    /*elif add shift strcmp str1 str2
    add_shift(shift *work_arr,)
    */
        i = 0;
    }
    printf("%s\n",arr[0].name); //test to see worker in side the array
    printf("%s\n",arr[1].name);
    printf("%s\n",arr[2].name);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

    // add_worker(arr,size);
    // size++;

return 0;
}
/*
/$ code .
*/