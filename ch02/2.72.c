/*************************************************************************
	> File Name: 2.72.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Thu 30 Apr 2015 09:03:32 PM CST
 ************************************************************************/

#include<stdio.h>


void copy_int(int val, void *buf, int maxbytes){
    if (maxbytes > 0 && maxbytes > sizeof(int)){
        memcpy(buf, (void *) &val, sizeof(val));
    }
}
