/*************************************************************************
	> File Name: 2.60.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Fri 24 Apr 2015 08:28:32 AM PDT
 ************************************************************************/

#include<stdio.h>

unsigned replace_byte(unsigned x, unsigned char b, int i){
    unsigned to_replace = ((unsigned) b) << i*8;
    return (x & ~(0xFF << i*8)) | to_replace;
}

int main(){
    printf("%X\n", replace_byte(0x12345678, 0xAB, 2));
    return 0;
}
