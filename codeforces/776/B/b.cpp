#include <bits/stdc++.h>

using namespace std;

int n;
bool vis[100005];
int main() {
	freopen("b.in", "r", stdin);
	cin >> n;
	for (int i = 2; i <= 100001; i++) {
		if (vis[i]) continue;
		for (int j = i + i; j <= 100001; j += i)
			vis[j] = 1;
	}
	if (n == 1) {
		cout << 1 << endl << 1 << endl;
		return 0;
	}
	if (n == 2) {
		cout << 1 << endl << "1 1" << endl;
		return 0;
	}
	cout << 2 << endl;
	for (int i = 2; i <= n + 1; i++) {
		cout << vis[i] + 1 << " \n"[i == n + 1];
	}

	return 0;
}
