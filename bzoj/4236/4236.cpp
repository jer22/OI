#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

const int MAXN = 200005;

int n;
char str[MAXN];
map<pii, int> ss;
int sum[MAXN][3];
int main() {
	freopen("4236.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", str + 1);
	int ans = 0;
	ss[mp(0, 0)] = 0;
	for (int i = 1; i <= n; i++) {
		sum[i][0] = sum[i - 1][0];
		sum[i][1] = sum[i - 1][1];
		sum[i][2] = sum[i - 1][2];
		if (str[i] == 'J') sum[i][0]++;
		if (str[i] == 'O') sum[i][1]++;
		if (str[i] == 'I') sum[i][2]++;
		pii p = mp(sum[i][0] - sum[i][1], sum[i][1] - sum[i][2]);
		if (ss.find(p) == ss.end())
			ss[p] = i;
		else ans = max(ans, i - ss[p]);
	}
	cout << ans << endl;


	return 0;
}
