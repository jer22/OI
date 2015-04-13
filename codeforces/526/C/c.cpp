#include <bits/stdc++.h>

using namespace std;

long long c, ha, hb, wa, wb;
int main() {
	// freopen("c.in", "r", stdin);
	cin >> c >> ha >> hb >> wa >> wb;
	int m = sqrt(c);
	if (wa > wb) swap(wa, wb), swap(ha, hb);
	long long ans = 0;
	if (wb > m) {
		for (int i = 0; i <= c / wb; i++) {
			int na = (c - i * wb) / wa;
			ans = max(ans, na * ha + i * hb);
		}
	} else {
		if (ha * wb > hb * wa) swap(wa, wb), swap(ha, hb);
		for (int i = 0; i <= wb; i++) {
			long long nb = (c - i * wa) / wb;
			ans = max(ans, i * ha + nb * hb);
		}
	}
	cout << ans << endl;

	return 0;
}
