#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int n;
string first[100005];
string last[100005];
int prio[100005];
int main() {
	freopen("e.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++)
			cin >> first[i] >> last[i];
		for (int i = 1; i <= n; i++)
			cin >> prio[i];
		bool flag = true;
		string pre;
		if (first[prio[1]] < last[prio[1]]) pre = first[prio[1]];
		else pre = last[prio[1]];
		for (int i = 2; i <= n; i++) {
			string tt = "";
			if (first[prio[i]]>pre)
			{
				tt=first[prio[i]];
			}
			if (last[prio[i]]>pre)
			{
				if (tt=="") tt=last[prio[i]];
				else tt=min(last[prio[i]],tt);
			}
			pre=tt;
			if (tt == "") {
				flag = false;
				break;
			}
		}
		if (flag) cout << "YES" << endl;
		else cout << "NO" << endl;
	}


	return 0;
}
