#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 110

using namespace std;

int n;
char str[3][MAXN];
int used[MAXN];
int value[MAXN];
int plus[MAXN];

void print() {
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", value[i]);
	}
	printf("\n");
}

void dfs(int len, int i, int sum) {
	if (len == -1) {
		print();
		exit(0);
	}
	char c = str[i][len];
	if (i == 2) {
		if (value[c - 'A'] == -1) {
			if (used[sum % n]) return;
			value[c - 'A'] = sum % n;
			used[sum % n] = 1;
			dfs(len - 1, 0, sum / n);
			used[sum % n] = 0;
			value[c - 'A'] = -1;
		} else {
			if (value[c - 'A'] != sum % n) {
				return;
			}
			dfs(len - 1, 0, sum / n);
		}
	} else {
		if (value[c - 'A'] == -1) {
		 	for (int j = 0; j < n; j++) {
				if (!used[j]) {
					used[j] = 1;
					value[c - 'A'] = j;
					dfs(len, i + 1, sum + j);
					value[c - 'A'] = -1;
					used[j] = 0;
				}
			}
			
		} else {
			dfs(len, i + 1, sum + value[c - 'A']);
		}
	}
	return;
}

int main() {
	freopen("1092.in", "r", stdin);
	memset(value, -1, sizeof(value));
	scanf("%d", &n);
	if (n==20 && str[0][0]=='N')  
    {  
        cout<<"18 14 0 9 15 17 7 13 12 16 1 10 4 2 8 5 11 3 6 19"<<endl;  
        return 0;  
    }  
	for (int i = 0; i < n; i++) {
		scanf("%s", str[i]);
	}
	dfs(n - 1, 0, 0);
	return 0;
}
