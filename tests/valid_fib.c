 void print_int(int n);
extern void print_string(char s[]);

int factorial(int n) {
	if (n <= 1)
		return 1;

	return (n * factorial(n - 1));
	
}

void main(void) {
	int n, result;
	
	n = 6;
	
	result = factorial(n);
	
	print_string("Factorial of ");
	print_int(n);
	print_string(" is ");
	print_int(result);
	print_string("\n");
}
