#include <cstdio>
#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

const int MAXN = 5005;

int T, n;
int arr[MAXN], tot = 0, aot;
unordered_map<int, long long> vis;
int main() {
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		tot = aot = 0;
		vis.clear();
		char op[10];
		for (int i = 1, x; i <= n; i++) {
			printf("Operation #%d: ", i);
			scanf("%s", op);
			if (op[0] == 'A') {								//add
				scanf("%d", &x);
				if (vis.find(x) != vis.end())
					printf("same priority.");
				else {
					vis.insert(make_pair(x, 0));
					arr[++tot] = x;
					printf("success.");
				}
			} else if (op[0] == 'C' && strlen(op) == 5) {	//close
				scanf("%d", &x);
				if (vis.find(x) == vis.end()) printf("invalid priority.");
				else {
					printf("close %d with %lld.", x, vis[x]);
					vis.erase(x);
					if (aot == x) aot = 0;
					int idx = 0;
					for (int j = 1; j <= tot; j++) {
						if (arr[j] == x) {
							idx = j;
							break;
						}
					}
					for (int j = idx; j < tot; j++)
						arr[j] = arr[j + 1];
					tot--;
				}
			} else if (op[0] == 'C' && strlen(op) == 4) {	//chat
				scanf("%d", &x);
				if (!tot) printf("empty.");
				else {
					if (aot) vis[aot] += x;
					else vis[arr[1]] += x;
					printf("success.");
				}
			} else if (op[0] == 'R') {						//rotate
				scanf("%d", &x);
				if (x < 1 || x > tot) printf("out of range.");
				else {
					int t = arr[x];
					for (int j = x - 1; j >= 1; j--)
						arr[j + 1] = arr[j];
					arr[1] = t;
					printf("success.");
				}
			} else if (op[0] == 'P') {						//prior
				if (!tot) printf("empty.");
				else {
					int mx = 0, idx = 0;
					for (int j = 1; j <= tot; j++)
						if (arr[j] > mx) mx = arr[j], idx = j;
					int t = arr[idx];
					for (int j = idx - 1; j >= 1; j--)
						arr[j + 1] = arr[j];
					arr[1] = t;
					printf("success.");
				}
			} else if (op[0] == 'C' && strlen(op) == 6) {	//choose
				scanf("%d", &x);
				if (vis.find(x) == vis.end()) printf("invalid priority.");
				else {
					int idx = 0;
					for (int j = 1; j <= tot; j++) {
						if (arr[j] == x) {
							idx = j;
							break;
						}
					}
					int t = arr[idx];
					for (int j = idx - 1; j >= 1; j--)
						arr[j + 1] = arr[j];
					arr[1] = t;
					printf("success.");
				}
			} else if (op[0] == 'T') {						//top
				scanf("%d", &x);
				if (vis.find(x) == vis.end()) printf("invalid priority.");
				else {
					aot = x;
					printf("success.");
				}
			} else {										//untop
				if (!aot) printf("no such person.");
				else {
					aot = 0;
					printf("success.");
				}
			}
			printf("\n");
		}
		if (aot && vis[aot] > 0) printf("Bye %d: %lld\n", aot, vis[aot]);
		for (int i = 1; i <= tot; i++) {
			if (vis[arr[i]] <= 0 || arr[i] == aot) continue;
			printf("Bye %d: %lld\n", arr[i], vis[arr[i]]);
		}
	}

	return 0;
}
