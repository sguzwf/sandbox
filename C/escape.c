int main(){
    /*I found in A~Z*/
    printf("\\a \a A\n");
    printf("\\b \b A\n");
    printf("\\e \e A\n");
    printf("\\f \f A\n");
    printf("\\n \n A\n");
    printf("\\r \r A\n");
    printf("\\t \t A\n");
    printf("\\v \v A\n");
    printf("\xFFFFFF");
    /*Asked Google*/
    printf("\\? \? A\n");
    /*Trigraph----ANSI C only*/
    /*To write C programs using character sets that do not contain all of C's punctuation characters*/
    printf("??=");//#
    printf("??(");//[
    printf("??/");//\
    printf("??)");//]
    printf("??'");//^
    printf("??<");//{
    printf("??!");//|
    printf("??>");//}
    printf("??-");//~
    /*Digraph----Only in /STANDARD=ISOC94 on OpenVMS systems mode*/
    printf("<:");//[
    printf(":>");//]
    printf(" ");//}
    printf("%:");//#
    printf("%:%:");//##
    while(1);
    return 0;
}
