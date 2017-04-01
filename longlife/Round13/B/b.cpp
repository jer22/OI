#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

int n;
long long m;
long long arr[MAXN], v[MAXN];
multiset<long long> s;

long long calc() {
	long long ans = 0;
	int i = 0;
	for (multiset<long long>::iterator it = s.begin(); it != s.end(); it++)
		ans += (*it) * v[++i];
	return ans;
}

int ans[MAXN];
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d %lld", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &v[i]);
	int l = 1;
	int now = 0;
	while (l <= n) {
		int j = 0;
		int r = l + 1;
		s.clear();
		s.insert(arr[l]);
		while (calc() <= m && r <= n) {
			j++;
			while (r < l + (1 << j) && r <= n) {
				s.insert(arr[r]);
				r++;
			}
		}
		if (!j) {
			if (calc() <= m) ans[l] = now;
			else ans[l] = ++now;
		} else {
			int ll = l + (1 << j - 1);
			int rr = r - 1;
			int mid = ll + rr >> 1;
			s.clear();
			for (int i = l; i <= mid; i++)
				s.insert(arr[i]);

			while (ll < rr) {
				mid = ll + rr >> 1;
				if (calc() > m) {
					int mmid = ll + mid >> 1;
					rr = mid;
					while (mid > mmid) {
						s.erase(arr[mid]);
						mid--;
					}
				}
				else {
					int mmid = (mid + 1 + rr) >> 1;
					ll = mid + 1;
					while (mid < mmid) {
						mid++;
						s.insert(arr[mid]);
					}
				}
			}
			if (calc() > m) ans[ll] = ++now;
			else ans[ll] = now;
			r = ll + 1;
		}
		l = r;
		// cout << pos[now] << endl;
		
	}
	for (int i = 1; i <= n; i++)
		ans[i] = max(ans[i], ans[i - 1]);
	for (int i = 1; i <= n; i++)
		printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}
