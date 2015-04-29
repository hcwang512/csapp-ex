/*************************************************************************
	> File Name: 2.67.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Wed 29 Apr 2015 06:02:06 AM PDT
 ************************************************************************/

#include<stdio.h>

/*
 *在c语言标准中，右移超过位宽度的结果是未定义的，因此在部分机型中是会引发错误的。
 *解决这个问题可以直接给出右移超过了位宽度的结果，看看这个数是不是0；另一种解决办法是分多次来位移。
 */
int bad_int_size_is_32(){
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
}

int main(){
    printf("%d\n", bad_int_size_is_32());
    return 0;
}
