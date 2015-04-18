/*************************************************************************
	> File Name: decimal_to_hex.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: Sat 18 Apr 2015 07:29:03 AM PDT
 ************************************************************************/
#include <stdio.h>
/*#include <stdlib.h>*/

/*
 *The easiest way to do this task is using '%X'.
 */
int atoi(const char *str){
    int re = 0;
    while(*str!='\0'){
        re = 10*re + *str++ - '0';
    }
    return re;
}

int main(int argc, char *argv[]){
    for (int i = 1; i < argc; i++){
        int decimal_number = atoi(argv[i]);
        char hex[20];
        printf ("The number in decimal is: %d\n", decimal_number);
        int  value, counter = 0;
        while(decimal_number != 0){
            value = decimal_number % 16;
            decimal_number /= 16;
            switch(value){
                case 10:
                    hex[counter] = 'A';
                    break;
                case 11:
                    hex[counter] = 'B';
                    break;
                case 12:
                    hex[counter] = 'C';
                    break;
                case 13:
                    hex[counter] = 'D';
                    break;
                case 14:
                    hex[counter] = 'E';
                    break;
                case 15:
                    hex[counter] = 'F';
                    break;
                default:
                    hex[counter] = value + '0';
                    break;

            }
            counter++;
        }
        hex[counter] = '\0';
        printf("The number in hexadecimal is: ");
        while(counter!=0){
            printf("%c", hex[--counter]);
        }
        printf("\n");
    }
    return 0;
} 

