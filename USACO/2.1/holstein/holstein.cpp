/*
ID:shijiey1
PROG:holstein
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct Ans{
	int cnt;
	int arr[30];
	Ans() {
		cnt = 0;
		memset(arr, 0, sizeof(arr));
	}
	bool operator < (const Ans &a) const {
		if (cnt != a.cnt) return cnt < a.cnt;
		for (int i = 0; i < cnt; i++) {
			if (arr[i] != a.arr[i]) {
				return arr[i] < a.arr[i];
			}
		}
		return 1;
	}
};

int n, m;
int arr[30];
int feed[30][30];
int ans[30];
vector<Ans> re;
void success(int bit) {
	for (int i = 0; i < n; i++) {
		if (ans[i] < arr[i]) {
			return;
		}
	}
	Ans a = Ans();
	int step = 1;
	while (bit) {
		if (bit & 1) {
			a.arr[a.cnt++] = step;
		}
		bit >>= 1;
		step++;
	}
	re.push_back(a);
}

void solve() {
	for (int bit = 1; bit < (1 << m); bit++) {
		int t = bit;
		int step = 0;
		memset(ans, 0, sizeof(ans));
		while (t) {
			if (t & 1) {
				for (int i = 0; i < n; i++) {
					ans[i] += feed[step][i];
				}
			}
			t >>= 1;
			step++;
		}
		success(bit);
	}
}

int main() {
	freopen("holstein.in", "r", stdin);
	freopen("holstein.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &feed[i][j]);
		}
	}
	solve();
	sort(re.begin(), re.end());
	
	printf("%d", re[0].cnt);
	for (int i = 0; i < re[0].cnt; i++) {
		printf(" %d", re[0].arr[i]);
	}
	printf("\n");
	
	
	return 0;
}
