#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int cas, n;
int arr[44][44];
int vis[44];
vector<int> ans, pre;
vector<vector<int> > final;
void dfs(int step, int now) {
	if (step == n) {
		if ((!arr[now][ans[0]]) && (!arr[ans[0]][now])) {
			pre.clear();
			pre.push_back(1);
			for (int i = n - 1; i >= 1; i--) {
				pre.push_back(ans[i]);
			}
			for (int i = 1; i < n; i++) {
				if (ans[i] > pre[i]) return;
				else if (ans[i] < pre[i]) break;
			}
			final.push_back(ans);
		}
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (i == now || arr[now][i] || arr[i][now] || vis[i]) continue;
		ans.push_back(i);
		vis[i] = 1;
		dfs(step + 1, i);
		vis[i] = 0;
		ans.pop_back();
	}
}

int main() {
	freopen("apec.in", "r", stdin);
	while (~scanf("%d", &cas) && cas) {
		cin >> n;
		ans.clear();
		final.clear();
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> arr[i][j];
			}
		}
		ans.push_back(1);
		vis[1] = 1;
		dfs(1, 1);
		cout << cas << ' ' << final.size() << endl;
		for (int i = 0; i < final.size(); i++) {
			for (int j = 0; j < n; j++) {
				if (j) cout << ' ';
				cout << final[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}


	return 0;
}
