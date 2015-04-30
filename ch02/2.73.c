/*************************************************************************
	> File Name: 2.73.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Thu 30 Apr 2015 09:12:41 PM CST
 ************************************************************************/

#include<stdio.h>
#include<limits.h>

int saturating_add(int x, int y){
    int sum = x + y;
    /*positive overflow only when both x and y is positive, while sum is negative.*/
    int pos_overflow = !(x&INT_MIN)&&!(y&INT_MIN)&&(sum&INT_MIN);
    int neg_overflow = (x&INT_MIN)&&(y&INT_MIN)&&!(sum&INT_MIN);
    
    (pos_overflow&&(sum=INT_MAX)) || (neg_overflow&&(sum=INT_MIN));
    return sum;
}

int main(){
    printf("%X\t%X\t%X\n", saturating_add(INT_MIN, INT_MIN), saturating_add(INT_MAX, INT_MAX), saturating_add(1, 1));
    return 0;
}
