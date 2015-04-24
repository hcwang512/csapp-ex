/*************************************************************************
	> File Name: 2.58.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Fri 24 Apr 2015 07:56:20 AM PDT
 ************************************************************************/

#include<stdio.h>

/*return 1 if the machine is little_endian, return 1 if the machine is big_endian.*/

int is_little_endian(){
    int i = 1;
    return (* (char *) &i);
}

int main(){
    printf("%d\n", is_little_endian());
    return 0;
}
