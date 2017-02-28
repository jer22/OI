#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

char a[MAXN], b[MAXN];
int lena, lenb;
bool vis[MAXN];
int arr[MAXN];
bool check(int p) {
	for (int i = 0; i < lena; i++)
		vis[i] = 0;
	for (int i = 1; i <= p; i++)
		vis[arr[i] - 1] = 1;
	int l = 0;
	for (int i = 0; i < lena; i++) {
		if (vis[i]) continue;
		if (l < lenb && a[i] == b[l]) l++;
	}
	return l == lenb;
}

int main() {
	freopen("a.in", "r", stdin);
	scanf("%s%s", a, b);
	lena = strlen(a), lenb = strlen(b);
	for (int i = 1; i <= lena; i++)
		scanf("%d", &arr[i]);
	int l = 1, r = lena;
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	if (!check(l)) l = 0;
	cout << l << '\n';
	return 0;
}
