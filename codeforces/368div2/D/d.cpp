#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, q;
int que[MAXN][3];

int arr[1005][1005];
bool rev[1005];
int cnt[1005];
int num = 0;
int pre[MAXN];
bool vali[MAXN];

int tot = 1;

bool ins(int i, int j) {
	if (!(arr[i][j] ^ rev[i])) {
		arr[i][j] ^= 1;
		num++;
		cnt[i]++;
		return true;
	}
	return false;
}
bool del(int i, int j) {
	if (arr[i][j] ^ rev[i]) {
		arr[i][j] ^= 1;
		num--;
		cnt[i]--;
		return true;
	}
	return false;
}
bool rever(int i) {
	rev[i] ^= 1;
	num += m - cnt[i] * 2;
	cnt[i] = m - cnt[i];
	return true;
}

int ans[MAXN];
vector<int> edges[MAXN];

void dfs(int x, int pre) {
	if (que[x][0] == 1) vali[x] = ins(que[x][1], que[x][2]);
	else if (que[x][0] == 2) vali[x] = del(que[x][1], que[x][2]);
	else if (que[x][0] == 3) vali[x] = rever(que[x][1]);
	ans[x] = num;
	// if (x == 6) cout << que[x][0] << endl;
	for (int i = 0; i < edges[x].size(); i++)
		if (edges[x][i] != pre) dfs(edges[x][i], x);
	if (vali[x]) {
		if (que[x][0] == 1) del(que[x][1], que[x][2]);
		else if (que[x][0] == 2) ins(que[x][1], que[x][2]);
		else if (que[x][0] == 3) rever(que[x][1]);
	}
}

int main() {
	freopen("d.in", "r", stdin);
	cin >> n >> m >> q;
	for (int i = 1; i <= q; i++) {
		cin >> que[i][0];
		if (que[i][0] < 3) cin >> que[i][1] >> que[i][2];
		else cin >> que[i][1];
		if (que[i][0] == 4) {
			edges[i].push_back(que[i][1]);
			edges[que[i][1]].push_back(i);
		} else {
			edges[i].push_back(i - 1);
			edges[i - 1].push_back(i);
		}
	}
	dfs(0, 0);
	for (int i = 1; i <= q; i++)
		cout << ans[i] << endl;


	return 0;
}
