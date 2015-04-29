/*************************************************************************
	> File Name: 2.68.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Wed 29 Apr 2015 06:20:03 AM PDT
 ************************************************************************/

#include<stdio.h>


int lower_bit(int x, int n){
    int w = sizeof(int);
    int mask = (1 << n) -1;
    return mask & x;
}

int main(){
    printf("0x%X\n", lower_bit(0x78ABCDEF, 8));
    return 0;
}
