#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int a, b, c, d;
int xa[5], xb[5], xc[5], xd[5];
int main() {
	freopen("1002.in", "r", stdin);
	scanf("%d", &T);
	int aa, bb, cc, dd;
	while (T--) {
		aa = bb = cc = dd = 0;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		if (a > 3) {
			xa[aa++] = 0;
			xa[aa++] = 1;
			if (a > 4) {
				xa[aa++] = 2;
			}
		} else xa[aa++] = a % 3;
		if (b > 3) {
			xb[bb++] = 0;
			xb[bb++] = 1;
			if (b > 4) {
				xb[bb++] = 2;
			}
		} else xb[bb++] = b % 3;
		if (c > 3) {
			xc[cc++] = 0;
			xc[cc++] = 1;
			if (c > 4) {
				xc[cc++] = 2;
			}
		} else xc[cc++] = c % 3;
		if (d > 3) {
			xd[dd++] = 0;
			xd[dd++] = 1;
			if (d > 4) {
				xd[dd++] = 2;
			}
		} else xd[dd++] = d % 3;
		// cout << dd << endl;
		bool flag = false;
		for (a = 0; a < aa; a++) {
			if (flag) break;
			for (b = 0; b < bb; b++) {
				if (flag) break;
				for (c = 0; c < cc; c++) {
					if (flag) break;
					for (d = 0; d < dd; d++) {
						if (flag) break;
						if (!(xa[a] + xb[b] + xc[c] + xd[d])) {
							flag = true;
							break;
						} else if (xa[a] + xb[b] + xc[c] + xd[d] == 3) {
							if ((xa[a] && xb[b] && xc[c]) || (xb[b] && xc[c] && xd[d])) {
								flag = true;
								break;
							}
						} else if (xa[a] + xb[b] + xc[c] + xd[d] == 4) {
							if (xa[a] && xb[b] && xc[c] && xd[d]) {
								flag = true;
								break;
							}
							// else printf("No\n");
						} else if (xa[a] + xb[b] + xc[c] + xd[d] == 6) {
							if (xb[b] == 2 && xc[c] == 2) {
								flag = true;
								break;
							}
							// else printf("No\n");
						} else if (xa[a] + xb[b] + xc[c] + xd[d] == 7) {
							if (xb[b] == 2 && xc[c] == 2) {
								flag = true;
								break;
							}
							// else printf("No\n");
						} else if (xa[a] + xb[b] + xc[c] + xd[d] == 8) flag = true;
						// else printf("No\n");
					}
				}
			}
		}
		if (flag) printf("Yes\n");
		else printf("No\n");
		
	}


	return 0;
}
