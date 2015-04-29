/*************************************************************************
	> File Name: 2.69.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Wed 29 Apr 2015 06:26:23 AM PDT
 ************************************************************************/

#include<stdio.h>


int rotate_right(int x, int n){
    int w = 32;
    int left = x >> n;
    int right = x <<  w-n;
    return left | right;
}

int main(){
    printf("%X\t%X\n", rotate_right(0x12345678, 4), rotate_right(0x12345678, 20));
    return 0;
}
