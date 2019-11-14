/* 
*  INVALID operation
*/

float foo(int x, float y) {
    float z[3];
    z[0] = x;
    return z['s'];
}

void main(void) {
    float y;
    int x;

    x = 2;
    y = 3.5;

    y = foo(x, y);
}