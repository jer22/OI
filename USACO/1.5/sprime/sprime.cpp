/*
ID:shijiey1
PROG:sprime
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

int n;
priority_queue<int, vector<int>, greater<int> > q;

bool isPrime(int a) {
	if (a == 1 || !a) return false;
	bool flag = false;
	for (int i = 2; i <= sqrt(a); i++) {
		if (!(a % i)) {
			flag = true;
			break;
		}
	}
	return !flag;
}

void dfs(int step, int cur) {
	if (step == n) {
		q.push(cur);
		return;
	}
	int t;
	for (int i = 1; i <= 9; i++) {
		t = cur * 10 + i;
		if (isPrime(t)) {
			dfs(step + 1, t);
		}
	}
}

int main() {
	freopen("sprime.in", "r", stdin);
	freopen("sprime.out", "w", stdout);
	scanf("%d", &n);
	dfs(0, 0);
	while (!q.empty()) {
		printf("%d\n", q.top());
		q.pop();
	}
	return 0;
}
