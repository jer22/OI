/*
ID:shijiey1
PROG:contact
LANG:C++
*/

/*
略水。
枚举长度l从a到b，找出字符串中所有长度为l的字串然后用map记录，排序输出。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Num {
	string number;
	int cnt;
	bool operator < (const Num &n) const {
		if (cnt != n.cnt) return cnt > n.cnt;
		if (number.size() != n.number.size()) return number.size() < n.number.size();
		int l = number.size();
		for (int i = 0; i < l; i++) {
			if (number[i] != n.number[i]) {
				return number[i] < n.number[i];
			}
		}
	}
};

int a, b, n;
char s[200010];
int lens;
map<string, int> cnt;
vector<Num> ans;
int main() {
	freopen("contact.in", "r", stdin);
	freopen("contact.out", "w", stdout);
	scanf("%d %d %d\n", &a, &b, &n);
	char c;
	while ((c = getchar()) != EOF) {
		if (c == '\n') continue;
		s[lens++] = c;
	}
	for (int l = a; l <= b; l++) {
		for (int i = 0; i <= lens - l; i++) {
			string str = "";
			for (int j = i; j < i + l; j++) {
				str += s[j];
			}
			cnt[str]++;
		}
	}
	map<string, int>::iterator it;
	for (it = cnt.begin(); it != cnt.end(); it++) {
		Num n;
		n.number = it -> first;
		n.cnt = it -> second;
		ans.push_back(n);
	}
	sort(ans.begin(), ans.end());
	int l = 0, r = 0;
	while (n-- && l < ans.size()) {
		r = l;
		if (l) cout << endl;
		while (ans[r].cnt == ans[l].cnt) r++;
		cout << ans[l].cnt << endl;
		int t = 0;
		for (int i = l; i < r; i++) {
			if (i != l) {
				if (!(t % 6)) {
					cout << endl;
				} else {
					cout << ' ';
				}
			}
			cout << ans[i].number;
			t++;
		}
		l = r;
	}
	cout << endl;
	return 0;
}
