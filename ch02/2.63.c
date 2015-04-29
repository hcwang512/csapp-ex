/*************************************************************************
	> File Name: 2.63.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Mon 27 Apr 2015 08:00:19 AM PDT
 ************************************************************************/

#include<stdio.h>


int sra(int x, int k){
    int xsrl = (unsigned) x >> k;
    int mask = ~(~0 << ((sizeof(int)<<3)-k));
    xsrl = mask & xsrl;

}

unsigned srl(unsigned x, int k){
    unsigned xsra = (int) x >> k;
    xsra = xsra & (1<<(8*sizeof(int)-k))-1;
}
