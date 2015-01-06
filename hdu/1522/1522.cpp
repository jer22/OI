#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int n;
map<string, int> boy;
map<string, int> girl;
string boys[505], girls[505];
int bmat[505], gmat[505];
int bprio[505][505];
int gprio[505][505];
int pos[505];
int main() {
	freopen("1522.in", "r", stdin);
	while (~scanf("%d", &n)) {
		boy.clear();
		girl.clear();
		memset(bmat, 0, sizeof(bmat));
		memset(gmat, 0, sizeof(gmat));
		string s, ss;
		int cnt = 0;
		int c = 0;
		for (int i = 1; i <= n; i++) {
			cin >> s;
			boy[s] = ++cnt;
			boys[cnt] = s;
			for (int j = 1; j <= n; j++) {
				cin >> ss;
				if (!girl[ss]) {
					girl[ss] = ++c;
					girls[c] = ss;
				}
				bprio[cnt][j] = girl[ss];
			}
		}
		for (int i = 1; i <= n; i++) {
			cin >> s;
			for (int j = 1; j <= n; j++) {
				cin >> ss;
				gprio[girl[s]][boy[ss]] = j;
			}
		}
		memset(pos, 0, sizeof(pos));
		bool imp = false;
		while (true) {
			bool done = true;
			for (int i = 1; i <= n; i++) {
				if (bmat[i]) continue;
				done = false;
				pos[i]++;
				if (pos[i] > n) {
					imp = true;
					break;
				}
				int g = bprio[i][pos[i]];
				if (!gmat[g]) {
					bmat[i] = g;
					gmat[g] = i;
				} else {
					if (gprio[g][i] < gprio[g][gmat[g]]) {
						bmat[gmat[g]] = 0;
						bmat[i] = g;
						gmat[g] = i;
					}
				}
			}
			if (done || imp) break;
		}
		if (imp) {
			cout << "Impossible" << endl;
			continue;
		}
		for (int i = 1; i <= n; i++) {
			cout << boys[i] << ' ' << girls[bmat[i]] << endl;
		}
	}

	return 0;
}
