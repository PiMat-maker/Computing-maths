#include "workvector.h"
#include "io.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool trySetElement(string value, void* elem, char type) {
	try {
		if (type == 'd') {
			if (!(checkIsDouble(value))) {
				printError("Wrong input (it's not a number)");
				return false;
			}
			int posOfComma = value.find(",");
			if (posOfComma != string::npos) {
				value = value.replace(posOfComma, 1, ".");
			}
			*((double*)elem) = stod(value);
		}
		else {
			*((int*)elem) = stoi(value);
			if (to_string(*((int*)elem)) != value) {
				*((int*)elem) = 0;
				throw - 1;
			}
		}
	}
	catch (invalid_argument ex) {
		printError("Wrong input (it's not a number)");
		return false;
	}
	catch (out_of_range ex) {
		printError("Wrong input (number is to big)");
		return false;
	}
	catch (int a) {
		printError("Wrong input (it's not an int)");
		return false;
	}

	return true;
}

void setVector(vector<vector<double>> &matrix, int size) {
	vector<vector<double>> vector(size, vector<double>(size + 1, 0));
	matrix = vector;
}

void initializeVector(vector<vector<double>> &matrix) {

	for (size_t i = 0; i < matrix.size(); ++i) {
		for (size_t j = 0; j < matrix.size() + 1; ++j) {
			string value;
			string text = "Enter a number [" + to_string(i) + ", " + to_string(j) + "]";
			do {
				talkToUser(text);
				readElement(&value);
			} while (!trySetElement(value, &(matrix[i][j]), 'd'));
		}
	}
}