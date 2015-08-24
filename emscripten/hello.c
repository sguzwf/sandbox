#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    char *hello = (char*)malloc(sizeof(char) * 6);
    hello[0] = 'h';
    hello[1] = 'e';
    hello[2] = 'l';
    hello[3] = 'l';
    hello[4] = 'o';
    hello[5] = '\0';
    printf(hello);
    return 0;
}
