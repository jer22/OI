#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int n;
string s;
int cnt[4];
int m[128];
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n >> s;
	m['A'] = 0, m['C'] = 1, m['G'] = 2, m['T'] = 3;
	for (int i = 0; i < n; i++)
		cnt[m[s[i]]]++;
	sort(cnt, cnt + 4);
	long long base = 1;
	base += (cnt[3] == cnt[2]) + (cnt[3] == cnt[1]) + (cnt[3] == cnt[0]);
	long long ans = 1ll;
	for (int i = 0; i < n; i++) ans = ans * base % MOD;
	cout << ans << endl;


	return 0;
}
