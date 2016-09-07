#include <bits/stdc++.h>

using namespace std;

long long a, b, c, d;
map<long long, long long> vis;

void init() {
	long long now = 1;
	for (int i = 2; i <= 1000000; i++) {
		vis[now] = i;
		now += i;
		if (now > 1000000000) break;
	}
}

char s[1000005];
int main() {
	freopen("d.in", "r", stdin);
	cin >> a >> b >> c >> d;
	init();
	if ((a && !vis[a]) || (d && !vis[d])) {
		printf("Impossible\n");
		return 0;
	}
	long long n0 = vis[a];
	long long n1 = vis[d];
	long long tot = n0 * n1;
	if (!n1 && !n0) {
		if (!b && !c) cout << '1' << endl;
		else if (b == 1 && c == 0) cout << "01" << endl;
		else if (b == 0 && c == 1) cout << "10" << endl;
		else cout << "Impossible" << endl;
		
		return 0;
	}
	if (n1 + n0 > 1000000) {
		printf("Impossible\n");
		return 0;
	}
	if (b == tot - c) {
		if (!n1) {
			for (int i = 0; i < n0; i++)
				cout << '0';
			cout << endl;
			return 0;
		}
		int e = b / n1, f = b % n1;
		for (int i = 0; i < e; i++)
			cout << '0';
		for (int i = 0; i < n1 - f; i++)
			cout << '1';
		if (e - f < n0)
			cout << '0';
		for (int i = 0; i < f; i++)
			cout << '1';
		for (int i = 0; i < n0 - 1 - e; i++)
			cout << '0';
		cout << endl;

	} else {
		if (!n1) n1 = 1;
		if (!n0) n0 = 1;
		tot = n0 * n1;
		if (b == tot - c) {
			int e = b / n1, f = b % n1;
			for (int i = 0; i < e; i++)
				cout << '0';
			for (int i = 0; i < n1 - f; i++)
				cout << '1';
			if (e - f < n0)
				cout << '0';
			for (int i = 0; i < f; i++)
				cout << '1';
			for (int i = 0; i < n0 - 1 - e; i++)
				cout << '0';
			cout << endl;

		} else {
			cout << "Impossible" << endl;
		}
	}



	return 0;
}
