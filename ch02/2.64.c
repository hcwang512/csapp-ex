/*************************************************************************
	> File Name: 2.64.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Mon 27 Apr 2015 08:38:14 AM PDT
 ************************************************************************/

#include<stdio.h>

int any_even_one(unsigned x){
    return ~(1 && (x & 0x55555555 ^ 0x55555555));
}

int main(){
    printf("%d\t%d\n", any_even_one(0x55), any_even_one(0x54));
    return 0;
}
