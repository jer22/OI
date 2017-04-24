#include <bits/stdc++.h>

using namespace std;

int arr[12][6];
int now[12];
map<long long, double> vis;

double dfs(int dep) {
	if (dep == 19) return 1.;
	int cnt[12];
	vector<int> pos[12];
	long long stat = 0;
	for (int i = 1; i <= 9; i++) {
		cnt[i] = 0;
		pos[i].clear();
		stat += now[i] << ((i - 1) * 3ll);
	}
	if (vis.find(stat) != vis.end()) return vis[stat];
	int tot = 0;
	for (int i = 1; i <= 9; i++) {
		if (now[i] == 5) continue;
		tot += cnt[arr[i][now[i]]];
		// if (dep == 1 && arr[i][now[i]] == 7) cout << i << endl;
		pos[arr[i][now[i]]].push_back(i);
		++cnt[arr[i][now[i]]];
	}
	if (!tot) return 0;
	double ans = 0;
	for (int i = 1; i <= 9; i++) {
		int siz = pos[i].size();
		// if (dep == 1) cout << siz << endl;
		for (int j = 0; j < siz; j++) {
			for (int k = j + 1; k < siz; k++) {
				// if (dep == 1) cout << pos[i][j] << ' ' << pos[i][k] << endl;
				++now[pos[i][j]];
				++now[pos[i][k]];
				double p = dfs(dep + 1);
				ans += p / (double)tot;
				--now[pos[i][j]];
				--now[pos[i][k]];
			}
		}
	}
	vis.insert({stat, ans});
	return ans;
}

int main() {
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
	char op[5];
	for (int i = 1; i <= 9; i++) {
		now[i] = 1;
		for (int j = 1; j <= 4; j++) {
			scanf("%s", op);
			if (op[0] >= '6' && op[0] <= '9')
				arr[i][5 - j] = op[0] - '5';
			else if (op[0] == 'T') arr[i][5 - j] = 5;
			else if (op[0] == 'J') arr[i][5 - j] = 6;
			else if (op[0] == 'Q') arr[i][5 - j] = 7;
			else if (op[0] == 'K') arr[i][5 - j] = 8;
			else if (op[0] == 'A') arr[i][5 - j] = 9;
		}
	}
	printf("%.6lf\n", dfs(1));

	return 0;
}