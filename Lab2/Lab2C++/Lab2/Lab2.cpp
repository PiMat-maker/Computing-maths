#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stack>
#include "io.h"
#include "simpleIterations.h"
#include "dopMath.h"
#include "workvector.h"

#pragma comment(lib, "Lab1.lib")

using namespace std;

map<string, function<double(double, double)>> operations;
map<string, function<double(double)>> fcnPtr;
vector<vector<string>> equations;

void initOperations() {
	operations.insert({ "+", countPlus });
	operations.insert({ "-", countMinus });
	operations.insert({ "*", countMultiply });
	operations.insert({ "/", countDivision });
	operations.insert({ "^", countPower });
}

void initFcnPtr() {
	fcnPtr.insert({ "log", countLog });
	fcnPtr.insert({ "sin", countSin });
	fcnPtr.insert({ "cos", countCos });
	fcnPtr.insert({ "tan", countTg });
	fcnPtr.insert({ "ctg", countCtg });
}

void inputFromConsoleEquation(int* numOfEquation, char type) {

	int rightLimit;

	if (type == 'e') {
		rightLimit = 5;
		talkToUser("Please choose the equation:\n1) x^2 - e^(-x) = 0\n2) x^3 - x + 1 = 0\n3) x^2 + 9x + 9 = 0\n4) 2x - sin(x) = 0\n5) x^3 - 0.2x^2 + 0.5x + 1.5 = 0");
	}
	else {
		rightLimit = 3;
		talkToUser("Please choose the system of equations:\n1) 3x - y = 0.9\n   sin(x - 0.6) - y = 1.6\n");
	}

	
	while (*numOfEquation < 1 || *numOfEquation > rightLimit) {
		string eq;
		readElement(&eq);
		try {
			*numOfEquation = stoi(eq);
			if (*numOfEquation < 1 || *numOfEquation > rightLimit) {
				printError("Wrong input (no equation with this number)");
			}
		}
		catch (invalid_argument ex) {
			printError("Wrong input (it's not a number)");
		}
	}

	--*numOfEquation;

}

double M_PI = 3.1415;

void drawGraphic(vector<string> functions) {
	ofstream fout;
	fout.open("../../Variables.txt");
	for (auto function : functions) {
		fout << function << endl;
	}
	fout.close();
	system("python ../../Lab2Python/main.py");
}


void inputBoundaryPoints(double *left, double *right) {

	bool isSetPoints = false;
	while (!isSetPoints) {
		string valA, valB;
		readElement(&valA);
		readElement(&valB);
		replace(valA.begin(), valA.end(), ',', '.');
		replace(valB.begin(), valB.end(), ',', '.');
		try {
			*left = stod(valA);
			*right = stod(valB);
			isSetPoints = true;
		}
		catch (invalid_argument ex) {
			printError("Wrong input (it's not a number)");
		}
	}

	if (*left > *right) {
		*left += *right;
		*right = *left - *right;
		*left -= *right;
	}
}

double getTopNum(stack<double> &data) {
	double num = data.top();
	data.pop();
	return num;
}

void makeOperationWithTwoTopNums(stack<double> &data, stack<string> &signs) {
	double val1 = getTopNum(data);
	double val2 = getTopNum(data);
	auto itOperationOnTop = operations.find(signs.top());
	signs.pop();
	if (itOperationOnTop != operations.end()) val1 = itOperationOnTop->second(val2, val1);
	data.push(val1);
}

