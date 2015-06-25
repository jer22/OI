#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 10005;

int n, m;
int arr[2][MAXN];
bool flag = 0;

bool vis[MAXN];
int cm() {
	memset(vis, 0, sizeof(vis));
	int suma = 0, sumb = 0;
	int cnta = 0, cntb = 0;
	for (int i = 0; i < n; i++) {
		if (cnta < cntb) {
			cnta++;
			suma += arr[flag][i];
		} else {
			cntb++;
			vis[i] = 1;
			sumb += arr[flag][i];
		}
	}
	int best = min(suma, sumb);
	for (int i = 0; i < 10000; i++) {
		int a = rand() % n;
		int b = rand() % n;
		while (vis[a] == vis[b]) {
			a = rand() % n;
			b = rand() % n;
		}
		if (vis[a]) {
			sumb -= arr[flag][a];
			sumb += arr[flag][b];
			suma += arr[flag][a];
			suma -= arr[flag][b];
		} else {
			suma -= arr[flag][a];
			suma += arr[flag][b];
			sumb -= arr[flag][b];
			sumb += arr[flag][a];
		}
		swap(vis[a], vis[b]);
		best = max(best, min(suma, sumb));
	}

	return best;
}

int main() {
	freopen("3063.in", "r", stdin);
	srand(0x865312);
	while (scanf("%d %d", &n, &m) != EOF) {
		flag = 0;
		int suma = 0, sumb = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &arr[0][i], &arr[1][i]);
			suma += arr[0][i], sumb += arr[1][i];
		}
		if (sumb > suma) flag = 1;
		int best = 0;
		for (int i = 0; i < 10; i++)
			best = max(best, cm());
		if (best <= n * m / 4) printf("No solution\n");
		else {
			if (flag) printf("B ");
			else printf("W ");
			printf("%.2f\n", ((double)best * 100 / (n * m / 2)));
		}
	}
	return 0;
}
