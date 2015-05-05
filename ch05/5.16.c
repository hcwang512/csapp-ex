/*************************************************************************
	> File Name: 5.16.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Sun 03 May 2015 11:56:21 PM CST
 ************************************************************************/

#include<stdio.h>

void inner4(vec_ptr x, vec_ptr y, data_t *dest){
    long int i;
    int length = vec_length(x);
    data_t *xdata = get_vec_start(x);
    data_t *ydata = get_vec_start(y);
    data_t sum = (data_t) 0;
    int limit = length-2;
    for(i = 0; i < limit; i+=3){
        sum += xdata[i] * ydata[i];
        sum += xdata[i+1] * ydata[i+1];
        sum += xdata[i+2] * ydata[i+2];
    }
    for(; i < length; i++){
        sum += xdata[i] * ydata[i];
    }
    *dest = sum;
}

/*A. 在关键路径上两个load 导致CPE下界是2.*/
/*B. 因为浮点数的激发延迟是3.*/
