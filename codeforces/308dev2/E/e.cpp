#include <bits/stdc++.h>

using namespace std;

int n;
string str;
vector<int> pos;
stack<char> sc;
stack<long long> sn;

long long twoResult(long long a, long long b, char c) {
	return (c == '*') ? a * b : a + b;
}

void cal() {
	char t = sc.top();
	sc.pop();
	long long a = sn.top();
	sn.pop();
	long long b = sn.top();
	sn.pop();
	sn.push(twoResult(a, b, t));
}

long long expression(string s) {
	for (int i = 0; i < s.length(); i++) {
		char c = s[i];
		if (isdigit(c)) {
			sn.push(c - '0');
		} else if (c == '(') {
			sc.push(c);
		} else if (c == ')') {
			while (sc.top() != '(')
				cal();
			sc.pop();
		} else {
			if (c == '+') {
				while (!sc.empty() && sc.top() == '*')
					cal();
				sc.push(c);
			} else sc.push(c);
		}
	}
	while (!sc.empty()) cal();
	return sn.top();
}

int main() {
	cin >> str;
	n = str.size();
	pos.push_back(-1);
	for (int i = 1; i < n; i += 2)
		if (str[i] == '*') pos.push_back(i);
	pos.push_back(n);
	int len = pos.size();
	long long ans = 0;
	for (int i = 0; i < len - 1; i++) { // left
		for (int j = i + 1; j < len; j++) { // right
			string s = str;
			s.insert(pos[i] + 1, 1, '(');
			s.insert(pos[j] + 1, 1, ')');
			ans = max(ans, expression(s));
		}
	}
	cout << ans << endl;
	return 0;
}
