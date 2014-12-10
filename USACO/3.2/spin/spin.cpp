/*
ID:shijiey1
PROB:spin
LANG:C++
*/

/*
因为每个轮子转360次一定会回到原位，所以360秒之后还没有结果就说明无解。
每次转动之后枚举0到359的每一个位置如果符合则输出。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int speed[6];
int wheel[5][360];
int pos[5];
int main() {
	freopen("spin.in", "r", stdin);
	freopen("spin.out", "w", stdout);
	for (int i = 0; i < 5; i++) {
		int n;
		scanf("%d %d", &speed[i], &n);
		int a, b;
		for (int k = 0; k < n; k++) {
			scanf("%d %d", &a, &b);
			for (int j = a; j <= a + b; j++) {
				wheel[i][j % 360] = 1;
			}
		}
	}
	for (int i = 0; i < 360; i++) {
		for (int j = 0; j < 360; j++) {
			if (wheel[0][(j + pos[0]) % 360] && wheel[1][(j + pos[1]) % 360] && wheel[2][(j + pos[2]) % 360] && wheel[3][(j + pos[3]) % 360] && wheel[4][(j + pos[4]) % 360]) {
				printf("%d\n", i);
				return 0;
			}
		}
		for (int j = 0; j < 5; j++) {
			pos[j] -= speed[j];
			pos[j] += 360;
			pos[j] %= 360;
		}
	}
	printf("none\n");

	return 0;
}
