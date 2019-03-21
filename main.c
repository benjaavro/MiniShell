//
//  main.c
//  MiniShell
//
//  Created by Benjamín Ávila Rosas on 3/18/19.
//  Copyright © 2019 Benjamín Avila. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXLINE 4096

char    buffer[MAXLINE];
char    com[10] = "";
char    arg1[20] = "";
char    arg2[20] = "";
char    arg3[20] = "";
char    arg4[20] = "";


int separate(char string[MAXLINE]) {
    int space_counter = 0;
    char aux_string[MAXLINE] = "";
    
    strcpy(aux_string, string);
    
    for (int i = 0; i <= strlen(string); i++) {
        if (string[i] == ' ') {
            space_counter++;
        }
    }
    
    if (space_counter == 0) {
        
        char* token = strtok(aux_string, " ");
        strcpy(com, token);
        //printf("COMMAND: %s\n",com);                  DEBUGGING TOOL
    } else
        
    if (space_counter == 1) {
        char* token = strtok(aux_string, " ");
        strcpy(com, token);
        //printf("COMMAND: %s\n",com);                  DEBUGGING TOOL
        
        token = strtok(NULL, " ");
        strcpy(arg1, token);
        //if (strcmp(arg1, "") != 0) printf("ARG 1: %s\n",arg1);    DEBUGGING TOOL
    } else
        
    if (space_counter == 2) {
        char* token = strtok(aux_string, " ");
        strcpy(com, token);
        //printf("COMMAND: %s\n",com);                  DEBUGGING TOOL
        
        token = strtok(NULL, " ");
        strcpy(arg1, token);
        //if (strcmp(arg1, "") != 0) printf("ARG 1: %s\n",arg1);    DEBUGGING TOOL
        
        token = strtok(NULL, " ");
        strcpy(arg2, token);
        //if (strcmp(arg2, "") != 0) printf("ARG 2: %s\n",arg2);    DEBUGGING TOOL
    } else
        
    if (space_counter == 3) {
        char* token = strtok(aux_string, " ");
        strcpy(com, token);
        printf("COMMAND: %s\n",com);
        
        token = strtok(NULL, " ");
        strcpy(arg1, token);
        //if (strcmp(arg1, "") != 0) printf("ARG 1: %s\n",arg1);    DEBUGGING TOOL
        
        token = strtok(NULL, " ");
        strcpy(arg2, token);
        //if (strcmp(arg2, "") != 0) printf("ARG 2: %s\n",arg2);    DEBUGGING TOOL
        
        token = strtok(NULL, " ");
        strcpy(arg3, token);
        //if (strcmp(arg3, "") != 0) printf("ARG 3: %s\n",arg3);    DEBUGGING TOOL
    } else
        
    if (space_counter == 4) {
        char* token = strtok(aux_string, " ");
        strcpy(com, token);
        //printf("COMMAND: %s\n",com);                              DEBUGGING TOOL
        
        token = strtok(NULL, " ");
        strcpy(arg1, token);
        //if (strcmp(arg1, "") != 0) printf("ARG 1: %s\n",arg1);    DEBUGGING TOOL
        
        token = strtok(NULL, " ");
        strcpy(arg2, token);
        //if (strcmp(arg2, "") != 0) printf("ARG 2: %s\n",arg2);    DEBUGGING TOOL
        
        token = strtok(NULL, " ");
        strcpy(arg3, token);
        //if (strcmp(arg3, "") != 0) printf("ARG 3: %s\n",arg3);    DEBUGGING TOOL
        
        token = strtok(NULL, " ");
        strcpy(arg4, token);
        //if (strcmp(arg4, "") != 0) printf("ARG 4: %s\n",arg4);    DEBUGGING TOOL
    }
    
    return space_counter;
}


int main(void) {
    pid_t   pid;
    int     status;
    int     type = 0;
    
    printf("-> ");
    while(fgets(buffer, MAXLINE, stdin) != NULL) {
        
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        
        if ((pid = fork()) < 0) {
            printf("Fork error... \n");
            exit(1);
        } else if (pid == 0) {      /* Child Process */
            //execlp("ls", "ls","-l", (char *)0);    // Used this line for testing arguments in a command
            
            // Separate arguments
            type = separate(buffer);
            if (type == 0) {
                execlp(com, com, (char *)0);
            }
            if (type == 1) {
                execlp(com, com, arg1, (char *)0);
            }
            if (type == 2) {
                execlp(com, com, arg1, arg2, (char *)0);
            }
            if (type == 3) {
                execlp(com, com, arg1, arg2, arg3, (char *)0);
            }
            if (type == 4) {
                execlp(com, com, arg1, arg2, arg3, arg4, (char *)0);
            }
            if (strcmp(buffer, "help") == 0) {
                printf("\n--- MANUAL ---\n\n");
                printf("Welcome to the MiniShell\n");
                printf("\nHere you can execute any UNIX command\n");
                printf("that has no more than 4 arguments at a time\n");
                printf("\n\nPress the combo   ctrl + C   for EXIT\n");
                printf("\nDeveloped by Benjamín Ávila Rosas, 2019\n");
            } else {
                printf("couldn't execute command with such arguments number\n");
                printf("ARGS NUM: %d\n",type);
            }
            
            //printf("couldn't execute: %s\n",buffer);
            exit(127);
        }
        
        /* Parent Process */
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            printf("waitpid error...\n");
            exit(2);
        }
        printf("\n-> ");
    }
    exit(0);
}
