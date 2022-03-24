// 3rd order smoothing function
int smooth(int in) {
	static int b1 = 0;
	static int b2 = 0;

	int val = (in + b1 + b2) * .33;

	b2 = b1;
	b1 = in;

	return val;
}