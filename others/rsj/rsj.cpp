#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int k;
string str;
map<string, int> vis;
int main() {
	int ans = 0;
	string ss = "";
	freopen("rsj.in", "r", stdin);
	freopen("rsj.out", "w", stdout);
	scanf("%d", &k);
	cin >> str;
	if (k > str.size() || !k) {
		printf("-1\n");
		return 0;
	}
	string s;
	for (int i = 0; i <= str.size() - k; i++) {
		s = str.substr(i, k);
		vis[s]++;
		if (vis[s] > ans || (vis[s] == ans && s < ss)) {
			ss = s;
			ans = vis[s];
		}
	}
	cout << ss << endl;
	return 0;
}
