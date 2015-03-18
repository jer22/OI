/*************************************************************************
    > File Name: 1743.cpp
    > Author: wmg_1001
    > Mail: wmg_1007@163.com 
    > Created Time: 2014Äê12ÔÂ19ÈÕ ÐÇÆÚÎå 23Ê±35·Ö05Ãë
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <queue>
#include <map>
#include <set>
using namespace std;

const int maxn = 20005;
const int maxm = 205;

int n, A[maxn], sa[maxn], rank[maxn], height[maxn], tmp[maxn];
struct Node {
	int id, c[2];
}Count[maxn], Count_b[maxn];

void Make_sa(void) {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < n; i++) tmp[A[i]]++;
	for (int i = 1; i < maxm; i++) tmp[i] += tmp[i - 1];
	for (int i = 0; i < n; i++) rank[i] = tmp[A[i] - 1];
	int j = 0;
	while ((1 << j) < n) {
		for (int i = 0; i < n; i++) {
			Count[i].c[0] = rank[i], Count[i].c[1] = (i + (1 << j)) >= n ? -1 : rank[i + (1 << j)];
			Count[i].id = i;
		}
		for (int i = 1; i >= 0; i--) {
			memset(tmp, 0, sizeof(tmp));
			for (int j = 0; j < n; j++) tmp[Count[j].c[i] + 1]++;
			for (int j = 1; j < maxn; j++) tmp[j] += tmp[j - 1];
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

void Make_height(void) {
	int k = 0, j;
	for (int i = 0; i < n; height[rank[i++]] = k) {
		if (rank[i] == 0) k = 0;
		else {
			for (k ? k-- : 0, j = sa[rank[i] - 1]; A[i + k] == A[j + k]; k++)
				if (i + k == n - 1 || j + k == n - 1) {
					k++;
					break;
				}
		}
	}
}

bool Calc(int x) {
	int l, r;
	for (int i = 0; i < n; i++) {
		if (height[i] < x) {
			l = r = sa[i];
			continue;
		}
		l = min(l, sa[i]);
		r = max(r, sa[i]);
		if (r - l > x) return true;
	}
	return false;
}

int main() {
	freopen("1743.in", "r", stdin);
	// freopen("1743.out", "w", stdout);
	while (scanf("%d", &n) != EOF && n != 0) {
		for (int i = 0; i < n; i++) scanf("%d", &A[i]);
		if (n == 1) {
			cout << 0 << endl;
			continue;
		}
	
		for (int i = 0; i < n; i++) A[i] = A[i + 1] - A[i] + 87;
		Make_sa();
		Make_height();
		int l = 0, r = n;
		while (l < r) {
			if (r == l + 1) {
				if (Calc(r)) l = r;
				else r = l;
			} else {
				int mid = (l + r) >> 1;
				if (Calc(mid)) l = mid;
				else r = mid;
			}
		}
		if (l > 3) printf("%d\n", l + 1);
		else printf("0\n");
	}
	return 0;
}
