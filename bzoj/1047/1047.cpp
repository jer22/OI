#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

const int MAXN = 1005;

int n, m, k;
int arr[MAXN][MAXN];
int milef[MAXN][MAXN], mxlef[MAXN][MAXN], mi[MAXN][MAXN], mx[MAXN][MAXN];

pii q1[MAXN], q2[MAXN];
int tail1 = 0, tail2 = 0, head1 = 1, head2 = 1;
// bool inq1[MAXN], inq2[MAXN];
void callef(int i) {
	int l = 1;
	tail1 = 0, tail2 = 0, head1 = 1, head2 = 1;
	for (int j = 1; j <= m; j++) {
		while (tail1 >= head1 && q1[tail1].first <= arr[i][j])
			tail1--;
		q1[++tail1] = mp(arr[i][j], j);

		while (tail2 >= head2 && q2[tail2].first >= arr[i][j])
			tail2--;
		q2[++tail2] = mp(arr[i][j], j);
		if (l + k == j) {
			if (q1[head1].second == l)
				head1++;
			if (q2[head2].second == l)
				head2++;
			l++;
		}
		mxlef[i][j] = q1[head1].first;
		milef[i][j] = q2[head2].first;
	}
}

void calup(int j) {
	int l = 1;
	tail1 = 0, tail2 = 0, head1 = 1, head2 = 1;
	for (int i = 1; i <= n; i++) {
		while (tail1 >= head1 && q1[tail1].first <= mxlef[i][j])
			tail1--;
		q1[++tail1] = mp(mxlef[i][j], i);

		while (tail2 >= head2 && q2[tail2].first >= milef[i][j])
			tail2--;
		q2[++tail2] = mp(milef[i][j], i);
		if (l + k == i) {
			if (q1[head1].second == l)
				head1++;
			if (q2[head2].second == l)
				head2++;
			l++;
		}
		mx[i][j] = q1[head1].first;
		mi[i][j] = q2[head2].first;
	}
}

int main() {
	freopen("1047.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &arr[i][j]);
	for (int i = 1; i <= n; i++)
		callef(i);
	for (int j = 1; j <= m; j++)
		calup(j);
	int ans = 0x3f3f3f3f;
	for (int i = k; i <= n; i++)
		for (int j = k; j <= m; j++)
			ans = min(mx[i][j] - mi[i][j], ans);

	printf("%d\n", ans);
	return 0;
}
