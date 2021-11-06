#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include "io.h"

using namespace std;

int findMaxAbsInRow(vector<double> &row) {
	double max = abs(row[0]);
	int pos = 0;
	for (int i = 0; i < row.size() - 1; ++i) {
		if (max < abs(row[i])) {
			max = abs(row[i]);
			pos = i;
		}
	}
	return pos;
}

void swapColumns(vector<vector<double>> &matrix, int firstColumnNum, int secondColumnNum) {
	if (firstColumnNum == secondColumnNum) return;
	for (int i = 0; i < matrix.size(); ++i) {
		double temp = matrix[i][firstColumnNum];
		matrix[i][firstColumnNum] = matrix[i][secondColumnNum];
		matrix[i][secondColumnNum] = temp;
	}
}

void subtractThisRow(vector<double> &mainRow, vector<double> &subtractRow, double coef) {
	for (int i = 0; i < subtractRow.size(); ++i) {
		subtractRow[i] -= mainRow[i] * coef;
	}
}

bool tryToMakeDiagonalPredominance(vector<vector<double>> &matrix) {

	for (int thisRow = 0; thisRow < matrix.size(); ++thisRow) {
		int columnNum = findMaxAbsInRow(matrix[thisRow]);
		if (matrix[thisRow][columnNum] == 0 || columnNum < thisRow) return false;
		swapColumns(matrix, thisRow, columnNum);
	}
	return true;
}

void divideByDiagonal(vector<vector<double>> &matrix) {
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			if (i == j) { continue; }
			matrix[i][j] /= matrix[i][i];
		}
		matrix[i][i] = 0;
	}
}

double countConvergeCoefByRows(vector<vector<double>> &matrix) {
	double max = 0;

	for (int i = 0; i < matrix.size(); ++i) {
		double sum = 0;
		for (int j = 0; j < matrix.size(); ++j) {
			sum += abs(matrix[i][j]);
		}
		if (max < sum) max = sum;
	}
	if (max < 1) return max;
	return 0;
}

double countConvergeCoefByColumns(vector<vector<double>> &matrix) {
	double max = 0;

	for (int j = 0; j < matrix.size(); ++j) {
		double sum = 0;
		for (int i = 0; i < matrix.size(); ++i) {
			sum += abs(matrix[i][j]);
		}
		if (max < sum) max = sum;
	}
	if (max < 1) return max;
	return 0;
}

double countConvergeCoefByEachValue(vector<vector<double>> &matrix) {
	double sum = 0;
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix.size(); ++j) {
			sum += pow(matrix[i][j], 2);
		}
	}
	sum = sqrt(sum);
	if (sum < 1) return sum;
	return 0;
}

double countConvergeCoef(vector<vector<double>> &matrix) {
	double convergeCoef = 0;
	convergeCoef = countConvergeCoefByRows(matrix);
	if (convergeCoef) return convergeCoef;
	convergeCoef = countConvergeCoefByColumns(matrix);
	if (convergeCoef) return convergeCoef;
	convergeCoef = countConvergeCoefByEachValue(matrix);
	return convergeCoef;
}

vector<double> makeIteration(vector<vector<double>> &matrix, vector<double> &prevResults) {
	vector<double> results;
	for (int i = 0; i < matrix.size(); ++i) {
		double sum = 0;
		for (int j = 0; j < matrix.size(); ++j) {
			sum += matrix[i][j] * prevResults[j];
		}
		sum = (-sum) + matrix[i][matrix.size()];
		results.push_back(sum);
	}
	return results;
}

double countPrecision(vector<double> &prevResults, vector<double> &currentResults) {
	double max = abs(prevResults[0] - currentResults[0]);
	for (int i = 1; i < prevResults.size(); ++i) {
		if (max < abs(prevResults[0] - currentResults[0])) {
			max = abs(prevResults[0] - currentResults[0]);
		}
	}
	return max;
}

vector<double> countInaccuracyVector(vector<double> &result, vector<double> &prevStep, double convergeCoef) {
	vector<double> inaccuracyVector;
	for (int i = 0; i < result.size(); ++i) {
		double inaccuracy = convergeCoef / (1 - convergeCoef) * abs(result[i] - prevStep[i]);
		inaccuracyVector.push_back(inaccuracy);
	}
	return inaccuracyVector;
}

void substituteWithResult(vector<vector<double>> &matrix, vector<double> &results, int precision) {
	vector<double> total;
	for (int i = 0; i < matrix.size(); ++i) {
		double temp = 0;
		for (int j = 0; j < matrix.size(); ++j) {
			temp += matrix[i][j] * results[j];
		}
		temp -= matrix[i][matrix.size()];
		total.push_back(temp);
	}

	printRow(total, precision);
}