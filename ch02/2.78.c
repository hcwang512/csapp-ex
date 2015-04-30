/*************************************************************************
	> File Name: 2.78.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Thu 30 Apr 2015 11:38:29 PM CST
 ************************************************************************/

#include<stdio.h>
#include<limits.h>

int mul5div8(int x){
    int sign = 1 && (x & INT_MIN);
    int bais = (0x7 + !sign) & 0x7;
    x = (x << 2) + x;
    return (x+bais)>>3;
}
