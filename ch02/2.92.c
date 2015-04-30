/*************************************************************************
	> File Name: 2.92.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Fri 01 May 2015 12:35:22 AM CST
 ************************************************************************/

#include<stdio.h>

typedef unsigned float_bits;

float_bits float_negate(float_bits f){
    float_bits sign = f >> 31;
    float_bits exp = f >> 23 & 0xFF;
    float_bits frac = f & 0x7FFFFF;
    if(exp == 0xFF && frac){
        return f;
    }
    return ~(sign<<31) | (exp<<23) | frac;
}
