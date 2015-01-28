#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

char str[100005];
int main() {
	// freopen("b.in", "r", stdin);
	scanf("%s", str);
	int len = strlen(str);
	int t;
	int rear = str[len - 1] - '0';
	bool find = false;
	bool flag = false;
	int idx = 0;
	for (int i = 0; i < len - 1; i++) {
		t = str[i] - '0';
		if (t % 2) continue;
		find = true;
		idx = i;
		if (t < rear) {
			swap(str[i], str[len - 1]);
			flag = true;
			break;
		}
	}
	if (!find) {
		cout << "-1" << endl;
		return 0;
	}
	if (flag) cout << str << endl;
	else {
		swap(str[idx], str[len - 1]);
		cout << str << endl;
	}
	return 0;
}
