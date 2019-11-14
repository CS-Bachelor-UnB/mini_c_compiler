extern void print_str(char s[]), print_int(int i);

int foo(int i) {
    return i;
}

void main(void) {
    int x;
    x = foo(5);
    print_int(x);
}

int foo(float f) {
    return f;
}