#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>

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
    DIR *dir;
    if(argc == 1) printf("Invalid command\n");

    else if(strcmp(argv[1], "-i") == 0){
        if(argc <= 2) printf("Invalid command\n");
        else{
            for(int i=2; i<argc; i++){
                dir = opendir(argv[i]);
                if(dir != NULL) printf("Cannot delete a directory: '%s'\n", argv[i]);
                else{
                    ptr = fopen(argv[i], "r");
                    if(ptr == NULL) printf("File '%s' does not exist\n", argv[i]);
                    else{
                        fclose(ptr);
                        printf("remove file %s?", argv[i]);
                        char inp;
                        scanf("%c", &inp);
                        if(inp == 'y'){
                            int status = remove(argv[i]);
                            if(status != 0) printf("Cannot delete file\n");
                        } 
                    }
                }
            }
        } 
    }

    else if(strcmp(argv[1], "-d") == 0){
        if(argc <= 2) printf("Invalid command\n");
        else{
            for(int i=2; i<argc; i++){
                ptr = fopen(argv[i], "r");
                if(ptr == NULL) printf("File '%s' does not exist\n", argv[i]);
                else{
                    fclose(ptr);
                    int status = remove(argv[i]);
                    if(status != 0) printf("Cannot delete file\n");
                }
            }
        } 
    }
        
    else{
        for(int i=1; i<argc; i++){
            dir = opendir(argv[i]);
            if(dir != NULL) printf("Cannot delete a directory: '%s'\n", argv[i]);
            else{
                 ptr = fopen(argv[i], "r");
                if(ptr == NULL) printf("File '%s' does not exist\n", argv[i]);
                else{
                    fclose(ptr);
                    int status = remove(argv[i]);
                    if(status != 0) printf("Cannot delete file\n");
                }
            }
        }
    } 
    
    return 0;
}
