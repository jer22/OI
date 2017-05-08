#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const long long INF = 100000000000000000ll;

int n;
long long arr[MAXN];
multiset<long long> ed;
multiset<long long> lst;
int main() {
	freopen("c.in", "r", stdin);
	scanf("%d", &n);
	map<long long, int> s;
	lst.clear();
	ed.clear();
	s.clear();
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
		s[arr[i]]++;
		lst.insert(arr[i]);
	}

	int mx = s[1];
	int ans = -1;
	for (int i = 1; i <= mx; i++) {
		for (long long j = 1ll; j <= INF; j *= 2ll) {
			if (s.find(j) != s.end()) {
				if (s[j] == 1) s.erase(j);
				else s[j]--;
				multiset<long long>::iterator ii = lst.find(j);
				assert(ii != lst.end());
				lst.erase(ii);
			} else {
				ed.insert(j / 2ll);
				break;
			}
		}
		if (lst.size() > i) continue;
		multiset<long long>::iterator it2 = lst.begin();
		for (multiset<long long>::iterator it = ed.begin(); it != ed.end(); it++) {
			if (it2 != lst.end()){
				if (((*it2) <= (*it) * 2)) it2++;
			}
			else break;
		}
		if (it2 == lst.end()) ans = i;
		break;
	}
	if (ans == -1) cout << ans << endl;
	else {
		for (int i = ans; i <= mx; i++)
			cout << i << " \n"[i == mx];
	}
	return 0;
}
