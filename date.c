#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(int argc, char const *argv[])
{
    char *temp; char st[20];
    strcpy(st, argv[0]);
    temp = strtok(st, "/");
    if(strcmp(temp, argv[0]) != 0){
        for(int i=0; i<argc; i++) argv[i-1] = argv[i];
        argc--;
    }
    
    struct tm *local;
    time_t t = time(NULL);

    if(argc == 1){
        local = localtime(&t);
        printf("Local time and date: %s", asctime(local));
    }

    else if(argc == 2){
        if(strcmp(argv[1], "-u") == 0){
            local = gmtime(&t);
            printf("UTC time and date: %s", asctime(local));
        }
        else if(strcmp(argv[1], "-R") == 0){
            local = localtime(&t);
            char *d = asctime(local);
            char *arr1[10];
            char *token = strtok(d, " ");
            int position = 0 ;
            while(token != NULL){
                arr1[position] = token;
                token = strtok(NULL, " ");
                position++;
            }
            arr1[position] = NULL;
            arr1[4][4] = '\0';
            printf("%s, %s %s %s %s +0530\n", arr1[0], arr1[2], arr1[1], arr1[4], arr1[3]);
        }
        else printf("Invalid command\n");
    }
    else printf("Invalid command\n");
    
    return 0;
}
