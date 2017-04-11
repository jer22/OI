#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define MAXN 100005

using namespace std;

struct Node{
	long long sig = 0, wid = 0;
	Node() {}
	Node(long long a, long long b) : sig(a), wid(b) {}
	bool operator < (const Node &n) const {
		if (sig != n.sig) return sig > n.sig;
		return wid < n.wid;
	}
	Node operator + (const Node &n) const {
		return Node(sig + n.sig, wid + n.wid);
	}
};

int n, m;
long long d;
Node arr[MAXN], brr[MAXN];
Node sum1[MAXN], sum2[MAXN];

int main() {
	freopen("b.in", "r", stdin);
	scanf("%d %d %lld", &n, &m, &d);
	for (int i = 1; i <= n; i++)
		scanf("%lld %lld", &arr[i].sig, &arr[i].wid);
	for (int i = 1; i <= m; i++)
		scanf("%lld %lld", &brr[i].sig, &brr[i].wid);
	sort(arr + 1, arr + n + 1);
	sort(brr + 1, brr + m + 1);
	for (int i = 1; i <= n; i++)
		sum1[i] = sum1[i - 1] + arr[i];
	for (int i = 1; i <= m; i++)
		sum2[i] = sum2[i - 1] + brr[i];
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		if (sum1[i].wid > d) break;
		long long rem = d - sum1[i].wid;
		int l = 0, r = m;
		while (l < r) {
			int mid = (l + r >> 1) + 1;
			if (sum2[mid].wid <= rem) l = mid;
			else r = mid - 1;
		}
		if (!l) continue;
		ans = max(ans, sum1[i].sig + sum2[l].sig);
	}
	cout << ans << endl;


	return 0;
}
