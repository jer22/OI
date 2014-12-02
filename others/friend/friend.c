#include <stdio.h>

int uf[30002];
int sz[30002];

int find(int n) {
	while(n != uf[n])
		n = uf[n];
	return n;
}

void un(int p, int q) {
	int i = find(p);
	int j = find(q);
	if (i == j)
		return;
	if (sz[i] < sz[j]) {
		uf[i] = j;
		sz[j] += sz[i];
	} else {
		uf[j] = i;
		sz[i] += sz[j];
	}
}

int main( void ) {
	FILE* in = fopen("friend.in", "r");
	FILE* out = fopen("friend.out", "w");
	int n, m;
	fscanf(in, "%d %d", &n, &m);
	int i;
	for (i = 0; i < n; i++) {
		uf[i] = i;
		sz[i] = 1;
	}
	int a, b;
	for (i = 0; i < m; i++) {
		fscanf(in, "%d%d", &a, &b);
		un(a, b);
	}
	int max = 0;
	for (i = 0; i < n; i++) {
		if (sz[i] > max)
			max = sz[i];
	}
	fprintf(out, "%d", max);
	fclose(in);
	fclose(out);
	return 0;
}
