int foo(int foo_x, float foo_y);
float bar(int bar_x, float bar_y);
char doo(int doo_x, float doo_y);

void main(void) {
	int x;
	float y;
	char z;

	x = 2;
	y = 5.0;
	z = 'a';

	x = foo(x, y);
	y = bar(x, y);
	z = doo(x, y);
}

int foo(int foo_x, float foo_y) { return foo_x;}
float bar(int bar_x, float bar_y) {return bar_y;}
char doo(int doo_x, float doo_y) {return 'a';}
