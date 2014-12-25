#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int g, b, p;
int gb[22][22];
int gp[22][22];
int bp[22][22];

int visb[22];
int visp[22];

int main() {
	freopen("3121.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		memset(gb, 0, sizeof(gb));
		memset(gp, 0, sizeof(gp));
		memset(bp, 0, sizeof(bp));
		scanf("%d %d %d", &g, &b, &p);
		for (int i = 0; i < g; i++)
			for (int j = 0; j < b; j++)
				cin >> gb[i][j];
		for (int i = 0; i < g; i++)
			for (int j = 0; j < p; j++)
				cin >> gp[i][j];
		for (int i = 0; i < b; i++)
			for (int j = 0; j < p; j++)
				cin >> bp[i][j];
		
	}

	return 0;
}
