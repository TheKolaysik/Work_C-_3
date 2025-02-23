#include <iostream>
#include <cmath>
using namespace std;

float** create_matrix(int size);
void print_matrix(float** matrix, int size);
float** reverse_matrix(float** matrix, int size);
int minor_matrix(float** matrix, int i, int j, int size);
int determ_matrix(float** matrix, int size);
void trans_matrix(float** matrix, int size);
float** m_p_matrix(float** one_matrix, float** two_matrix, int size);

int main() {
	setlocale(LC_ALL, "RUS");
	const int n = 4;
	float** matrix = create_matrix(n);
	float** trans_matrix = reverse_matrix(matrix, n);
	float** multi_matrix = m_p_matrix(matrix, trans_matrix, n);
	cout << "Исходная матрица" << endl;
	print_matrix(matrix, n);
	cout << "Обратная матрица" << endl;
	print_matrix(trans_matrix, n);
	cout << "Результат умножения" << endl;
	print_matrix(multi_matrix, n);
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
		delete[] trans_matrix[i];
		delete[] multi_matrix[i];
	}
	delete[] matrix;
	delete[] trans_matrix;
	delete[] multi_matrix;
}

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
	for (y_coord; y_coord < size; y_coord++) {
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
	for (x_coord; x_coord < size - 1; x_coord++) {
		matrix[y_coord][x_coord] = count;
		count++;
	}
	x_coord--;
	for (y_coord; y_coord < size - 1; y_coord++) {
		matrix[y_coord][x_coord] = count;
		count++;
	}
	matrix[y_coord - 1][x_coord - 1] = count;
	return matrix;
}

void print_matrix(float** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
}

float** reverse_matrix(float** matrix, int size) {
	cout << "trans" << endl;
	float** tran_matrix = new float* [size];
	for (int i = 0; i < size; i++) {
		tran_matrix[i] = new float[size];
	}
	int det_matrix = determ_matrix(matrix, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tran_matrix[i][j] = pow(-1, i + j + 2) * minor_matrix(matrix, i, j, size) / det_matrix;
		}
	}
	trans_matrix(tran_matrix, size);
	return tran_matrix;
}

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
		y_new = 0;
		for (int x = 0; x < size; x++) {
			if (x == j) {
				continue;
			}
			//cout << x << " " << y << " " << x_new << " " << y_new << endl;
			m_matrix[y_new][x_new] = matrix[y][x];
			y_new++;
		}
		x_new++;
	}
	determ = m_matrix[0][0] * m_matrix[1][1] * m_matrix[2][2] + m_matrix[0][1] * m_matrix[1][2] * m_matrix[2][0] +
		+ m_matrix[0][2] * m_matrix[1][0] * m_matrix[2][1] - m_matrix[0][2] * m_matrix[1][1] * m_matrix[2][0] -
		- m_matrix[0][0] * m_matrix[1][2] * m_matrix[2][1] - m_matrix[0][1] * m_matrix[1][0] * m_matrix[2][2];
	for (int i = 0; i < size - 1; i++) {
		delete[] m_matrix[i];
	}
	delete[] m_matrix;
	return determ;
}

int determ_matrix(float** matrix, int size) {
	int determ = 0;
	int i = 0;
	for (int j = 0; j < size; j++) {
		determ += matrix[i][j] * minor_matrix(matrix, i, j, size) * pow(-1, j + 2);
	}
	return determ;
}

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
