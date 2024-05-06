#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//shalom github
typedef struct employee_t
{
    char name[128];
    int id;
    char role[128];
    int salary;
    } *employee;
    int employees_promotions(employee arr[], size_t size, /*OUT*/ employee expensive)
    {
        int mc = 0;
        int ms= 0;
        int i = 0;
        if (size == 0)
        return -1;
    
    /* Promoting employees with high salary :) */
    for (i = 0; i < size; i++)
        {
            employee c = arr[i];
            if (c->salary > 20000 && strcmp(c->role, "Developer") == 0)
            strcpy(c->role, "Manager");
            else if (c->salary > 20000 && strcmp(c->role, "Tester") == 0)
            strcpy(c->role, "Manager");
            else if (c->salary > 20000 && strcmp(c->role, "Analyst") == 0)
            strcpy(c->role, "Manager");
        }
    /* Counting managers */
    for (i = 0; i < size; i++)
        {
            employee current = arr[i];
            if (strcmp(current->role, "Manager") == 0)
            mc++;
        }
    /* Searching the most expensive worker */
    for (i = 0; i < size; i++)
        {
            employee c = arr[i];
            if (c->salary > ms)
            ms = c->salary;
            *expensive = *c;
            
        }
    return mc;
    }
// Yona-Tan ><>

/* 
4.1 סעיף א
הבעיה בקוד של יונתן זה שמתקבלת תוצאה איך לא התוצאה הרצוייה לפי בקשת הסעיף
פלט התוצאה אינו מחזיר את העובד ששילמו לו הכי הרבה אלה את העובד האחרון ברשימה

על מנת לתקן זאת יש לבצע 
שינוי ב: 
Searching the most expensive worker 
יש להכניס את השורות אל בלוק 

if (c->salary > ms){
            ms = c->salary;
            *expensive = *c;
    }

סעיף ג 4.3
    פתרון 1
    if((c->salary > 20000) && (strcmp(c->role,Analyst) || Tester || Developer))
        strcpy(c->role, "Manager");
        
    פתרון 2
    int role;
    חוסך לנו ביטים
    ואם אנחנו רוצים את המחרוזות נשמור את השמות במערך קבוע
   
    פתרון 3
    for (i = 0; i < size; i++)
        {
            employee c = arr[i];
            if (strcmp(c->role, "Manager") == 0)
            mc++;
            
            if (c->salary > ms)
            ms = c->salary;
            *expensive = *c;
            
        }
        
        ניתן לצמצם את פעולם הלולאה
        
*/

/*
סעיף ב 4.2
*/
int main(){
    struct employee_t employees[1] = {
        {"John", 1, "Developer", 25000},
    };

    employee employee_ptrs[1];

    for (int i = 0; i < 1; ++i)
    {
        employee_ptrs[i] = &employees[i];
    }

    struct employee_t most_expensive;
    employee expensive = &most_expensive;
    
    int managers_count = employees_promotions(employee_ptrs, 1, expensive);

    printf("Managers count: %d\n", managers_count);
    printf("Most expensive worker: \n");
    printf("Name: %s\n", expensive->name);
    printf("ID: %d\n", expensive->id);
    printf("Role: %s\n", expensive->role);
    printf("Salary: %d\n", expensive->salary);

    return 0;
}