#include <bits/stdc++.h>

using namespace std;

struct Node{
	char c;
	int pos;
	Node() {}
	Node(char a, int b) : c(a), pos(b) {}
	bool operator < (const Node &n) const {
		if (c != n.c) return c < n.c;
		return pos > n.pos;
	}
};

int m;
string s;
int cnt[255];
multiset<Node> ss;
char mmm[100005];
int pos[100005];
int main() {
	freopen("d.in", "r", stdin);
	cin >> m;
	cin >> s;
	for (int i = 0; i < s.size(); i++)
		cnt[s[i]]++;
	int l = 0, r = 0;
	for (; r < m; r++) ss.insert(Node(s[r], r));
	char mi = ss.begin() -> c;
	mmm[0] = mi;
	pos[0] = ss.begin() -> pos;
	for (; r < s.size() ; r++, l++) {
		ss.insert(Node(s[r], r));
		ss.erase(Node(s[l], l));
		mi = max(mi, ss.begin() -> c);
		mmm[l + 1] = ss.begin() -> c;

		pos[l + 1] = ss.begin() -> pos;
	}
	string ans = "";
	for (char cc = 'a'; cc < mi; cc++)
		for (int i = 0; i < cnt[cc]; i++)
			ans += cc;
	
	for (int i = 0; i < s.size(); i++) {
		if (i + m > s.size()) break;
		// cout << i << endl;
		if (mmm[i] != mi) continue;
		ans += mi;
		i = pos[i];
	}
	cout << ans << endl;


	return 0;
}
