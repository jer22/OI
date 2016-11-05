#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

const int MAXN = 105;

int n;
pii arr[MAXN];
int ans[10005][105];
bool end() {
	for (int i = 1; i < n; i++)
		if (arr[i].first != arr[i + 1].first) return false;
	return true;
}

bool cmp(pii a, pii b) {
	return a.first > b.first;
}

int main() {
	// freopen("a.in", "r", stdin);
	cin >> n;
	int tot = 0;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].first;
		arr[i].second = i;
	}
	while (!end()) {
		sort(arr + 1, arr + n + 1, cmp);
		int num = 2;
		while (num < n && arr[num + 1].first == arr[1].first) num++;
		if (num & 1) {
			ans[++tot][arr[1].second] = ans[tot][arr[2].second] = ans[tot][arr[3].second] = 1;
			arr[1].first = max(arr[1].first - 1, 0);
			arr[2].first = max(arr[2].first - 1, 0);
			arr[3].first = max(arr[3].first - 1, 0);
			for (int i = 4; i <= num; i += 2) {
				ans[++tot][arr[i].second] = ans[tot][arr[i + 1].second] = 1;	
				arr[i].first = max(arr[i].first - 1, 0);
				arr[i + 1].first = max(arr[i + 1].first - 1, 0);
			}
		} else {
			for (int i = 1; i <= num; i += 2) {
				ans[++tot][arr[i].second] = ans[tot][arr[i + 1].second] = 1;
				arr[i].first = max(arr[i].first - 1, 0);
				arr[i + 1].first = max(arr[i + 1].first - 1, 0);
			}
		}
	}
	cout << arr[1].first << endl;
	cout << tot << endl;
	for (int i = 1; i <= tot; i++) {
		for (int j = 1; j <= n; j++)
			cout << ans[i][j];
		cout << endl;
	}
	return 0;
}
