#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct worker_t
{
    char name[128];
    int id;
    double hour_wage;
    //worker_role role; //[6] enum

} worker;

int main(int argc, char *argv[]) {
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
    char buffer[255];

    if (pF == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    else {
        while (fgets(buffer, sizeof(buffer), pF) != NULL) {
            printf("%s", buffer);
        }
    }

    fclose(pF);

    return 0;
}