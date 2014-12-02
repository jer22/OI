#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

int isOperator_char(char op) {
	return (op == '+' || op == '-'
		|| op == '*' || op == '/'
		|| op == '%' || op == '(' || op == ')');
}

int isOperator_string(string op) {
	return (op == "+" || op == "-"
		|| op == "*" || op == "/"
		|| op == "%" || op == "(" || op == ")");
}

int priority(string op) {
	if (op == "+" || op == "-")
		return 1;
	else if (op == "*" || op == "%" || op == "/")
		return 2;
	else return 0;
}

string twoResult(string op, string a, string b) {
	string re;
	int x = atoi(b.c_str());
	int y = atoi(a.c_str());
	int z = 0;

	if (op == "+")
		z = x + y;
	else if (op == "-")
		z = x - y;
	else if (op == "*")
		z = x * y;
	else if (op == "/")
		z = x / y;
	else if (op == "%")
		z = x % y;
	stringstream ss;
	ss << z;
	ss >> re;
	return re;
}

vector<string> toRight(string input) {
	vector<string> expression;
	vector<string> right;

	int size = input.size();
	for (int i = 0; i < size; i++) {
		if (isOperator_char(input.at(i))) {
			string s;
			s.assign(input, i, 1);
			expression.push_back(s);
		}
		else {
			int temp = 0, j;
			for (j = i; j < size; j++) {
				if (!isOperator_char(input.at(j)))
					temp++;
				else
					break;
			}
			string s;
			s.assign(input, i, temp);
			i = j - 1;
			expression.push_back(s);
		}
	}

	stack<string> temp;
	string op;
	for (int position = 0; position < expression.size(); position++) {
		string element = expression[position];
		if (isOperator_string(element)) {
			
			if (temp.empty() || element == "(") {
				temp.push(element);
			} else if (element == ")") {
				while(true) {

					if (!temp.empty() && !(temp.top() == "(")) {
						op = temp.top();
						temp.pop();
						right.push_back(op);
					} else {
						if (!temp.empty())
							temp.pop();
						break;
					}
				}
			} else {
				while (!temp.empty() && 
					priority(element) <= priority(temp.top())) {

					op = temp.top();
					temp.pop();
					if (op != "(") {
						right.push_back(op);
					}
				}
				temp.push(element);
			}
		} else {
			right.push_back(element);
		}
	}
	while(!temp.empty()) {
		op = temp.top();
		temp.pop();
		if (op != "(")
			right.push_back(op);
	}

	return right;
}

string getResult(vector<string> right) {
	stack<string> s;
	string op1, op2, is;
	vector<string>::iterator it = right.begin();
	while(it != right.end()) {
		is = *it;
		if (isOperator_string(is)) {
			op1 = s.top();
			s.pop();
			op2 = s.top();
			s.pop();
			s.push(twoResult(is, op1, op2));
		} else {
			s.push(is);
		}
		it++;
	}
	return s.top();
}

string getResult(string expression) {
	return getResult(toRight(expression));
}

int main( void ) {
	char input[255];
	scanf("%s", &input);
	string s(input);
	vector<string> ss = toRight(s);
	printf("\n%s", getResult(s).c_str());
	
	system("pause");
	return 0;
}
