#include <iostream>
#include <windows.h>
#include <math.h>
#include <tchar.h>
#include <complex>
#include <iomanip>

using namespace std;

unsigned int root2(double a, double b, double c, double x[2]) {
	if (a == 0) {
		if (c == 0) {
			x[0] = 0.;
		}
		else {
			if (b == 0) return 0;
			x[0] = -c / b;
		}
		return 1;
	}
	else {
		if (c == 0) {
			x[0] = 0.;
			x[1] = -b / a;
		}
		else {
			b *= -0.5;
			double d = b * b - a * c;
			if (d < 0) return 0;
			d = sqrt(d);
			double t = b > 0 ? b + d : b - d;
			x[0] = c / t;
			x[1] = t / a;
		}
	}
	return 2;
}

// x^2 + a * x + b = 0 - приведённое квадратное уравнение

unsigned int root2(double a, double b, double x[2]) {
	if (b == 0) {
		x[0] = 0.;
		x[1] = -a;
	}
	else {
		a *= -0.5;
		double d = a * a - b;
		if (d < 0) return 0;
		d = sqrt(d);
		x[1] = a > 0 ? a + d : a - d;
		x[0] = b / x[1];
	}
	return 2;
}

double cubic(double a, double b) {
	double s = 1.;
	while (b + a > -1.) {
		a *= 4.;
		b *= 8.;
		s *= 0.5;
	}
	while (b + a + a < -8.) {
		a *= 0.25;
		b *= 0.125;
		s *= 2.;
	}
	double x = 1.5;
	x -= (x * (x * x + a) + b) / (3. * x * x + a);
	x -= (x * (x * x + a) + b) / (3. * x * x + a);
	x -= (x * (x * x + a) + b) / (3. * x * x + a);
	x -= (x * (x * x + a) + b) / (3. * x * x + a);
	x -= (x * (x * x + a) + b) / (3. * x * x + a);
	x -= (x * (x * x + a) + b) / (3. * x * x + a);
	x -= (x * (x * x + a) + b) / (3. * x * x + a);
	x -= (x * (x * x + a) + b) / (3. * x * x + a);
	x -= (x * (x * x + a) + b) / (3. * x * x + a);
	return x * s;
}

// x^3 + p * x + q = 0

int root3s(double p, double q, double * x) {
	if (q < 0) {
		*x = cubic(p, q);
	}
	else
		if (q > 0) {
			*x = -cubic(p, -q);
		}
		else {
			*x = 0;
		}
	return 1 + root2(*x, p + (*x)*(*x), x + 1);
}

// x^3 + a * x^2 + b * x + c = 0

int root3(double a, double b, double c, double * x) {
	if (c == 0) {
		*x = 0;
	}
	else {
		const double a3 = a / 3.;
		const double p = b - a3 * a;
		const double q = c - (a3 * a3 + p) * a3;
		if (q < 0) {
			*x = cubic(p, q);
		}
		else
			if (q > 0) {
				*x = -cubic(p, -q);
			}
			else {
				*x = 0;
			}
			*x -= a3;
			const double t = *x * (*x * 3. + a * 2.) + b;
			if (fabs(t) > 1e-3) {
				*x -= (*x * (*x * (*x + a) + b) + c) / t;
			}
			a += *x;
			b += *x * a;
	}
	return 1 + root2(a, b, x + 1);
}

int root4s(double p, double q, double r, double * x) {
	if (r == 0) {
		*x = 0;
		return 1 + root3s(p, q, x + 1);
	}
	if (q == 0) {
	m1:     double t[2];
		int n = root2(p, r, t);
		if (n == 0) return 0;
		if (t[0] >= 0) {
			x[0] = sqrt(t[0]);
			x[1] = -x[0];
			n = 2;
		}
		else {
			n = 0;
		}
		if (t[1] >= 0) {
			x[n] = sqrt(t[1]);
			x[n + 1] = -x[n];
			n += 2;
		}
		return n;
	}
	int n = root3(p + p, p * p - 4. * r, -q * q, x);
	double a = *x;
	if (n == 3) {
		if (a < x[1]) a = x[1];
		if (a < x[2]) a = x[2];
	}
	if (a <= 0) goto m1;
	p += a;
	a = sqrt(a);
	const double b = q / a;
	n = root2(a, 0.5 * (p - b), x);
	n += root2(-a, 0.5 * (p + b), x + n);
	return n;
}

