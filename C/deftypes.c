int main(){
    short a[2]={1,1};
    int b[2]={1,1};
    long c[2]={1,1};
    
    unsigned d[2]={8472,8472};

    float e[2]={1.2,1.2};
    double f[2]={1.2,1.2};

    char g[2]={a,b};
    
    printf("%u,%u\n",&a[1],&a[0]);
    printf("%u,%u\n",&b[1],&b[0]);
    printf("%u,%u\n",&c[1],&c[0]);
    printf("%u,%u\n",&d[1],&d[0]);
    printf("%u,%u\n",&e[1],&e[0]);
    printf("%u\n",(unsigned)&f[1]-(unsigned)&f[0]);
    printf("%u,%u\n",&g[1],&g[0]);
    printf("%u\n",(unsigned)&f[1]-(unsigned)&f[0]);
    
    while(1);
    return 0;
}
/*
short 16bits
2293606,2293604
int 32bits
2293596,2293592
long(?) 32bits
2293588,2293584
unsigned 32bits
2293580,2293576
float 32bits
2293572,2293568
double 64bits
2293552,2293544
char 8bits
2293543,2293542
*/
