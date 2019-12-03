extern void print_int(int n), print_str(char c[]);

float foo(int x, float y) {
    float z;
    z = x + y;
    return z;
}

void main(void) {
    float main_x;
    main_x = foo(2, 2.5);
}
