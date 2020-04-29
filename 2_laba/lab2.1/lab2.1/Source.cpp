#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

	setlocale(0, "");

	cout << "Исходная матрица: " << endl;
	double array[4][5] = { { 15.7, 6.6, -5.7, 11.5, -2.4 },
	{ 8.8, -6.7, 5.5, -4.5, 5.6 },
	{ 6.3, -5.7, -23.4, 6.6, 7.7 },
	{ 14.3, 8.7, -15.7, -5.8, 23.4 } };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	cout << "----------------------" << endl;

	double p;

	for (int k = 0; k < 4; k++) {
		for (int j = k + 1; j < 5; j++) {
			array[k][j] /= array[k][k];
		}

		cout << "Разделим " << k + 1 << " строку на " << array[k][k] << endl;
		array[k][k] = 1;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				cout << array[i][j] << " ";
			}
			cout << endl;
		}
		cout << "----------------------" << endl;

		for (int i = k + 1; i < 4; i++) {
			p = array[i][k];
			for (int j = k; j < 5; j++) {
				array[i][j] -= (array[k][j] * p);
			}
		}
		cout << "Вычитаем " << k + 1 << " строку с оставшихся:" << endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				cout << array[i][j] << " ";
			}
			cout << endl;
		}
		cout << "----------------------" << endl;
	}


	cout << "Ступенчатая матрица: " << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	cout << "----------------------" << endl;

	double* mas = new double[4];

	mas[3] = array[3][4];
	for (int i = 2; i >= 0; i--) {
		mas[i] = array[i][4];
		for (int j = 3; j >= i + 1; j--) {
			mas[i] -= array[i][j] * mas[j];
		}
	}

	cout << "Корни уравнения: " << endl;
	for (int i = 0; i < 4; i++) {
		cout << "X" << (i + 1) << ": " << round(mas[i]*1000.0)/1000.0 << endl;
	}
	cout << "----------------------" << endl;

	system("pause");
	return 0;
}
