#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include <pthread.h>
#include<signal.h>

int main(){
    char main_path[100];
    getcwd(main_path, 100);
    while(1){
        char input[100];char filepath[100];
        strcpy(filepath, main_path);
        printf("customShell$");
        if (fgets(input, 100, stdin) != NULL) {
            int len = strlen(input);
            if (len > 0 && input[len-1] == '\n') {
                input[--len] = '\0';
            }
        }
        
        if(input[0] == '\0') continue;

        char *command[15];
        int flg = 0;
        char *token = strtok(input, " ");
        int position = 0;
        while(token != NULL){
            command[position] = token;
            token = strtok(NULL, " ");
            position++;
        }
        command[position] = NULL;

        if(strcmp(command[0], "&t") == 0){
            flg = 1;
            for(int i=1; i<position; i++){
                command[i-1] = command[i];
            }
            position--;
        }

        if(strcmp(command[0], "echo") == 0){
            if(position == 1) continue;

            if(strcmp(command[1], "-n") == 0){
                for(int i=2; i<position-1; i++){
                    printf("%s ", command[i]);
                }
                printf("%s", command[position-1]);    
            }
            else if(strcmp(command[1], "--help") == 0){
                printf("-n: do not output the trailing newline\n-e: enable interpretation of backslash spaces\n--help: display this help and exit\n");
            }
            else{
                for(int i=1; i<position-1; i++){
                    printf("%s ", command[i]);
                }
                printf("%s\n", command[position-1]);
            }
        }
        
        else if(strcmp(command[0], "pwd") == 0){
            if(position == 1){
                char directory[256];
                if(getcwd(directory, 256) == NULL) printf("Error in printing working directory\n");
                else printf("%s\n", directory);
            }
            else if(position == 2){
                if(strcmp(command[1], "-L") == 0 || strcmp(command[1], "-P") == 0){
                    char directory[256];
                    if(getcwd(directory, 256) == NULL) printf("Error in printing working directory\n");
                    else printf("%s\n", directory);
                }
                else printf("Invalid command\n");
            }
            else printf("Invalid command\n");
            
        }

        else if(strcmp(command[0], "exit") == 0) break;

        else if(strcmp(command[0], "cd") == 0){
            if(position == 2){
                int status = 0;
                if(strcmp(command[1], "..") == 0) status = chdir("..");
                else if(strcmp(command[1], "~") == 0) status = chdir(getenv("HOME"));
                else {
                    char path[100];
                    getcwd(path, 100);
                    strcat(path, "/");
                    strcat(path, command[1]);
                    status = chdir(path);
                }
                if(status == -1) printf("Invalid path\n");
            }
            else printf("Invalid command\n");
        }

        else if(strcmp(command[0], "ls") == 0 || strcmp(command[0], "date") == 0 || strcmp(command[0], "cat") == 0 || 
                    strcmp(command[0], "rm") == 0 || strcmp(command[0], "mkdir") == 0){

            if(flg == 1){
                strcat(filepath, "/");
                strcat(filepath, command[0]);
                for(int i=0; i<position; i++){
                    strcat(filepath, " ");
                    strcat(filepath, command[i]);
                }
                pthread_t p;
                pthread_create(&p, NULL, (void*)(*system), (void*)filepath);
                pthread_join(p, NULL);
            }

            else{
                pid_t pid = fork();
                if(pid == 0){
                    strcat(filepath, "/");
                    strcat(filepath, command[0]);
                    execv(filepath, command);
                }
                else if(pid < 0) printf("fork error\n");
                else{   
                    if(command[position] == NULL){
                        waitpid(pid, NULL, 0);
                    }
                }
            } 
        }
    }
    return 0;
}
