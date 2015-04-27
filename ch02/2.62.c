/*************************************************************************
	> File Name: 2.62.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Mon 27 Apr 2015 07:02:33 AM PDT
 ************************************************************************/

#include<stdio.h>

int int_shift_logical(){
    int shifted = (~0>>((sizeof(int)<<3)));
    return 1&&shifted;
}

int main(){
    printf("%d\n", int_shift_logical());
    return 0;
}
