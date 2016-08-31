#include <bits/stdc++.h>

using namespace std;

int n;
char s[300005];
double f[300005], d[300005];
int main() {
	freopen("3450.in", "r", stdin);
	cin >> n;
	cin >> s + 1;
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'o') {
			f[i] = f[i - 1] + 2.0 * d[i - 1] + 1.0;
			d[i] = d[i - 1] + 1;
		} else if (s[i] == 'x') {
			f[i] = f[i - 1];
			d[i] = 0;
		} else {
			f[i] = f[i - 1] + d[i - 1] + 0.5;
			d[i] = (d[i - 1] + 1) * 0.5;
		}
	}
	printf("%.4lf\n", f[n]);

	return 0;
}
