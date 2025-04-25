#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;



void inputdata(float** arr, int k, int n) {
	ifstream inputFile("InputData.csv");
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			inputFile >> arr[i][j];
		}
	}
}

void calculate_average(float** arr, int k, int n, float average[]) {
	for (int j = 0; j < k; ++j) {
		float sum = 0.0;
		for (int i = 0; i < n; ++i) {
			sum += arr[i][j];
		}
		average[j] = sum / n;
	}
}
void time_error(float** arr, int k, int n, float average[], float terror[]) {
	for (int j = 0; j < k; ++j) {
		float sum = 0.0;
		for (int i = 0; i < n; ++i) {
			sum += pow(arr[i][j] - average[j], 2);
		}
		terror[j] = sqrt(sum / ((n - 1) * n));
	}
}
void acceleration(float** arr, int k, int n, float average[], float terror[], float g[]) {
	float h = 0.272;
	float v0 = 1.050;
	for (int j = 0; j < k; ++j) {
		g[j] = 2 * (h - (v0 * average[j] / 1000)) / pow(average[j] / 1000, 2);
	}
}
void gerror_calc(float** arr, int k, int n, float average[], float terror[], float g[], float gerror[]) {

	for (int j = 0; j < k; ++j) {
		float v0 = 1.050;
		float deltah = 0.0001;
		float h = 0.272;
		float deltav0 = 0.005;

		float temp = average[j] / 1000;
		float tt = std::pow(temp, 4);
		float te = tt;
		float c_h = 4 / (9 * std::pow(temp, 4));
		float c_v_0 = 4 / (9 * std::pow(temp, 2));
		float c_t = ((2 * v0 * temp - 4 * h) / pow(temp, 3)) * ((2 * v0 * temp - 4 * h) / pow(temp, 3));
		gerror[j] = sqrt(c_h * pow(deltah, 2) + c_v_0 * pow(deltav0, 2) + pow(terror[j], 2) * c_t / 1000000);
	}
}


void outputdata(float** arr, int k, int n, float average[], float terror[], float g[], float gerror[]) {
	ofstream outputFile("OutputData.csv");
	calculate_average(arr, k, n, average);
	time_error(arr, k, n, average, terror);
	acceleration(arr, k, n, average, terror, g);
	gerror_calc(arr, k, n, average, terror, g, gerror);
	outputFile << "Аллюминий, Латунь, Сталь, Дерево, Плексиглас, Свинец" << endl;
	for (int j = 0; j < k; ++j) {
		outputFile << std::setprecision(6) << average[j] << "  ";
	}
	outputFile << endl;
	for (int j = 0; j < k; ++j) {
		outputFile << std::setprecision(6) << terror[j] << "  ";
	}
	outputFile << endl;
	for (int j = 0; j < k; ++j) {
		outputFile << std::setprecision(3) << g[j] << "  ";
	}
	outputFile << endl;
	for (int j = 0; j < k; ++j) {
		outputFile << std::setprecision(1) << gerror[j] << "  ";
	}
}

int main() {
	int k = 6;
	int n = 30;
	float** data = new float* [k];
	for (int i = 0; i < n; ++i) {
		data[i] = new float[n];
	}
	float average[6];
	float terror[6];
	float g[6];
	float gerror[6];
	inputdata(data, k, n);
	outputdata(data, k, n, average, terror, g, gerror);

	return 0;
}