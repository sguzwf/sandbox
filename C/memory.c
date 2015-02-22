int main(){
    int a[2]={0};
    char b[2]={0};
    int c[3]={0};
    //c[0]=atoi(&a[1]-&a[0]);
    c[1]=&a[0];
    c[2]=&a[1];
    printf("%d\n",c[0]);
    printf("%d\n",c[2]-c[1]);
    while(1);
    return 0;
}
