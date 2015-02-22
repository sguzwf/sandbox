#include<stdio.h>

int main(){
    long reallylong;
    long long verylong;
    printf("%d\n",sizeof(reallylong));
    printf("%d\n",sizeof(verylong));
    while(1);
    return 0;
}
/*Result is:
===
4
8
===
I don't know this function "sizeof()" until today!!
*/
