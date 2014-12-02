/*
ID:shijiey1
PROG:lamps
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int n, c;
int start[8];
int on[8];
int off[8];
int isOn;
int isOff = 63;;
set<string> ans;

bool ok(int state) {
	return (state & isOn) == isOn && (state | isOff) == isOff;
}

void add(int state) {
	string s = "";
	for (int i = 0; i < min(n, 6); i++) {
		char c = ((state & 1) + '0');
		s = s + c;
		state >>= 1;
	}
	ans.insert(s);
}

void addState(int state) { if (ok(state)) add(state); }

void print() {
	set<string> :: iterator it;
	for (it = ans.begin(); it != ans.end(); it++) {
		for (int i = 0; i < n; i++) {
			printf("%c", (*it)[i % 6]);
		}
		printf("\n");
	}
}

void solve() {
	int bit = 63;
	for (int i = 0; i < 6; i++) {
		if (on[i] == 1) {
			isOn = isOn | (1 << i);
		} else if (!off[i]) {
			
			isOff = isOff ^ (1 << i);
		}
	}
	addState(bit);
	if (c) {
		addState(bit ^ 63);
		addState(bit ^ 21);
		addState(bit ^ 42);
		if (c == 1) {
			addState(bit ^ 9);	
		} else if (c == 2) {
			addState((bit ^ 63) ^ 9);
			addState((bit ^ 21) ^ 9);
			addState((bit ^ 42) ^ 9);
		} else {
			addState(bit ^ 9);
			addState((bit ^ 63) ^ 9);
			addState((bit ^ 21) ^ 9);
			addState((bit ^ 42) ^ 9);
		}
	}
	if (!ans.size()) {
		printf("IMPOSSIBLE\n");
		return;
	}
	print();
}

int main() {
	freopen("lamps.in", "r", stdin);
	freopen("lamps.out", "w", stdout);
	scanf("%d %d", &n, &c);
	int t;
	while (~scanf("%d", &t)) {
		if (t == -1) break;
		on[(t - 1) % 6] = 1;
	}
	for (int i = 0; i < 6; i++) off[i] = 1;
	while (~scanf("%d", &t)) {
		if (t == -1) break;
		if (on[(t - 1) % 6] == 1) {
			printf("IMPOSSIBLE\n");
			return 0;
		}
		off[(t - 1) % 6] = 0;
	}
	while (c > 4) c -= 2;
	solve();

	return 0;
}
