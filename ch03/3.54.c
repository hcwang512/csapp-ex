/*************************************************************************
	> File Name: 3.54.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Sat 02 May 2015 03:20:23 PM CST
 ************************************************************************/

#include<stdio.h>

int decode2(int x, int y, int z){
    int sub = y + z;
    int val = sub << 15 >> 15;
    sub ^= x;
    return sub * val;
}
