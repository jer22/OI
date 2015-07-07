#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int geth(int t) {
	return t / 3600;
}

int getm(int t) {
	return t / 60 % 60;
}

int gets(int t) {
	return t % 60;
}

int n;
int main() {
	freopen("a.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int t = 0; t < 43200; t += 10) {
			int hour = geth(t);
			int mini = getm(t);
			int sece = gets(t);

			// cout << hour << ' ' << mini << ' ' << sece << endl;
			int a = mini * 6000 + sece * 100 + hour * 360000;
			// cout << a << endl;
			int b = sece * 1200 + mini * 72000;
			// cout << b << endl;
			int ans = abs(a - b);
			if (ans > 2160000) ans = 2 * 2160000 - ans;
			if (ans == n) {
				printf("%02d:%02d:%02d\n", hour, mini, sece);
			}
		}

	}


	return 0;
}
