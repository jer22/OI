#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 1000005;
const int MAXM = 128;

int n;
char s[MAXN];
int sa[MAXN], rank[MAXN], height[MAXN], tmp[MAXN], lcp[MAXN];
struct Node{
	int id, c[2];
} Count[MAXN], Count_b[MAXN];

void getSa(void) {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < n; i++) tmp[s[i]]++;
	for (int i = 1; i < MAXM; i++) tmp[i] += tmp[i - 1];
	for (int i = 0; i < n; i++) rank[i] = tmp[s[i] - 1];
	int j = 0;
	while ((1 << j) < n) {
		for (int i = 0; i < n; i++) {
			Count[i].c[0] = rank[i], Count[i].c[1] = (i + (1 << j)) >= n ? -1 : rank[i + (1 << j)];
			Count[i].id = i;
		}
		for (int i = 1; i >= 0; i--) {
			memset(tmp, 0, sizeof(tmp));
			for (int j = 0; j < n; j++) tmp[Count[j].c[i] + 1]++;
			for (int j = 1; j < MAXN; j++) tmp[j] += tmp[j - 1];
			for (int j = n - 1; j >= 0; j--) Count_b[--tmp[Count[j].c[i] + 1]] = Count[j];
			for (int i = 0; i < n; i++) Count[i] = Count_b[i];
		}
		rank[Count[0].id] = 0;
		for (int i = 1; i < n; i++) {
			rank[Count[i].id] = rank[Count[i - 1].id];
			if (Count[i].c[0] != Count[i - 1].c[0] || Count[i].c[1] != Count[i - 1].c[1]) rank[Count[i].id]++;
		}
		j++;
	}
	for (int i = 0; i < n; i++) sa[rank[i]] = i;
}

void getHeight(void) {
	int k = 0, j;
	for (int i = 0; i < n; height[rank[i++]] = k) {
		if (rank[i] == 0) k = 0;
		else {
			for (k ? k-- : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
				if (i + k == n - 1 || j + k == n - 1) {
					k++;
					break;
				}
		}
	}
}


void LCP() {
	int k = rank[0];
	lcp[k] = 0x3f3f3f3f;
	for (int i = k - 1; i >= 0; i--) {
		lcp[i] = min(lcp[i + 1], height[i + 1]);  
	}
	for (int i = rank[0] + 1; i <= n; i++) {
		lcp[i] = min(height[i], lcp[i - 1]);
	}
}

int solve() {
	for (int i = 1; i <= n / 2; i++) {
		if (n % i) continue;
		if (lcp[rank[i]] == n - i) return i;
	}
	return n;
}

int main() {
	freopen("2406.in", "r", stdin);
	while (scanf("%s", s) != EOF) {
		if (s[0] == '.') break;
		n = strlen(s);
		getSa();
		getHeight();
		LCP();
		// for (int i = 0; i < n; i++)
		// 	cout << height[i] << ' ';
		// cout << endl;
		cout << n / solve() << endl;
	}

	return 0;
}
