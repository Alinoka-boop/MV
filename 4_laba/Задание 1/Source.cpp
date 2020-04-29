#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

	setlocale(0, "");

	cout << "Исходная матрица: " << endl;
	double array[3][4] = {
		{ 3.01,	-0.14, -0.15, 1.00 },
		{ 1.11,	0.13, -0.75, 0.13 },
		{ 0.17, -2.11, 0.71, 0.17 },
	};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	cout << "----------------------" << endl;

	double p;

	for (int k = 0; k < 3; k++) {
		for (int j = k + 1; j < 4; j++) {
			array[k][j] /= array[k][k];
		}

		cout << "Разделим " << k + 1 << " строку на " << array[k][k] << endl;
		array[k][k] = 1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				cout << array[i][j] << " ";
			}
			cout << endl;
		}
		cout << "----------------------" << endl;

		for (int i = 0; i < 3; i++) {
			if (i == k) continue;
			p = array[i][k];
			for (int j = k; j < 4; j++) {
				array[i][j] -= (array[k][j] * p);
			}
			cout << "Вычитаем " << k + 1 << " строку с оставшихся:" << endl;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 4; j++) {
					cout << array[i][j] << " ";
				}
				cout << endl;
			}
			cout << "----------------------" << endl;
		}
	}

	cout << "Матрица: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	cout << "----------------------" << endl;

	double* mas = new double[4];

	for (int i = 0; i < 4; i++) {
		mas[i] = array[i][3];
	}

	cout << "Корни уравнения: " << endl;
	for (int i = 0; i < 3; i++) {
		cout << "X" << (i + 1) << ": " << round(mas[i] * 1000.0) / 1000.0 << endl;
	}
	cout << "----------------------" << endl;

	system("pause");
	return 0;
}
