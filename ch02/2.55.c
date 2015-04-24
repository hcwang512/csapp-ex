/*************************************************************************
	> File Name: 2.55.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Fri 24 Apr 2015 07:26:41 AM PDT
 ************************************************************************/

#include<stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len){
    for(int i = 0; i < len; i++){
        printf(" %.2X", start[i]);
    }
    printf("\n");
}

void show_int(int x){
    show_bytes((byte_pointer) &x, sizeof(x));
}

void show_float(float x){
    show_bytes((byte_pointer) &x, sizeof(x));
}

void show_pointer(void *x){
    show_bytes((byte_pointer) &x, sizeof(x));
}

int main(){
    int i = 12345;
    int ival = i;
    float fval = (float) i;
    void *pval = &i;

    show_int(ival);
    show_float(fval);
    show_pointer(pval);

    return 0;
}
