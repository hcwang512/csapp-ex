/*************************************************************************
	> File Name: 2.77.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Thu 30 Apr 2015 10:56:41 PM CST
 ************************************************************************/

#include<stdio.h>
#include<limits.h>

int divide_power2(int x, int k){
    int sign = 1 && (x & INT_MIN);
    int mask = (1<<k) - 1;
    mask &= (mask + !sign);
    return (x+mask)>>k;
}

int main(){
    printf("%X\t%d\t%d\n", divide_power2(9, 2), divide_power2(-9, 2), -9>>2);
    return 0;
}
