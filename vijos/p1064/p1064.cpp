#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char arr[280];
int k;
int main() {
	freopen("p1064.in", "r", stdin);
	scanf("%d\n", &k);
	scanf("%s", arr);
	// 输出第一行
	for (int i = 0; i < strlen(arr); i++) {
		if (i) printf(" ");
		printf(" ");
		for (int j = 0; j < k; j++) {
			if (arr[i] == '1' || arr[i] == '4') {
				printf(" ");
			} else {
				printf("-");
			}
		}
		printf(" ");
	}
	printf("\n");
	for (int l = 0; l < k; l++) {
		for (int i = 0; i < strlen(arr); i++) {
			if (i) printf(" ");
			if (arr[i] == '1' || arr[i] == '2' || arr[i] == '3' || arr[i] == '7') {
				printf(" ");
			} else printf("|");
			for (int j = 0; j < k; j++) {
				printf(" ");
			}
			if (arr[i] == '5' || arr[i] == '6') {
				printf(" ");
			} else printf("|");
			
		}
		printf("\n");
	}
	for (int i = 0; i < strlen(arr); i++) {
		printf(" ");
		if (i) printf(" ");
		for (int j = 0; j < k; j++) {
			if (arr[i] == '1' || arr[i] == '7' || arr[i] == '0') {
				printf(" ");
			} else printf("-");
		}
		printf(" ");
	}
	printf("\n");
	for (int l = 0; l < k; l++) {
		for (int i = 0; i < strlen(arr); i++) {
			if (i) printf(" ");
			if (arr[i] == '2' || arr[i] == '6' || arr[i] == '8' || arr[i] == '0') {
				printf("|");
			} else printf(" ");
			for (int j = 0; j < k; j++) {
				printf(" ");
			}
			if (arr[i] == '2') {
				printf(" ");
			} else printf("|");
			
		}
		printf("\n");
	}
	for (int i = 0; i < strlen(arr); i++) {
		printf(" ");
		if (i) printf(" ");
		for (int j = 0; j < k; j++) {
			if (arr[i] == '1' || arr[i] == '4' || arr[i] == '7') {
				printf(" ");
			} else printf("-");
		}
		printf(" ");
	}
	printf("\n");
	return 0;
}
