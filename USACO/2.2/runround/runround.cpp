/*
ID:shijiey1
PROG:runround
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

long long n;

bool isNum() {
	int vis[80];
	memset(vis, 0, sizeof(vis));
	long long t = n;
	while (t) {
		int a = t % 10;
		if (!a) return 0;
		vis[a]++;
		if (vis[a] > 1) return 0;
		t /= 10;
	}
	return 1;
}

bool isLoop() {
	int vis[80];
	memset(vis, 0, sizeof(vis));
	long long t = n;
	string str = "";
	while (t) {
		int a = t % 10;
		char c = a + '0';
		str = str + c;
		t /= 10;;
	}
	int len = str.size();
	int i = len - 1;
	int cnt = 0;
	while (true) {
		i -= str[i] - '0';
		while (i < 0) i += len;
		vis[i]++;
		if (vis[i] > 1) return 0;
		cnt++;
		if (cnt == len) return 1;
	}
	
	return 1;
}

int main() {
	freopen("runround.in", "r", stdin);
	freopen("runround.out", "w", stdout);
	scanf("%lld", &n);
	while (true) {
		n++;
		if (!isNum()) continue;
		if (isLoop()) {
			printf("%lld\n", n);
			break;
		}
	}

	return 0;
}
