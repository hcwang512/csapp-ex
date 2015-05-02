/*************************************************************************
	> File Name: 3.56.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Sat 02 May 2015 05:05:15 PM CST
 ************************************************************************/

#include<stdio.h>

int loop(int x, int n){
    int result = 0x555555555;
    int mask;
    for(mask=0x800000000; mask != 0; mask >> n){
        result ^= mask & x;
    }
    return result;
}
