/*************************************************************************
	> File Name: 2.71.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Thu 30 Apr 2015 07:30:30 PM CST
 ************************************************************************/

#include<stdio.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum){
    /*return ((int) (word << (24- (bytenum<<3)) )) >> 24;*/
    
    /*
     *int i = (word >> (bytenum<<3) & 0xFF);
     *return (i&0x80)?(i | ~(0xFF)) : i;
     */

    return (word >> (bytenum<<3) & 0xFF) - ((word >> (bytenum << 3)) >> 7 << 31 >> 23);
}

int cast(packed_t word, int bytenum){
    return (int)(char)((word >> (bytenum<<3))&0xFF);
}
int main(){
    for(int i=0; i < 4; i++){
        printf("%d\t%X\t%X\n", i, xbyte(0xE2345678, i), cast(0xE2345678, i));
    }
    return 0;
}
