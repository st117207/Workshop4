#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>


void inputdata(float arr1[], float arr2[], int n)
{
	std::ifstream inputFile("InputData.csv");
	float firstCol = 0;
	float secondCol = 0;
	for (int i = 0; i < n; i++) {
		inputFile >> firstCol >> secondCol;
		arr1[i] = firstCol;
		arr2[i] = secondCol;
	}
}
void mass(float arr1[], float arr2[], int n)
{
	for (int i = 0; i < n; i++) {
		arr1[i] = arr1[i] * (4 * 3.14 * pow(arr2[i] / 2, 3)) / 3;
	}
}

void outputdata(float arr1[], float arr2[], int n)
{
	mass(arr1, arr2, n);
	std::ofstream outputFile("OutputData.csv");
	for (int i = 0; i < n; ++i)
		outputFile << std::setprecision(1) << arr1[i] << std::endl;

}
int main() {
	int n = 6;
	float data1[6];
	float data2[6];
	inputdata(data1, data2, n);
	outputdata(data1, data2, n);

	return 0;
}
