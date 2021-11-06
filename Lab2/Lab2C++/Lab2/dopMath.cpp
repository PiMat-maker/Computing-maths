#include <cmath>
#define PI 3.14159265    

double countPlus(double x, double y) {
	return x + y;
}

double countMinus(double x, double y) {
	return x - y;
}

double countMultiply(double x, double y) {
	return x * y;
}

double countDivision(double x, double y) {
	return x / y;
}

double countPower(double x, double y) {
	return pow(x, y);
}

double countLog(double x) {
	return log(x);
}

double countSin(double x) {
	return sin(x * PI / 180);
}

double countCos(double x) {
	return cos(x * PI / 180);
}

double countTg(double x) {
	return tan(x * PI / 180);
}

double countCtg(double x) {
	if (tan(x) != 0) {
		return 1 / tan(x * PI / 180);
	}
	return NULL;
}