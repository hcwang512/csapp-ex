/*************************************************************************
	> File Name: 3.57.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Sat 02 May 2015 05:31:16 PM CST
 ************************************************************************/

#include<stdio.h>

int created_alt(int *xp){
    int t = 0;
    return *(xp ? xp : &t);
}
