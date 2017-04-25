#include <bits/stdc++.h>

using namespace std;

int T, n;
int R, O, Y, G, B, V;
char ch[266];
string ff[266];
int main() {
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T;  cas++) {
		printf("Case #%d: ", cas);
		scanf("%d %d %d %d %d %d %d", &n, &R, &O, &Y, &G, &B, &V);
		int r = R, o = O, y = Y, g = G, b = B, v = V;
		r -= G;
		y -= V;
		b -= O;
		if (G && !r) {
			if (O || Y || B || V) printf("IMPOSSIBLE\n");
			else {
				for (int i = 0; i < G; i++) printf("GR");
				printf("\n");
			}
			continue;
		}
		if (O && !b) {
			if (R || Y || G || V) printf("IMPOSSIBLE\n");
			else {
				for (int i = 0; i < O; i++) printf("OB");
				printf("\n");
			}
			continue;
		}
		if (V && !y) {
			if (O || R || B || G) printf("IMPOSSIBLE\n");
			else {
				for (int i = 0; i < V; i++) printf("VY");
				printf("\n");
			}
			continue;
		}
		ch['r'] = 'R';
		ch['y'] = 'Y';
		ch['b'] = 'B';
		ff['r'] = "GR";
		ff['y'] = "VY";
		ff['b'] = "OB";
		if (r < y) swap(r, y), swap(ch['r'], ch['y']), swap(ff['r'], ff['y']), swap(G, V);
		if (r < b) swap(r, b), swap(ch['r'], ch['b']), swap(ff['r'], ff['b']), swap(G, O);
		if (b < y) swap(b, y), swap(ch['b'], ch['y']), swap(ff['b'], ff['y']), swap(V, O);
		if (r > y + b) printf("IMPOSSIBLE\n");
		else {
			for (int i = 1; i <= r; i++) {
				cout << ch['r'];
				if (i == 1) for (int j = 0; j < G; j++) cout << ff['r'];
				if (y > 0) {
					cout << ch['y'];
					if (y == 1) for (int j = 0; j < V; j++) cout << ff['y'];
					y--;
				}
				if (i + b > r) {
					cout << ch['b'];
					if (b == 1) for (int j = 0; j < O; j++) cout << ff['b'];
					b--;
				}
			}
			cout << endl;
		}
	}


	return 0;
}
