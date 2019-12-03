/* 
*  INVALID types for operation
*  and mismatched type passed to foo().
*/

float foo(int x, char y) {
    char z;
    z = x + y;
    return z;
}

void main(void) {
    float main_x;
    main_x = foo(2, 2.5);
}
