#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int T;
int n;
bool arr[20005];
map<string, int> vis;
string str[20005];

int gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}

int main() {
	freopen("1002.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		string s;
		int a = 0, b = 0;
		int ans = 0;
		vis.clear();
		for (int i = 0; i < n; i++) {
			cin >> s;
			vis[s]++;
			str[i] = s;
			int len = s.size();
			if (len & 1) a++;
			else b++;
			arr[i] = len & 1;
		}
		for (int i = 0; i < n; i++) {
			if (arr[i]) ans += b;
			else {
				ans += a;
			}
			ans += vis[str[i]] - 1;
		}
		int bb = n * (n - 1);
		if (ans == bb) {
			cout << "1/1" << endl;
		} else if (!ans) {
			cout << "0/1" << endl;
		} else {
			int k = gcd(ans, bb);
			ans /= k;
			bb /= k;
			printf("%d/%d\n", ans, bb);
		}
		for (int i = 1; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int a = str[i].size();
			}
		}
	}

	return 0;
}
