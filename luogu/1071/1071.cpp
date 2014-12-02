#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char secret[110];
char original[110];
char request[110];
char encrypt[26];
int exist[26];
int main( void ) {
	freopen("1071.in", "r", stdin);
	scanf("%s%s%s", secret, original, request);
	for (int i = 0; i < strlen(original); i++) {
		exist[original[i] - 65] = 1;
	}
	for (int i = 0; i < 26; i++) {
		if (!exist[i]) {
			printf("Failed\n");
			exit(0);
		}
	}
	for (int i = 0; i < strlen(original); i++) {
		if (!encrypt[secret[i] - 65]) {
			encrypt[secret[i] - 65] = original[i];
		} else {
			if (encrypt[secret[i] - 65] != original[i]) {
				printf("Failed\n");
				exit(0);
			}
		}
	}
	for (int i = 0; i < strlen(request); i++) {
		printf("%c", encrypt[request[i] - 65]);
	}

	return 0;
}
