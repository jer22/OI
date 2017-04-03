#include <cstdio>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

int n, k;
set<int> s1, s2;
bool solve(int x) {
	s1.clear();
	s2.clear();
	for (int i = 1; i <= n; i++)
		if (i == x) s1.insert(i); else s2.insert(i);
	vector<int> v;
	while (!s2.empty()) {
		v.clear();
		for (set<int>::iterator it = s1.begin(); it != s1.end(); it++) {
			set<int>::iterator f = s2.upper_bound(*it + k);
			if (f == s2.begin()) return false;
			f--;
			v.push_back(*f);
			s2.erase(f);
		}
		for (auto vv : v) s1.insert(vv);
		v.clear();
	}
	return true;
}

int main() {
	freopen("d.in", "r", stdin);
	scanf("%d %d", &n, &k);
	int l = 1, r = n;
	while (l < r) {
		int mid = l + r >> 1;
		if (solve(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;

	return 0;
}
