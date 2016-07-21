#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;

int n;
char s[200005];
int p[200005];
int main() {
	// freopen("a.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", s);
	for (int i = 0; i < n; i++)
		scanf("%d", &p[i]);
	int ans = INF;
	for (int i = 1; i < n; i++) {
		if (s[i - 1] == 'R' && s[i] == 'L') {
			ans = min(ans, p[i] - p[i - 1]);
		}
	}
	if (ans == INF) cout << -1 << endl;
	else cout << ans / 2 << endl;


	return 0;
}
