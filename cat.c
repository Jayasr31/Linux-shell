#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char const *argv[])
{
    char *temp; char st[20];
    strcpy(st, argv[0]);
    temp = strtok(st, "/");
    if(strcmp(temp, argv[0]) != 0){
        for(int i=0; i<argc; i++) argv[i-1] = argv[i];
        argc--;
    }

    FILE *ptr;
    if(argc == 1) printf("Invalid command\n");

    else if(argc > 3) printf("Invalid command");

    else if(strcmp(argv[1], ">") == 0){
        if(argc <= 2) printf("Invalid command\n");
        else{
            ptr = fopen(argv[2], "r");
            if(ptr != NULL) printf("File already exists\n");
            else{
                ptr = fopen(argv[2], "w");
            }
        } 
    }

    else if(strcmp(argv[1], "-n") == 0){
        if(argc <= 2) printf("Invalid command\n");
        else{
            ptr = fopen(argv[2], "r");
            if(ptr == NULL) printf("File does not exist\n");
            else{
                char line[100];
                int l=0;
                while(fgets(line, 100, ptr) != NULL){
                    l++;
                    printf("%d) %s", l, line);
                }
                printf("\n");
            }
            fclose(ptr);
        } 
    }

    else{
        ptr = fopen(argv[1], "r");
        if(ptr == NULL) printf("File does not exist\n");
        else{
            char line[100];
            while(fgets(line, 100, ptr) != NULL){
                printf("%s", line);
            }
            printf("\n");
        }
        fclose(ptr);
    }

    return 0;
}
