#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

int n1, n2;
set<int> dist;
vector<int> ans1, ans2;
int cur1 = 0, cur2 = 0;
int main() {
	// freopen("c.in", "r", stdin);
	// freopen("c.out", "w", stdout);
	scanf("%d", &n1);
	int t;
	dist.insert(0);
	for (int i = 0; i < n1; i++) {
		scanf("%d", &t);
		dist.insert(t);
		ans1.push_back(t);
	}
	scanf("%d", &n2);
	for (int i = 0; i < n2; i++) {
		scanf("%d", &t);
		dist.insert(t);
		ans2.push_back(t);
	}
	set<int>::iterator it;
	sort(ans1.begin(), ans1.end());
	sort(ans2.begin(), ans2.end());
	int l1 = ans1.size();
	int l2 = ans2.size();
	long long maxans = -10000000;
	long long t1 = 0, t2 = 0;
	for (it = dist.begin(); it != dist.end(); it++) {
		for (int &i = cur1; i < l1; i++) {
			if (ans1[i] > (*it)) break;
		}
		for (int &j = cur2; j < l2; j++) {
			if (ans2[j] > (*it)) break;
		}
		long long score1 = cur1 * 2 + (l1 - cur1) * 3;
		long long score2 = cur2 * 2 + (l2 - cur2) * 3;
		long long ans = score1 - score2;
		if (ans > maxans) {
			maxans = ans;
			t1 = score1;
			t2 = score2;
		} else if (ans == maxans) {
			if (score1 > t1) {
				t1 = score1;
				t2 = score2;
			}
		}
	}
	cout << t1 << ':' << t2 << endl;
	return 0;
}