// x^4 + a * x^3 + b * x^2 + c * x + d = 0

int root4(double a, double b, double c, double d, double * x) {
	if (a == 0) {
		return root4s(b, c, d, x);
	}
	if (d == 0) {
		*x = 0;
		return 1 + root3(a, b, c, x + 1);
	}
	const double e = a / 4;
	const double h = e * e;
	const double p = -6 * h + b;
	const double q = 8 * h * e - 2 * b * e + c;
	const double r = -3 * h * h + b * h - c * e + d;
	const int n = root4s(p, q, r, x);
	for (int i = 0; i < n; ++i) x[i] -= e;
	return n;
}

int main() {
	setlocale(LC_ALL, "Rus");
	double A[4][4] = { 
		{ 2, 1, 1.4, 0.5 },
		{ 1, 1, 0.5, 1 },
		{ 1.4, 0.5, 2, 1.2 },
		{ 0.5, 1, 1.2, 0.5 } 
	};

	double M[20][20] = { 0 },
		P[20][20] = { 0 },
		B[20][20] = { 0 },
		S1[20][20], 
		S[4][4] = { 
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};

	int N = 4;
	double **F = new double *[20];
	double * x = new double[4];
	for (int i = 0; i < 20; i++)
		F[i] = new double[20];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			F[i][j] = 0;
		}
	}

	int k = 1;

	// нахождение коэффициентов матрицы M[N-1] и M[N-1][-1]
	for (int m = N - 2; m >= 0; m--) {
		cout << (m - 1) << "-ый проход" << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i != m) {
					M[i][i] = 1;
					P[i][i] = 1;
					if (i != j) {
						M[i][j] = 0;
						P[i][j] = 0;
					}
				}
				else {
					if (i == m) {
						if (i != j) {
							M[i][j] = -A[i + 1][j] / A[i + 1][i];
						}
						else {
							M[i][j] = 1 / A[i + 1][i];
						}
						P[i][j] = A[i + 1][j];
					}
				}
			}
		}

		cout << "\nМатрица M[" << (m + 1) << "]" << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << setw(10) << M[i][j];
			}
			cout << endl;
		}

		cout << "\nМатрица M[" << (m + 1) << "][-1]" << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << setw(10) << P[i][j];
			}
			cout << endl;
		}

		double z = 0;
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				for (int j = 0; j < N; j++) {
					z += S[i][j] * M[j][k];
				}
				S1[i][k] = z;
				z = 0;
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				S[i][j] = S1[i][j];
			}
		}
		double q = 0;
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				for (int j = 0; j < N; j++) {
					q += A[i][j] * M[j][k];
				}
				B[i][k] = q;
				q = 0;
			}
		}
		cout << "\nМатрица A[" << k << "]" << endl;
		k++;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << setw(15) << B[i][j];
			}
			cout << endl;
		}

		double u = 0;
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				for (int j = 0; j < N; j++) {
					u += P[i][j] * B[j][k];
				}
				F[i][k] = u;
				u = 0;
			}
		}

		cout << "\nМатрица F" << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << setw(10) << round(F[i][j] * 1000.0) / 1000.0;
			}
			cout << endl;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				A[i][j] = F[i][j];
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << setw(10) << round(S[i][j] * 1000.0) / 1000.0;
			}
			cout << endl;
		}
	}

	cout << "\nМатрица Фробениуса: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << setw(10) << round(F[i][j] * 1000.0) / 1000.0;
		}
		cout << endl;
	}

	cout << "Собственные числа: " << endl;
	root4(-F[0][0], -F[0][1], -F[0][2], -F[0][3], x);
	for (int i = 0; i < 4; i++) {
		cout << "x[" << i << "]=" << setw(10) << round(x[i] * 1000.0) / 1000.0 << endl;
	}

	double Y[4][4];
	int v = 3;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			Y[i][j] = pow(x[j], v);
			v--;
		}
		v = 3;
	}

	double X1[4][4];
	for (int k = 0; k < 4; k++) {
		for (int j = 0; j < 4; j++) {
			X1[j][k] = 0;
			for (int i = 0; i < 4; i++)
				X1[j][k] += S[j][i] * Y[i][k];
		}
	}

	cout << "Собственные вектора матрицы: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << setw(10) << round(X1[i][j] * 1000.0) / 1000.0;
		}
		cout << endl;
	}

	system("pause");
	return 0;
}
