#include <string>
#include <vector>
using namespace std;
#pragma once
int findMaxAbsInRow(vector<double> &row);
void swapColumns(vector<vector<double>> &matrix, int firstColumnNum, int secondColumnNum);
void subtractThisRow(vector<double> &mainRow, vector<double> &subtractRow, double coef);
bool tryToMakeDiagonalPredominance(vector<vector<double>> &matrix);
void divideByDiagonal(vector<vector<double>> &matrix);
double countConvergeCoefByRows(vector<vector<double>> &matrix);
double countConvergeCoefByColumns(vector<vector<double>> &matrix);
double countConvergeCoefByEachValue(vector<vector<double>> &matrix);
double countConvergeCoef(vector<vector<double>> &matrix);
vector<double> makeIteration(vector<vector<double>> &matrix, vector<double> &prevResults);
double countPrecision(vector<double> &prevResults, vector<double> &currentResults);
vector<double> countInaccuracyVector(vector<double> &result, vector<double> &prevStep, double convergeCoef);
void substituteWithResult(vector<vector<double>> &matrix, vector<double> &results, int precision);