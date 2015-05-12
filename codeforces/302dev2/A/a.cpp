#include <bits/stdc++.h>

using namespace std;

int k;
string str;
bool vis[257];
int ans[35];
int main() {
	freopen("a.in", "r", stdin);
	cin >> k >> str;
	int cnt = 0;
	bool flag = false;
	for (int i = 0; i < str.size(); i++) {
		if (!vis[str[i]]) {
			vis[str[i]] = 1;
			ans[cnt++] = i;
		}
		if (cnt == k) {
			flag = true;
			break;
		}
	}
	if (!flag) cout << "NO" << endl;
	else {
		int pos = 0;
		cout << "YES";
		for (int i = 0; i < str.size(); i++) {
			if (i == ans[pos]) {
				cout << endl;
				pos++;
			}
			cout << str[i];
		}
	}

	return 0;
}
