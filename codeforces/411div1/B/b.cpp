#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1000000007ll;

string s;
int main() {
	freopen("b.in", "r", stdin);
	cin >> s;
	int len = s.size();
	long long ans = 0;
	long long num = 0;
	for (int i = len - 1; i >= 0; i--) {
		if (s[i] == 'a') {
			(ans += num) %= MOD;
			(num *= 2) %= MOD;
		} else (num += 1) %= MOD;
	}


	cout << ans << endl;

	return 0;
}
