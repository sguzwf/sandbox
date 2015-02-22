void displayBits( unsigned value ){
    unsigned c;/* counter */
    
    /*declare displayMask and left shift 31 bits*/
    unsigned displayMask = 1 << 31;
    
    printf( "%7u = ",value );
    
    /*loop trough bits */
    for ( c = 1; c <=32; c++ ){
    putchar( value & displayMask ? '1' : '0');
    value <<=1; /*Shift value left by 1*/
    
        if (c%8 == 0){/*Output a space after 8 bits*/
            putchar(' ');
        }/*end if*/
    }/*end for*/
    
    putchar('\n');
}/*end function displayBits*/
