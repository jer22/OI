#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>

#define MAXN 110

using namespace std;

int n;
string name[MAXN];
int score[MAXN];
int class_score[MAXN];
char cardre[MAXN];
char west[MAXN];
int paper[MAXN];
int money[MAXN];
int main() {
	freopen("1051.in", "r", stdin);
	memset(money, 0, sizeof(money));
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		cin >> name[i] >> score[i] >> class_score[i] >> cardre[i] >> west[i] >> paper[i];
	}
	for (int i = 0; i < n; i++) {
		if (score[i] > 80 && paper[i] >= 1) {
			money[i] += 8000;
		}
		if (score[i] > 85 && class_score[i] > 80) {
			money[i] += 4000;
		}
		if (score[i] > 90) {
			money[i] += 2000;
		}
		if (score[i] > 85 && west[i] == 'Y') {
			money[i] += 1000;
		}
		if (class_score[i] > 80 && cardre[i] == 'Y') {
			money[i] += 850;
		}
	}
	int max = 0;
	int idx = 0;
	int total = 0;
	for (int i = 0; i < n; i++) {
        printf("%d ", money[i]);
		if (money[i] > max) {
			idx = i;
			max = money[i];
		}
		total += money[i];
	}
	printf("\n");
	cout << name[idx] << '\n' << money[idx] << '\n' << total << '\n';
	return 0;
}
