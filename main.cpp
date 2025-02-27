#include <iostream>
#include <cmath>
using namespace std;

float** create_matrix(int size); // Инициализация исходной матрицы
void print_matrix(float** matrix, int size, bool exp_m); // Вывод матрицы в консоль
float** reverse_matrix(float** matrix, int size); // Обратная матрица
int minor_matrix(float** matrix, int i, int j, int size); // Минор матрицы
int determ_matrix(float** matrix, int size); // Определитель матрицы
void trans_matrix(float** matrix, int size); // Транспонирование матрицы
float** m_p_matrix(float** one_matrix, float** two_matrix, int size); // Умножение одной матрицы на другую

int main() {
	setlocale(LC_ALL, "RUS");
	const int n = 4;
	float** matrix = create_matrix(n);
	float** trans_matrix = reverse_matrix(matrix, n);
	float** multi_matrix = m_p_matrix(matrix, trans_matrix, n);
	cout << "Исходная матрица" << endl;
	print_matrix(matrix, n, false);
	cout << "Обратная матрица" << endl;
	print_matrix(trans_matrix, n, true);
	cout << "Результат умножения" << endl;
	print_matrix(multi_matrix, n, false);
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
		delete[] trans_matrix[i];
		delete[] multi_matrix[i];
	}
	delete[] matrix;
	delete[] trans_matrix;
	delete[] multi_matrix;
}

// Инициализация матрицы
float** create_matrix(int size) {
	float** matrix = new float* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new float[size];
	}
	int x_coord = 0, y_coord = 0, count = 1;
	for (x_coord; x_coord < size; x_coord++) {
		matrix[y_coord][x_coord] = count;
		count++;
	}
	x_coord--;
	for (y_coord++; y_coord < size; y_coord++) {
		matrix[y_coord][x_coord] = count;
		count++;
	}
	y_coord--;
	x_coord--;
	for (x_coord; x_coord >= 0; x_coord--) {
		matrix[y_coord][x_coord] = count;
		count++;
	}
	x_coord++;
	y_coord--;
	for (y_coord; y_coord > 0; y_coord--) {
		matrix[y_coord][x_coord] = count;
		count++;
	}
	y_coord++;
	for (x_coord++; x_coord < size - 1; x_coord++) {
		matrix[y_coord][x_coord] = count;
		count++;
	}
	x_coord--;
	for (y_coord++; y_coord < size - 1; y_coord++) {
		matrix[y_coord][x_coord] = count;
		count++;
	}
	matrix[y_coord - 1][x_coord - 1] = count;
	return matrix;
}

// Вывод матрицы в консоль
void print_matrix(float** matrix, int size, bool exp_m) {
	if (!exp_m) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				printf("%.0f\t", matrix[i][j]);
			}
			cout << endl;
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
}

// Инициализация обратной матрицы
float** reverse_matrix(float** matrix, int size) {
	float** tran_matrix = new float* [size];
	for (int i = 0; i < size; i++) {
		tran_matrix[i] = new float[size];
	}
	int det_matrix = determ_matrix(matrix, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tran_matrix[i][j] = pow(-1, i + j) * minor_matrix(matrix, i, j, size) / det_matrix;
		}
	}
	trans_matrix(tran_matrix, size);
	return tran_matrix;
}

// Минор матрицы
int minor_matrix(float** matrix, int i, int j, int size) {
	float** m_matrix = new float* [size - 1];
	int determ, x_new = 0, y_new = 0;
	for (int i = 0; i < size - 1; i++) {
		m_matrix[i] = new float[size - 1];
	}
	for (int y = 0; y < size; y++) {
		if (y == i) {
			continue;
		}
		x_new = 0;
		for (int x = 0; x < size; x++) {
			if (x == j) {
				continue;
			}
			m_matrix[y_new][x_new] = matrix[y][x];
			x_new++;
		}
		y_new++;
	}
	determ = m_matrix[0][0] * m_matrix[1][1] * m_matrix[2][2] + m_matrix[1][0] * m_matrix[2][1] * m_matrix[0][2];
	determ += m_matrix[2][0] * m_matrix[0][1] * m_matrix[1][2] - m_matrix[2][0] * m_matrix[1][1] * m_matrix[0][2];
	determ +=  -m_matrix[0][0] * m_matrix[1][2] * m_matrix[2][1] - m_matrix[1][0] * m_matrix[0][1] * m_matrix[2][2];
	for (int i = 0; i < size - 1; i++) {
		delete[] m_matrix[i];
	}
	delete[] m_matrix;
	return determ;
}

// Определитель матрицы
int determ_matrix(float** matrix, int size) {
	int determ = 0;
	int i = 0;
	for (int j = 0; j < size; j++) {
		determ += matrix[i][j] * minor_matrix(matrix, i, j, size) * pow(-1, j);
	}
	return determ;
}

// Транспонирование матрицы
void trans_matrix(float** matrix, int size) {
	int count = 1;
	float temp;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < count; j++) {
			temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
		count++;
	}
}

// Умножение одной матрицы на другую
float** m_p_matrix(float** one_matrix, float** two_matrix, int size) {
	float res;
	float** multiplication = new float* [size];
	for (int i = 0; i < size; i++) {
		multiplication[i] = new float[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			res = 0;
			for (int k = 0; k < size; k++) {
				res += one_matrix[i][k] * two_matrix[k][j];
			}
			multiplication[i][j] = res;
		}
	}
	return multiplication;
}