double countFunction(string function, map<string, double> variables) {
	stack<double> data;
	data.push(0);
	stack<string> signs;

	while (function.size()) {
		double number;
		int pos = function.find(' ');
		string val = function.substr(0, pos);
		
		if (isdigit(val[0])) {
			data.push(stod(val));
		}

		if (val[0] == 'e') {
			data.push(exp(1));
		}

		auto itVar = variables.find(val);
		if (itVar != variables.end()){
			data.push(itVar->second);
		}

		auto itFunc = fcnPtr.find(val.substr(0, 3));
		if (itFunc != fcnPtr.end()) {
			pos = function.find(')');
			if (pos != string::npos) {
				double res = countFunction(function.substr(4, pos - 4), variables);
				data.push(itFunc->second(res));
			}
		}

		auto itOper = operations.find(val);
		if (itOper != operations.end()) {
			if (val == "+" || val == "-") {
				while (!signs.empty()) {
					makeOperationWithTwoTopNums(data, signs);
				}
			}

			if (val == "*" || val == "/") {
				if (!signs.empty() && (signs.top() == "*" || signs.top() == "/" || signs.top() == "^")) {
					makeOperationWithTwoTopNums(data, signs);
				}
				
			}

			signs.push(val);
		}

		if (val[0] == '(') {
			pos = function.find(')');
			if (pos != string::npos) {
				double res = countFunction(function.substr(1, pos - 1), variables);
				data.push(res);
			}
		}

		if (pos == string::npos) {
			val = function;
			function = "";
		}
		function.erase(0, pos + 1);
	}

	while (!signs.empty()) {
		makeOperationWithTwoTopNums(data, signs);
	}

	return data.top();
}

double countDerivative(string function, map<string, double> variables, string whichDerivative ) {

	double dVar = 1e-8;
	variables[whichDerivative] -= dVar;
	double resFunction = countFunction(function, variables);
	variables[whichDerivative] += 2 * dVar;
	return (countFunction(function, variables) - resFunction) / (2 * dVar);
}

double countSecondDerivative(string function, map<string, double> variables, string whichDerivative) {

	double dVar = 1e-8;
	variables[whichDerivative] -= dVar;
	double resFunction = countFunction(function, variables);
	variables[whichDerivative] += dVar;
	double doubleResFunction = 2 * countFunction(function, variables);
	variables[whichDerivative] += dVar;
	return (countFunction(function, variables) - doubleResFunction + resFunction) / (dVar*dVar);
}

class ProblemAnswer {
public:
	ProblemAnswer(vector<double> unknownVariables, int numOfIterations, vector<double> inaccuracy) {
		setUnknownVariables(unknownVariables);
		setNumOfIterations(numOfIterations);
		setInaccuracy(inaccuracy);
	}
	ProblemAnswer(int numOfIterations) {
		setNumOfIterations(numOfIterations);
	}
	void setUnknownVariables(vector<double> &unknownVariables) {
		this->unknownVariables = unknownVariables;
	}
	void setNumOfIterations(int numOfIterations) {
		this->numOfIterations = numOfIterations;
	}
	void setInaccuracy(vector<double> inaccuracy) {
		this->inaccuracy = inaccuracy;
	}
	vector<double> getUnknownVariables() {
		return unknownVariables;
	}
	int getNumOfIterations() {
		return numOfIterations;
	}
	vector<double> getInaccuracy() {
		return inaccuracy;
	}
	void printAnswer(int precision) {
		talkToUser("Number of Iterations:");
		cout << this->numOfIterations << "\n";
		talkToUser("UnknownVariables:");
		printRow(this->unknownVariables, precision);
		talkToUser("InaccuracyOfResult:");
		printRow(this->inaccuracy, precision);
	}
private:
	vector<double> unknownVariables;
	int numOfIterations;
	vector<double> inaccuracy;
};

int findMaxDegree(vector<pair<string, int>> const_Variables) {

	int maxDegree = -100000;
	int pos = 0;
	for (int i = 0; i < const_Variables.size(); ++i) {
		if (maxDegree < const_Variables[i].second) {
			maxDegree = const_Variables[i].second;
			pos = i;
		}
		
	}
	return pos;
}

