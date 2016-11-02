#include <bits/stdc++.h>

#define pll pair<long long, long long>
#define pli pair<long long, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

const int MAXN = 100005;

int n;
long long arr[MAXN][3];
map<pll, pli> height;

void update(long long x, long long y, long long z, int id) {
	if (height.find(mp(x, y)) == height.end())
		height[mp(x, y)] = mp(z, id);
	else height[mp(x, y)] = max(height[mp(x, y)], mp(z, id));
}

int main() {
	// freopen("d.in", "r", stdin);
	cin >> n;
	int idx1 = 0, idx2[2] = {0, 0};
	long long best1 = 0, best2 = 0;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
		sort(arr[i], arr[i] + 3);
		if (arr[i][0] > best1) {
			best1 = arr[i][0];
			idx1 = i;
		}
		if (height.find(mp(arr[i][1], arr[i][2])) != height.end()) {
			long long t = min(arr[i][0] + height[mp(arr[i][1], arr[i][2])].first, min(arr[i][1], arr[i][2]));
			if (t > best2) {
				idx2[0] = i;
				idx2[1] = height[mp(arr[i][1], arr[i][2])].second;
				best2 = t;
			}
		}
		update(arr[i][0], arr[i][1], arr[i][2], i);
		update(arr[i][0], arr[i][2], arr[i][1], i);
		update(arr[i][1], arr[i][2], arr[i][0], i);
	}
	if (best1 > best2)
		cout << 1 << endl << idx1 << endl;
	else cout << 2 << endl << idx2[0] << ' ' << idx2[1] << endl;
	return 0;
}
