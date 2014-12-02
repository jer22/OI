#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int n = 0;
string a, b;
string rule[8][2];
map<string,int> vis;
vector<string> arr[11];

int main() {
	freopen("1032.in", "r", stdin);
	cin >> a >> b;
	string x, y;
	while (cin >> x >> y) {
		rule[n][0] = x;
		rule[n][1] = y;
		n++;
	}
	arr[0].push_back(a);
	vis[a] = 1;
	for (int layer = 0; layer <= 10; layer++) {
		for (int i = 0; i < arr[layer].size(); i++) {
			string current = arr[layer][i];
			if (current == b) {
				printf("%d\n", layer);
				return 0;
			}
			string from, to;
			int start = 0;
			for (int j = 0; j < n; j++) {
				start = 0;
				from = rule[j][0];
				to = rule[j][1];
				while (start = current.find(from, start) + 1) {
					string s = current;
					s.replace(start - 1, from.size(), to);
					if (!vis[s]) {
						arr[layer + 1].push_back(s);
					}

					vis[s] = 1;
				}
			}
		}
	}
	printf("NO ANSWER!");
	return 0;
}