void reduceTheDegree(vector<pair<string, int>> &const_Varialbes) {

	int pos = findMaxDegree(const_Varialbes);
	bool isMinus = false;
	if (const_Varialbes[pos].first.size() < 2) {
		const_Varialbes[pos].first += "1";
	}
	if (!isdigit(const_Varialbes[pos].first[0])) {
		if (const_Varialbes[pos].first[0] == '-') {
			isMinus = true;
		}
		const_Varialbes[pos].first.erase(0, 1);
	}
	

	for (int i = 0; i < const_Varialbes.size(); ++i) {
		if (i == pos) {
			continue;
		}
		if (const_Varialbes[i].first.size() < 2) {
			const_Varialbes[i].first += "1";
		}

		if (isMinus) {
			if (isdigit(const_Varialbes[i].first[0])) {
				const_Varialbes[i].first = "-" + const_Varialbes[i].first;
			}
			else {
				if (const_Varialbes[i].first[0] == '-') {
					const_Varialbes[i].first.erase(0, 1);
					const_Varialbes[i].first = "+" + const_Varialbes[i].first;
				}
				if (const_Varialbes[i].first[0] == '+') {
					const_Varialbes[i].first.erase(0, 1);
					const_Varialbes[i].first = "-" + const_Varialbes[i].first;
				}
			}
			
		}
		const_Varialbes[i].first += "/" + const_Varialbes[pos].first;
		const_Varialbes[i].second += 1 - const_Varialbes[pos].second;
	}

	const_Varialbes[pos].first = "0";
	const_Varialbes[pos].second = 0;
}

vector<pair<string, int>> reduceToConst_VariableLook(string function, string variable) {
	function.erase(remove_if(function.begin(), function.end(), isspace), function.end());
	vector<pair<string, int>> const_Variables;
	const_Variables.push_back({ "", 0 });
	for (int i = 0; i < function.size(); ++i) {
		if (function[i] == '+' || function[i] == '-') {
			if (function[i] == '-') {
				const_Variables.push_back({ "-", 0 });
			}
			else {
				const_Variables.push_back({ "+", 0 });
			}
			continue;
		}

		if (function[i] == variable[0]) {
			string num = "1";
			if (function[i + 1] == '^') {
				num = function.substr(i + 2, 1);
				i += 2;
			}
			if (i > 2 && function[i - 3] == '/') {
				const_Variables.back().second -= stoi(num);
			}
			else {
				const_Variables.back().second += stoi(num);
			}
			continue;
		}

		const_Variables[const_Variables.size() - 1].first += function[i];
	}

	return const_Variables;
}

string returnToNormalLook(vector<pair<string, int>> const_Variables, string variable) {

	string function = "";
	for (auto const_variable : const_Variables) {
		for (int i = 0; i < const_variable.first.size(); ++i) {
			if (operations.find(const_variable.first.substr(i, 1)) != operations.end()) {
				const_variable.first.insert(i + 1, " ");
				const_variable.first.insert(i, " ");
				i += 2;
			}
		}
		if (function != "") {
			function += " ";
		}

		if (const_variable.second < 0) {
			function += const_variable.first + " * " + variable + " ^ (- " + to_string(abs(const_variable.second)) + ")";
		}
		else {
			function += const_variable.first + " * " + variable + " ^ " + to_string(const_variable.second);
		}

	}

	return function;
}

void expressVariables(vector<string> &functions) {
	vector<string> nameOfVariables{ "x", "y", "z" };
	for (int i = 0; i < functions.size(); ++i) {
		vector<pair<string, int>> const_Variables = reduceToConst_VariableLook(functions[i], nameOfVariables[i]);
		reduceTheDegree(const_Variables);
		functions[i] = returnToNormalLook(const_Variables, nameOfVariables[i]);
	}
}

bool isOutOfBounds(map<string, double> prevStep, vector<pair<double, double>> bounds, vector<string> nameOfVariables) {
	for (int i = 0; i < prevStep.size(); ++i) {
		if (prevStep[nameOfVariables[i]] < bounds[i].first || prevStep[nameOfVariables[i]] > bounds[i].second) {
			return true;
		}
	}
	return false;
}

