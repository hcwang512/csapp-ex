/*************************************************************************
	> File Name: 2.91.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Fri 01 May 2015 12:30:48 AM CST
 ************************************************************************/

#include<stdio.h>

typedef unsigned float_bits;

float_bits float_absval(float_bits f){
    float_bits exp = (f >> 23) & 0xFF;
    float_bits frac = f & 0x7FFFFF;
    if (exp == 0xFF && frac){
        return f;
    }
    return exp | frac;
}
