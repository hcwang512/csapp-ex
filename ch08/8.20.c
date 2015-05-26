/*************************************************************************
	> File Name: 8.20.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Tue 12 May 2015 08:39:41 AM CST
 ************************************************************************/

#include<stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>

extern char *environ[];

int main(int argc, char *argv[]){
    pid_t pid;
    pid = fork();
    if (pid < 0){
        perror("fork");
        exit(1);
    }
    else if (pid == 0){
        execve("/bin/ls", argv, environ);
        perror("execve error");
        exit(2);
    }
    else{
        int status, ret;
        ret = waitpid(pid, &status, 0);
        if (ret < 0){
            perror("waitpid");
            exit(3);
        }
    }
    return 0;
}
