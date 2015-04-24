/*************************************************************************
	> File Name: 2.59.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Fri 24 Apr 2015 08:03:59 AM PDT
 ************************************************************************/

#include<stdio.h>

int replace(int x, int y){
    return (x & 0xFF) | (y & ~0xFF);
}

int main(){
    printf("%X\n", replace(0x89ABCDEF, 0x76543210));
    return 0;
}
