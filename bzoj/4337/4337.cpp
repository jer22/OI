#include <bits/stdc++.h>

using namespace std;

int m;
vector<int> edges[55][55];
int ns[55];
long long has[55];

long long geth(vector<long long> v) {
	long long ans = '(';
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++)
		ans = ans * 23 + v[i];
	return ans * 23 + ')';
}

long long getHash(int tr, int x, int pre) {
	long long ans = '(';
	vector<long long> v;
	for (int i = 0; i < edges[tr][x].size(); i++) {
		int nex = edges[tr][x][i];
		if (nex == pre) continue;
		v.push_back(getHash(tr, nex, x));
	}
	return geth(v);
}

int main() {
	freopen("4337.in", "r", stdin);
	scanf("%d", &m);
	int a;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &ns[i]);
		for (int j = 1; j <= ns[i]; j++) {
			scanf("%d", &a);
			if (a) {
				edges[i][a].push_back(j);
				edges[i][j].push_back(a);
			}
		}
		vector<long long> v;
		for (int j = 1; j <= ns[i]; j++)
			v.push_back(getHash(i, j, 0));
		has[i] = geth(v);
	}
	for (int i = 1; i <= m; i++) {
		int ans = i;
		for (int j = 1; j < i; j++) {
			if (ns[i] != ns[j]) continue;
			if (has[i] == has[j]) {
				ans = j;
				break;
			}
		}
		printf("%d\n", ans);
	}


	return 0;
}
