/*
ID:shijiey1
PROG:gift1
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>

using namespace std;

int np;
string name[12];
map<string, int> m;
int main() {
	freopen("gift1.in", "r", stdin);
	freopen("gift1.out", "w", stdout);
	scanf("%d", &np);
	for (int i = 0; i < np; i++) {
		cin >> name[i];
	}
	string now;
	while (cin >> now) {
		int tot, num;
		scanf("%d %d", &tot, &num);
		if (!num) {
			continue;
		}
		int money = tot / num;
		string s;
		for (int i = 0; i < num; i++) {
			cin >> s;
			m[s] += money;
		}
		m[now] -= num * money;
	}
	for (int i = 0; i < np; i++) {
		cout << name[i] << ' ' << m[name[i]] << endl;
	}
	return 0;
}
