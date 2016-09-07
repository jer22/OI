#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
long long a;
long long cor[MAXN];
bool vis[MAXN];



int main() {
	freopen("b.in", "r", stdin);
	cin >> n >> a;
	for (int i = 1; i <= n; i++)
		cin >> cor[i];
	sort(cor + 1, cor + n + 1);
	if (n == 1) {
		cout << 0 << endl;
		return 0;
	}
	long long ans = min(min(abs(a - cor[1]) + cor[n - 1] - cor[1], abs(cor[n - 1] - a) + cor[n - 1] - cor[1])
		, min(abs(a - cor[2]) + cor[n] - cor[2], abs(cor[n] - a) + cor[n] - cor[2]));
	cout << ans << endl;



	return 0;
}
