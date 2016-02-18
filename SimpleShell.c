/******************************************************************************
@file         SimgpleShell.c
@author       Darren Lowe, Jacqueline Catlin, Georgia Greegoriou, Cameron Turner, Ethan Dickson
@date         Thursday, 11/02/2016
@brief
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>


void parseLine(char* cmd, char** params);
int executeLine(char** params);
 
#define MAXIN 512
#define MAXPARA 50

int main()
{
    char line[MAXIN];
    char* strings[MAXPARA];
    
    
    while(1){
        
        printf(">");
        
        if (fgets(line, sizeof(line), stdin) == NULL) break;
        
        if (line[strlen(line)-1] == '\n') {
            line[strlen(line)-1] = '\0';
        }
        
        
        parseLine(line, strings);
    
        
        if (strcmp(strings[0], "exit") == 0) break;
        
        
        if (executeLine(strings) == 0) break;
        
    }
    
    return 0;
}
    

void parseLine(char* line, char** strings)
{
    
    for(int i = 0; i < MAXPARA; i++) {
        strings[i] = strsep(&line, " ");
        if(strings[i] == NULL) break;
    
}
}




    int executeLine(char** strings)
    {
        // Fork process
        pid_t pid = fork();
        
        // Error
        if (pid < 0) {
            char* error = strerror(errno);
            printf("fork: %s\n", error);
            return 1;
        }
        
        // Child process
        else if (pid == 0) {
            // Execute command
            execvp(strings[0], strings);
            
            // Error occurred
            char* error = strerror(errno);
            printf("shell: %s: %s\n", strings[0], error);
            return 0;
        }
        
        // Parent process
        else {
            // Wait for child process to finish
            int childStatus;
            waitpid(pid, &childStatus, 0);
            return 1;
        }
        
    }



/*

   Need to error trap for White space input (can trap other error input here as well)
   Need to add the exit command to break the loop
    Added 14/02/2016
*/
