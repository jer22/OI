#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 200005;
const int MAXM = 128;

int n, lens;
char s[MAXN];
int sa[MAXN], rank[MAXN], height[MAXN], tmp[MAXN];
struct Node {
	int id, c[2];
} Count[MAXN], Count_b[MAXN];

void getSA() {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < n; i++) tmp[s[i]]++;
	for (int i = 1; i < MAXM; i++) tmp[i] += tmp[i - 1];
	for (int i = 0; i < n; i++) rank[i] = tmp[s[i] - 1];
	int j = 0;
	while ((1 << j) < n) {
		for (int i = 0; i < n; i++) {
			Count[i].id = i;
			Count[i].c[0] = rank[i];
			Count[i].c[1] = (i + (1 << j)) >= n ? -1 : rank[i + (1 << j)];
		}
		for (int i = 1; i >= 0; i--) {
			memset(tmp, 0, sizeof(tmp));
			for (int j = 0; j < n; j++) tmp[Count[j].c[i] + 1]++;
			for (int j = 1; j < MAXN; j++) tmp[j] += tmp[j - 1];
			for (int j = n - 1; j >= 0; j--) Count_b[--tmp[Count[j].c[i] + 1]] = Count[j];
			for (int j = 0; j < n; j++) Count[j] = Count_b[j];
		}
		rank[Count[0].id] = 0;
		for (int i = 1; i < n; i++) {
			rank[Count[i].id] = rank[Count[i - 1].id];
			if (Count[i].c[0] != Count[i - 1].c[0] || Count[i].c[1] != Count[i - 1].c[1])
				rank[Count[i].id]++;
		}
		j++;
	}
	for (int i = 0; i < n; i++) sa[rank[i]] = i;
}

void getHeight() {
	int k = 0, j;
	for (int i = 0; i < n; height[rank[i++]] = k) {
		if (!rank[i]) k = 0;
		else {
			for (k ? k-- : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
				if (i + k == n - 1 || j + k == n - 1) {
					k++;
					break;
				}
		}
	}
}

int main() {
	freopen("2774.in", "r", stdin);
	scanf("%s", s);
	lens = strlen(s);
	s[lens] = '#';
	scanf("%s", s + lens + 1);
	n = strlen(s);
	getSA();
	getHeight();
	int ma = 0;
	int idx;
	for (int i = 1; i < n; i++) {
		if (height[i] > ma) {
			if (sa[i] > lens && sa[i - 1] < lens || sa[i - 1] > lens && sa[i] < lens) {
				ma = height[i];
				idx = i;
			}
		}
	}
	cout << ma << endl;
	return 0;
}