ProblemAnswer simpleIterationMethod(vector<string> functions, vector<pair<double, double>> bounds, vector<double> startPoints, int precision) {

	vector<string> nameOfVariables{ "x", "y", "z" };
	map<string, double> prevStep;
	map<string, double> currentStep;
	map<string, double> precisions;
	int size = bounds.size();
	for (int i = 0; i < size; ++i) {
		currentStep.insert({ nameOfVariables[i], startPoints[i]});
		prevStep.insert({ nameOfVariables[i], startPoints[i] });
		precisions.insert({ nameOfVariables[i], 0 });
	}

	double currentPrecision = 1;
	int iterations = 0;
	while (currentPrecision >= pow(0.1, precision)) {
		if (isOutOfBounds(currentStep, bounds, nameOfVariables)) {
			ProblemAnswer answer(0);
			return answer;
		}
		prevStep = currentStep;

		for (int i = 0; i < size; ++i) {
			currentStep[nameOfVariables[i]] = prevStep[nameOfVariables[i]] - countFunction(functions[i], prevStep);
		}

		double maxPrecision = 0;
		for (int i = 0; i < size; ++i) {
			precisions[nameOfVariables[i]] = abs(currentStep[nameOfVariables[i]] - prevStep[nameOfVariables[i]]);
			maxPrecision = max(maxPrecision, precisions[nameOfVariables[i]]);
		}

		currentPrecision = maxPrecision;
		++iterations;
	}

	vector<double> result;
	vector<double> prevResult;
	for (int i = 0; i < size; ++i) {
		result.push_back(currentStep[nameOfVariables[i]]);
		prevResult.push_back(prevStep[nameOfVariables[i]]);
	}
	vector<double> inaccuracy = countInaccuracyVector(result, prevResult, 0.07);

	ProblemAnswer answer(result, iterations, inaccuracy);
	return answer;
}

ProblemAnswer methodOfTheCurve(string equation, double leftBound, double rightBound, int precision) {
	double approximation = (leftBound + rightBound) / 2;
	double currentPrecision = 1, coef = 0, prevApproximation = 0;
	int iterations = 0;
	while (approximation <= rightBound && approximation >= leftBound && currentPrecision >= pow(0.1, precision)) {
		prevApproximation = approximation;
		coef = countFunction(equation, { {"x", approximation} }) / countDerivative(equation, { {"x", approximation} }, "x");
		approximation = prevApproximation - coef;
		currentPrecision = abs(approximation - prevApproximation);
		++iterations;
	}
	
	if (approximation < leftBound || approximation > rightBound) {
		ProblemAnswer answer(0);
		return answer;
	}

	vector<double> result{ approximation };
	vector<double> prevStep{ prevApproximation };
	ProblemAnswer answer({ approximation }, iterations, countInaccuracyVector(result, prevStep, coef));
	return answer;
}

bool isConvergeByMethodOfSimpleIterations(vector<pair<double,double>> boundsRes) {

	for (auto boundRes : boundsRes) {
		if (boundRes.first * boundRes.second > 0) return false;
	}
	
	return true;
}

bool isConvergeByMethodOfTheCurve(string function, double leftBound, double rightBound) {
	if (countFunction(function, { { "x", leftBound } }) * countFunction(function, { { "x", rightBound } }) >= 0) {
		return false;
	}

	if (countDerivative(function, { { "x", leftBound } }, "x") * countDerivative(function, { { "x", rightBound } }, "x") <= 0) {
		return false;
	}

	if (countSecondDerivative(function, { { "x", leftBound } }, "x") * countSecondDerivative(function, { { "x", rightBound } }, "x") <= 0) {
		return false;
	}
}

vector<pair<double, double>> countBoundsResults(vector<pair<double, double>> bounds, vector<string> functions) {
	vector<pair<double, double>> boundsRes;
	vector<string> nameOfVariables{ "x", "y", "z" };

	for (int i = 0; i < bounds.size(); ++i) {
		double leftRes = countDerivative(functions[i], { { nameOfVariables[i], bounds[i].first } }, nameOfVariables[i]);
		double rightRes = countDerivative(functions[i], { { nameOfVariables[i], bounds[i].second } }, nameOfVariables[i]);
		boundsRes.push_back({ leftRes, rightRes });
	}

	return boundsRes;
}

vector<double> countLambdas(vector<pair<double, double>> boundsRes, vector<pair<double, double>> bounds, vector<double> &startPoints) {
	vector<double> lambdas;

	for (int i = 0; i < boundsRes.size(); ++i) {
		if (abs(boundsRes[i].first) > abs(boundsRes[i].second)) {
			startPoints.push_back(bounds[i].first);
			lambdas.push_back(boundsRes[i].first);
		}
		else {
			startPoints.push_back(bounds[i].second);
			lambdas.push_back(boundsRes[i].second);
		}
	}

	return lambdas;
}

