#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
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
    
    DIR *dir;
    if(argc == 1) printf("Invalid command\n");
    else if(strcmp(argv[1], "-v") == 0){
        if(argc <= 2) printf("Invalid command\n");
        else{
            for(int i=2; i<argc; i++){
                dir = opendir(argv[i]);
                if(dir != NULL) printf("Directory '%s' already exists\n", argv[i]);
                else{
                    int newdir;
                    newdir = mkdir(argv[i],
                            S_IRUSR | S_IRGRP | S_IROTH | S_IXUSR | S_IXGRP | S_IXOTH);
                    printf("Created new directory: '%s'\n", argv[i]);
                }
            }   
        }
        
    }

    else if(strcmp(argv[1], "-p") == 0){
        if(argc <= 2) printf("Invalid command\n");
        else{
            for(int i=2; i<argc; i++){
                dir = opendir(argv[i]);
                if(dir != NULL) continue;
                else{
                    int newdir;
                    newdir = mkdir(argv[i],
                            S_IRUSR | S_IRGRP | S_IROTH | S_IXUSR | S_IXGRP | S_IXOTH);
                }
            }   
        }
        
    }

    else{
        for(int i=1; i<argc; i++){
            dir = opendir(argv[i]);
            if(dir != NULL) printf("Directory '%s' already exists\n", argv[i]);
            else{
                int newdir;
                newdir = mkdir(argv[i], 
                            S_IRUSR | S_IRGRP | S_IROTH | S_IXUSR | S_IXGRP | S_IXOTH);
            }
        }
    }

    return 0;
}
