#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <prog2_ex1.h>

//Add Worker <name> <id> <hourly wage> <role> <number of shifts>
typedef struct Worker{
    char name[128];
    int id;
    double hour_wage;
    worker_role role; //[6] enum
}Worker;

void add_worker(Worker **worker_arr,int size,char *name_w ,int id_w ,double hour_wage_w ,worker_role role_w){

    strcpy(worker_arr[size]->name, name_w);
    worker_arr[size]->id = id_w;
    worker_arr[size]->hour_wage = hour_wage_w;
    worker_arr[size]->role = role_w;
}

void main(){
    Worker arr[MAX_WORKERS];
    int size = 0;

    add_worker(arr,size,);
    size++;

return 0;
}
/*
/$ code .
*/