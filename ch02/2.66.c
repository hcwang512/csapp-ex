/*************************************************************************
	> File Name: 2.66.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Wed 29 Apr 2015 04:50:46 AM PDT
 ************************************************************************/

#include<stdio.h>

int leftmost_one(unsigned x){
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x - (x>>1);
}

int main(){
    printf("%X\t%X\n", leftmost_one(0xFF0000), leftmost_one(0x0));
    return 0;
}
