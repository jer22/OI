#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

struct Node{
	int hei, val;
	Node() {}
	Node(int a, int b) : hei(a), val(b) {}
	bool operator < (const Node &n) {
		return hei < n.hei;
	}
};

int n;
Node arr[100005];
int sum[100005], ss[100005];
int main() {
	// freopen("c.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i].hei);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i].val);
	sort(arr + 1, arr + n + 1);
	for (int i = n; i >= 1; i--)
		sum[i] = sum[i + 1] + arr[i].val;
	for (int i = 1; i <= n; i++)
		ss[i] = ss[i - 1] + arr[i].val;
	multiset<pii > s;
	int res = 0x3f3f3f3f;
	int temp = 0;
	for (int i = 1; i <= n; i++) {
		s.insert(mp(-arr[i].val, i));
		int cnt = 1;
		int idx = i;
		while (i != n && arr[i].hei == arr[i + 1].hei) {
			cnt++;
			i++;
			s.insert(mp(-arr[i].val, i));
		}
		int ans = sum[i + 1] + ss[idx - 1];
		// ans += temp - cnt * arr[i].val;
		int tot = cnt;
		for (multiset<pii >::iterator it = s.begin(); it != s.end(); it++) {
			// cout << it -> second << endl;
			if (cnt * 2 <= tot + 1) {
				break;
			}
			if (arr[it -> second].hei == arr[i].hei) {
				continue;
			}
			tot++;
			ans += it -> first;
			
		}
		res = min(res, ans);
		// cout << ans << endl;
	}
	cout << res << endl;

	return 0;
}
