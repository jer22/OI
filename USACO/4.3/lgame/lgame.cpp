/*
ID:shijiey1
PROG:lgame
LANG:C++
*/

/*
第一步先从字典里筛选出所有符合条件的串。
看似数据很大其实第一步筛出来已经没剩几个了，枚举就行。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Pair{
	string a;
	string b;
	void init(string c, string d) {
		a = c;
		b = d;
	}
};

string ori;
int oriarr[28];
vector<string> strings;
int scoo[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};
bool nice(string str) {
	int l = str.size();
	int t[28];
	memset(t, 0, sizeof(t));
	for (int i = 0; i < l; i++) {
		int c = str[i] - 'a';
		t[c]++;
		if (t[c] > oriarr[c]) return false;
	}
	return true;
}

map<string, int> score;
int getsco(string s) {
	if (score[s]) return score[s];
	int l = s.size();
	int sco = 0;
	for (int i = 0; i < l; i++) {
		sco += scoo[s[i] - 'a'];
	}
	score[s] = sco;
	return sco;
}

vector<Pair> ans;
int main() {
	freopen("lgame.out", "w", stdout);
	freopen("lgame.in", "r", stdin);
	cin >> ori;
	int l = ori.size();
	for (int i = 0; i < l; i++) {
		oriarr[ori[i] - 'a']++;
	}
	freopen("lgame.dict", "r", stdin);
	string str;
	while (cin >> str) {
		if (str[0] == '.') break;
		if (nice(str)) {
			strings.push_back(str);
		}
	}
	int n = strings.size();
	int maxsco = 0;
	sort(strings.begin(), strings.end());
	for (int i = 0; i < n; i++) {
		int li = strings[i].size();
		if (!nice(strings[i])) continue;
		int sco = getsco(strings[i]);
		if (sco >= maxsco) {
			maxsco = max(sco, maxsco);
			Pair p;
			p.init(strings[i], ".");
			ans.push_back(p);
		}

		for (int j = i; j < n; j++) {
			int lj = strings[j].size();
			if (li + lj > l) continue;
			string s = strings[i] + strings[j];
			if (nice(s)) {
				int sco = getsco(strings[i]) + getsco(strings[j]);
				if (sco < maxsco) continue;
				maxsco = max(sco, maxsco);
				Pair p;
				p.init(strings[i], strings[j]);
				ans.push_back(p);
			}
		}
	}
	cout << maxsco << endl;
	int len = ans.size();
	for (int i = 0; i < len; i++) {
		if (ans[i].b[0] == '.') {
			if (getsco(ans[i].a) == maxsco) {
				cout << ans[i].a << endl;
			}
		} else {
			if (getsco(ans[i].a) + getsco(ans[i].b) == maxsco) {
				cout << ans[i].a << ' ' << ans[i].b << endl;
			}
		}
	}

	return 0;
}
