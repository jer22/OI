#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int L;
int N, C, T;
int VR, VT1, VT2;
int dist[105];
double dp[105];
int main() {
	freopen("2059.in", "r", stdin);
	while (cin >> L) {
		cin >> N >> C >> T;
		cin >> VR >> VT1 >> VT2;
		for (int i = 1; i <= N; i++)
			cin >> dist[i];
		dist[N + 1] = L;
		for (int i = 1; i <= N + 1; i++) {
			dp[i] = 0x3f3f3f3f;
			for (int j = i - 1; j >= 0; j--) {
				int l = dist[i] - dist[j];
				double tmp;
				if (l < C)
					tmp = (l * 1.0) / VT1;
				else tmp = C * 1.0 / VT1 + (l - C) * 1.0 / VT2;
				if (j) tmp += T;
				dp[i] = min(dp[i], dp[j] + tmp);
			}
		}
		printf(dp[N + 1] > (L * 1.0 / VR)?"Good job,rabbit!\n":"What a pity rabbit!\n");
	}
	return 0;
}
