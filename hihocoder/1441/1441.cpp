#include <bits/stdc++.h>

using namespace std;

string s;
map<string, vector<int> > endpos;
int n;
int main() {
	freopen("1441.in", "r", stdin);
	cin >> s;
	for (int i = 1; i <= s.size(); i++) {
		for (int j = 0; j + i <= s.size(); j++) {
			string p = s.substr(j, i);
			endpos[p].push_back(i + j);
		}
	}
	scanf("%d", &n);
	string ss;
	for (int i = 1; i <= n; i++) {
		cin >> ss;
		string lon = ss, sho = ss;
		for (map<string, vector<int> >::iterator it = endpos.begin(); it != endpos.end(); it++) if (it -> first != ss) {
			if (it -> second == endpos[ss]) {
				if ((it -> first).size() > lon.size()) lon = it -> first;
				if ((it -> first).size() < sho.size()) sho = it -> first;
			}
		}
		cout << sho << ' ' << lon;
		for (int j = 0; j < endpos[ss].size(); j++)
			cout << ' ' << endpos[ss][j];
		cout << endl;
	}

	return 0;
}
