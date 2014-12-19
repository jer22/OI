#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

string origin;
int n;
long long ans[22];
long long a[22];

int getPriority(char c) {
	if (c == '+' || c == '-') return 1;
	if (c == '*') return 2;
	if (c == '^') return 3;
	return 0;
}

stack<char> op;
stack<long long> num;

long long power(long long a, long long b) {
	long long ans = 1;
	for (int i = 0; i < b; i++) {
		ans *= a;
	}
	return ans;
}

long long getResult(long long a, long long b, char op) {
	if (op == '+') return a + b;
	if (op == '-') return a - b;
	if (op == '*') return a * b;
	if (op == '^') return power(a, b);
}
void calc() {
	char oper = op.top();
	op.pop();
	long long a = num.top();
	num.pop();
	long long b = num.top();
	num.pop();
	long long res = getResult(b, a, oper);
	num.push(res);
}

long long getAns(long long a, string expression) {

	while (!op.empty()) op.pop();
	while (!num.empty()) num.pop();
	int siz = expression.size();
	for (int i = 0; i < siz; i++) {
		// if (!op.empty()) cout << op.size() << ' ';
		// if (!num.empty()) cout << num.size() << endl;
		char c = expression[i];
		if (c == 'a') num.push(a);
		else if (c >= '0' && c <= '9') {
			int t = c - '0';
			while (i < siz - 1 && expression[i + 1] >= '0' && expression[i + 1] <= '9') {
				t *= 10;
				t += expression[i + 1] - '0';
				i++;
			}
			num.push(t);
		}
		else {
			if (c == '(') op.push(c);
			else if (c == ')') {
				while (true) {
					if ((!op.empty()) && (op.top() != '(')) {
						calc();
					} else {
						if (!op.empty()) op.pop();
						break;
					}
				}
			} else {
				while ((!op.empty()) && getPriority(c) <= getPriority(op.top())) {
					calc();
				}
				op.push(c);
			}
		}
	}
	while (!op.empty()) calc();
	return num.top();
}

bool nice(string expression) {
	for (int i = 0; i < 20; i++) {
		long long now = getAns(a[i], expression);
		if (ans[i] != now) return false;
	}
	return true;
}

string expr[33];
int main() {
	freopen("1054.in", "r", stdin);
	string str;
	getline(cin, str);
	int siz = str.size();
	origin = "";
	for (int i = 0; i < siz; i++) {
		if (str[i] == ' ') continue;
		origin += str[i];
	}
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		expr[i] = "";
		getline(cin, str);
		int siz = str.size();
		int deep = 0;
		for (int j = 0; j < siz; j++) {
			if (str[j] == ' ') continue;
			if (str[j] == '(') deep++;
			if (str[j] == ')')
			{
				if (deep==0) continue;
				deep--;
			}
			expr[i] += str[j];
		}
		while (deep>0) {expr[i] += ')'; deep--;}
	}
	for (int i = 0; i < 20; i++) {
		int r = rand() % 97 + 1;
		a[i] = r;
		long long ori = getAns(r, origin);
		ans[i] = ori;
	}
	for (int i = 0; i < n; i++) {
		
		if (nice(expr[i])) {
			printf("%c", 'A' + i);
		}
	}
	printf("\n");

	return 0;
}
