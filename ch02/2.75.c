/*************************************************************************
	> File Name: 2.75.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Thu 30 Apr 2015 10:21:55 PM CST
 ************************************************************************/

#include<stdio.h>

unsigned unsigned_high_prod(unsigned x, unsigned y){
    int x_highest = 1 && (x & INT_MIN);
    int y_highest = 1 && (x & INT_MIN);
    return signed_high_prod(x, y) + y_highest*x + x_highest*y;
}
