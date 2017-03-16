#include <bits/stdc++.h>

#define blo(i) ((i) / bc + 1)

using namespace std;

const int MAXN = 200005;

int n, q;
int root[MAXN + 100000];

int arr[MAXN];
int brr[MAXN];
int l[500], r[500];

void update(int p) {
	for (int i = l[p]; i <= r[p]; i++)
		brr[i] = arr[i];
	sort(brr + l[p], brr + r[p] + 1);
}

int bc = 0;

int getmx(int a, int b, int x) {

	int aa = a, bb = b;
	while (aa < bb) {
		int mid = (aa + bb >> 1);
		if (brr[mid] < x) aa = mid + 1;
		else bb = mid;
	}
	if (brr[aa] < x) return 0;
	return b - aa + 1;
}

int getmi(int a, int b, int x) {
	int aa = a, bb = b;
	while (aa < bb) {
		int mid = aa + bb >> 1;
		if (brr[mid] < x) aa = mid + 1;
		else bb = mid;
	}
	if (brr[aa] < x) return aa - a + 1;
	return aa - a;
}

int quemx(int a, int b, int x) {
	if (a > b) return 0;
	int ta = blo(a), tb = blo(b);
	int ans = 0;
	if (ta == tb) {
		for (int i = a; i <= b; i++)
			if (arr[i] > x) ans++;
		return ans;
	}
	for (int i = a; i <= r[ta]; i++)
		if (arr[i] > x) ans++;
	for (int i = l[tb]; i <= b; i++) {
		if (arr[i] > x) ans++;
	}
	ta++, tb--;
	if (a > b) return ans;
	for (int bb = ta; bb <= tb; bb++) {
		ans += getmx(l[bb], r[bb], x);
	}
	return ans;
}

int quemi(int a, int b, int x) {
	if (a > b) return 0;
	int ta = blo(a), tb = blo(b);
	int ans = 0;
	if (ta == tb) {
		for (int i = a; i <= b; i++)
			if (arr[i] < x) ans++;
		return ans;
	}
	for (int i = a; i <= r[ta]; i++)
		if (arr[i] < x) ans++;
	for (int i = l[tb]; i <= b; i++)
		if (arr[i] < x) ans++;
	ta++, tb--;
	if (a > b) return ans;
	for (int bb = ta; bb <= tb; bb++) {
		ans += getmi(l[bb], r[bb], x);
	}
	return ans;
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		arr[i] = brr[i] = i;
	}
	bc = (int)sqrt(n) + 1;
	for (int i = 1; i <= n; i++) {
		if (!l[blo(i)]) l[blo(i)] = i;
		r[blo(i)] = i;
	}
	int a, b;
	long long ans = 0;
	int tot = n;


	for (int i = 1; i <= q; i++) {
		scanf("%d %d", &a, &b);
		if (a == b) {
			printf("%lld\n", ans);
			continue;
		}
		if (a > b) swap(a, b);

		int t1 = quemx(a + 1, b - 1, arr[a]);
		int t2 = quemx(a + 1, b - 1, arr[b]);
		int t3 = quemi(a + 1, b - 1, arr[a]);
		int t4 = quemi(a + 1, b - 1, arr[b]);
		ans += t1;
		ans -= t2;
		ans -= t3;
		ans += t4;
		if (i == q) {

		}
		swap(arr[a], arr[b]);
		if (blo(a) != blo(b)) update(blo(a)), update(blo(b));
		if (arr[a] > arr[b]) ans++;
		else ans--;
		printf("%lld\n", ans);
		
	}

	return 0;
}
