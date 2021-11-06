#include <string>
#include <vector>
#include <fstream>
using namespace std;
#pragma once
void talkToUser(string text);
void readElement(string* value);
void printError(string error);
void readNameOfFile(string* nameOfFile);
void printRow(vector<double> &row, int precision);
void printMatrix(vector<vector<double>> &matrix, int precision);
vector<string> splitString(string line);
bool checkIsDouble(string value);
void inputFromConsolePrecision(vector<vector<double>> &matrix, int* precision);
void inputFromConsoleSize(int* size);
void inputFromFilePrecision(vector<vector<double>> &matrix, int* precision, ifstream& in);
void inputFromFileSize(int* size, ifstream& in);
void inputFromFileData(vector<vector<double>> &matrix, ifstream& in);