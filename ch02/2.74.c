/*************************************************************************
	> File Name: 2.74.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Thu 30 Apr 2015 09:52:02 PM CST
 ************************************************************************/

#include<stdio.h>
#include<limits.h>

int tsub_ovf(int x, int y){
    int diff = x - y;
    int pos_overflow = !(x&INT_MIN)&&(y&INT_MIN)&&(diff&INT_MIN);
    int neg_overflow = (x&INT_MIN)&&!(y&&INT_MIN)&&!(diff&INT_MIN);
    (pos_overflow && (diff=1)) || (neg_overflow&&(diff=1));
    return diff;
}

int main(){
    printf("%X\t%X\t%X\n", tsub_ovf(INT_MAX, INT_MIN), tsub_ovf(INT_MIN, INT_MAX), tsub_ovf(1, 1));
    return 0;
}
