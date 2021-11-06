#include "io.h"
#include "workvector.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void talkToUser(string text) {
	cout << text << "\n";
}

void readElement(string* value) {
	cin >> *value;
}

void printError(string error) {
	cout << error << "\n";
}

void readNameOfFile(string* nameOfFile) {
	while (true) {
		talkToUser("Enter valid name of file");
		cin >> *nameOfFile;
		ifstream file(*nameOfFile);
		if (!file.good()) {
			printError("Wrong name of file");
		}
		else {
			break;
		}
	}
}

void printRow(vector<double> &row, int precision) {
	cout << "|";
	for (size_t i = 0; i < row.size(); ++i) {
		cout.precision(precision);
		cout.width(precision + 4);
		cout << row[i] << " ";
	}
	cout << "|\n";
}

void printMatrix(vector<vector<double>> &matrix, int precision) {

	for (size_t i = 0; i < matrix.size(); ++i) {
		printRow(matrix[i], precision);
	}
}

vector<string> splitString(string line) {
	vector<string> strings;
	int pos = line.find(' ');
	while (pos != string::npos) {
		strings.push_back(line.substr(0, pos));
		line.erase(0, pos + 1);
		pos = line.find(' ');
	}
	strings.push_back(line);
	return strings;
}

bool checkIsDouble(string value) {
	int i = 0;
	bool thereIsComma = false;
	bool thereIsSign = false;
	bool thereIsNotNullDigit = false;
	if (value[i] == '-') {
		thereIsSign = true;
		++i;
	}
	if (thereIsSign && !isdigit(value[i])) return false;
	while (i < value.length()) {
		if (!isdigit(value[i])) {
			if (!thereIsComma && (value[i] == ',' || value[i] == '.') && (i + 1) < value.length()) {
				thereIsComma = true;
			}
			else {
				return false;
			}
		}
		else {
			if (value[i] != '0') thereIsNotNullDigit = true;
		}
		++i;
	}
	if (thereIsSign && !thereIsNotNullDigit) return false;
	return true;
}

void inputFromConsolePrecision(vector<vector<double>> &matrix, int* precision) {

	string value;

	while (*precision < 1) {
		do {
			talkToUser("Enter result precision");
			readElement(&value);
		} while (!trySetElement(value, precision, 'i'));
		if (*precision < 1) printError("Wrong precision (must be precision > 0)");
	}

}

void inputFromConsoleSize(int* size) {

	string value;

	while (*size < 1 || *size > 20) {
		do {
			talkToUser("Enter size of matrix");
			readElement(&value);
		} while (!trySetElement(value, size, 'i'));
		if (*size < 1 || *size > 20) printError("Wrong size (must be 1 <= size <= 20)");
	}
}

void inputFromFilePrecision(vector<vector<double>> &matrix, int* precision, ifstream& in) {

	vector<string> values;
	if (in.is_open()) {
		string line;
		while (*precision < 1 && getline(in, line)) {

			values = splitString(line);
			for (int k = 0; k < values.size(); ++k) {
				if (trySetElement(values[k], precision, 'i')) break;
			}
		}
	}
}

void inputFromFileSize(int* size, ifstream& in) {

	vector<string> values;
	if (in.is_open()) {
		string line;
		while ((*size <= 1 || *size > 20) && getline(in, line)) {

			values = splitString(line);
			for (int k = 0; k < values.size(); ++k) {
				if (trySetElement(values[k], size, 'i')) {
					break;
				}
			}
		}
	}
	if (!*size) {
		printError("Size is null");
	}
}

void inputFromFileData(vector<vector<double>> &matrix, ifstream& in) {

	int size = matrix.size();
	vector<string> values;
	if (in.is_open()) {
		string line;
		int i = 0, j = 0;
		while (i < size && getline(in, line)) {

			values = splitString(line);
			for (int k = 0; k < values.size(); ++k) {
				if (trySetElement(values[k], &(matrix[i][j]), 'd')) {
					++j;
					if (j > size) {
						++i;
						j = 0;
						if (i == size) break;
					}
				}
			}
		}
		in.close();
		if (i < size) printError("Matrix is not full. Missing elements will be replace by 0");
	}

}