/*************************************************************************
	> File Name: 2.65.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Mon 27 Apr 2015 05:28:49 PM PDT
 ************************************************************************/

#include<stdio.h>


int even_ones(unsigned x){
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return !(x&0x01);
}
