#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>

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
    struct dirent *rd;
    dir = opendir(".");
    if(argc == 1){
        if(dir == NULL){
            printf("Can't open directory\n");
        }
        else{
            while((rd = readdir(dir)) != NULL){
                if(rd->d_name[0] == '.') continue;
                else printf("%s  ", rd->d_name);
            }
            printf("\n");
        }
        closedir(dir);
    }
    else if(argc == 2){
        if(strcmp(argv[1], "-a") == 0){
            if(dir == NULL){
                printf("Can't open directory\n");
            }
            else{
                while((rd = readdir(dir)) != NULL){
                    printf("%s  ", rd->d_name);
                }
                printf("\n");
            }
            closedir(dir);
        }
        else if(strcmp(argv[1], "-1") == 0){
            if(dir == NULL){
                printf("Can't open directory\n");
            }
            else{
                while((rd = readdir(dir)) != NULL){
                    if(rd->d_name[0] == '.') continue;
                    else printf("%s\n", rd->d_name);
                }
            }
            closedir(dir);
        }
        else printf("Invalid command\n");
        
    }
    else printf("Invalid Command\n");

    return 0;
}