bool isLambdaEqualsZero(vector<double> lambdas) {
	for (auto lambda : lambdas) {
		if (lambda == 0) return true;
	}

	return false;
}

void solveEquation(string equation, int precision) {

	vector<string> functions{ equation };

	drawGraphic(functions);
	talkToUser("Enter boundary points");
	
	double leftBound, rightBound;
	inputBoundaryPoints(&leftBound, &rightBound);

	bool isConvergeByIterations = true, isConvergeByCurve= true;

	vector<pair<double, double>> boundsRes = countBoundsResults({ {leftBound, rightBound} }, functions);

	//vector<double> startPoints;

	if (isConvergeByIterations) {
		/*vector<double> lambdas = countLambdas(boundsRes, { {leftBound, rightBound} }, startPoints);
		if (isLambdaEqualsZero(lambdas)) {
			printError("No answer by method of the simple iterations");
			return;
		}
		*/
		ProblemAnswer answer = simpleIterationMethod({ functions[0] + " + x" }, { {leftBound, rightBound} }, { (rightBound + leftBound) / 2 }, precision);
		if (!answer.getNumOfIterations()) {
			printError("No answer by method of the simple iterations");
		}
		else {
			answer.printAnswer(precision + 2);
		}
	}

	if (isConvergeByCurve) {
		ProblemAnswer answer = methodOfTheCurve(equation, leftBound, rightBound, precision);
		if (!answer.getNumOfIterations()) {
			printError("No answer by method of the curve");
		}
		else {
			answer.printAnswer(precision + 2);
		}
	}

}

void solveSystemOfEquations(vector<string> functions, int precision) {

	drawGraphic(functions);

	vector<double> startPoints;
	vector<pair<double, double>> boundaryPoints(functions.size());
	vector<string> nameOfVariables{ "x", "y", "z" };
	for (int i = 0; i < functions.size(); ++i) {
		talkToUser("Enter boundary points for " + nameOfVariables[i]);
		inputBoundaryPoints(&boundaryPoints[i].first, &boundaryPoints[i].second);
		startPoints.push_back((boundaryPoints[i].second + boundaryPoints[i].first) / 2);
	}

	ofstream fout;
	fout.open("../../Variables.txt");
	fout << precision << endl;
	for (auto boundaryPoint : boundaryPoints) {
		fout << boundaryPoint.first << " " << boundaryPoint.second << endl;
	}
	for (auto function : functions) {
		fout << function << endl;
	}
	fout.close();
	system("python ../../Lab2Python/solve_systems.py");

}

int main()
{
	initFcnPtr();
	initOperations();

	char inputFrom = ' ';
	while (inputFrom != 'k' && inputFrom != 'f') {
		talkToUser("Enter what way to use to read data(k - for console, f - for file)");
		cin >> inputFrom;
	}

	char inputWhat = ' ';
	while (inputWhat != 'e' && inputWhat != 's'){
		talkToUser("What do we solve (e - for equation, s - for system of the equations)");
		cin >> inputWhat;
	}

	string nameOfFile;
	ifstream in;
	if (inputFrom == 'f') {
		readNameOfFile(&nameOfFile);
	}
	

	int precision = 0;
	vector<vector<double>> matrix;
	if (inputFrom == 'k') {
		inputFromConsolePrecision(matrix, &precision);
	}
	else {
		in.open(nameOfFile);
		inputFromFilePrecision(matrix, &precision, in);
	}

	int numOfTask = 0;
	inputFromConsoleEquation(&numOfTask, inputWhat);

	vector<string> equations(5);
	equations[0] = "x ^ 2 - e ^ (- x)";
	equations[1] = "x ^ 3 - x + 1";
	equations[2] = "x ^ 2 + 9 * x + 9";
	equations[3] = "2 * x - sin(x)";
	equations[4] = "x ^ 3 - 0.2 * x ^ 2 + 0.5 * x + 1.5";

	vector<vector<string>> systems(3);
	systems[0].push_back("3 * x - y - 0.9");
	systems[0].push_back("sin(x - 0.6) - y - 1.6");
	

	if (inputWhat == 'e'){
		solveEquation(equations[numOfTask], precision);
	}
	else {
		solveSystemOfEquations(systems[numOfTask], precision);
	}
}