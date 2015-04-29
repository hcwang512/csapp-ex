/*************************************************************************
	> File Name: 2.70.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Wed 29 Apr 2015 06:46:59 AM PDT
 ************************************************************************/

#include<stdio.h>

int fits_bits(int x, int n){
    /*
     *先截去后n位，若x为正数，则剩下的全为0，若x为负数，则剩下的全为1. 因此判断的依据是剩下的全为0或1
     */
    int left = x & ~((1<<n)-1);
    return !left || !(~left);
}

int main(){
    printf("%d\t%d\n", fits_bits(0xFF, 10), fits_bits(0xFF, 6));
    return 0;
}
