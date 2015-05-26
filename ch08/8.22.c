/*************************************************************************
	> File Name: 8.22.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Tue 12 May 2015 09:39:23 AM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

extern char *environ[];


int mysystem(char *command){
    pid_t pid;
    pid = fork();

    if(pid < 0){
        perror("fork");
        return -1;
    }

    else if(pid == 0){

        if(!command){
            fprintf(stderr, "mysystem: command is null\n");
            exit(-1);
        }
        char *argv[4];
        argv[0] = "sh";
        argv[1] = "-c";
        argv[2] = command;
        argv[3] = NULL;
        execve("/bin/sh", argv, environ);
        // something went wrong
        perror("execve");
        return -1;
    }
    else{
        // parent
        int status, ret;
        ret = waitpid(pid, &status, 0);
        /* waitpid error */
        if(ret < 0){
            perror("waitpid");
            return -1;
        }
        /* the child process is terminated */
        if(WIFEXITED(status)){
            return WEXITSTATUS(status);
        }

        return 0;
    }
}

