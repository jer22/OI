#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Num{
	int num[55], len;
	void init(int i) {
		memset(num, 0, sizeof(num));
		len = 1;
		num[0] = i;
	}
	void print() {  
        for (int i = len - 1; i >= 0; i--) {  
            printf("%d", num[i]);  
        }  
        printf("\n");  
    }  
};

Num operator + (Num a, Num b) {
	Num c;  
    memset(c.num, 0, sizeof(c.num));  
    c.len = max(a.len, b.len);  
    for (int i = 0; i < c.len; i++) {  
        c.num[i] += a.num[i] + b.num[i];  
        c.num[i + 1] += c.num[i] / 10;  
        c.num[i] %= 10;  
    }  
    if (c.num[c.len]) c.len++;  
    return c;  
}

int n, K;
int arr[105];
Num dp[105][105];
int main() {
	freopen("a.in", "r", stdin);
	while (~scanf("%d %d", &n, &K)) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i <= n; i++)
			dp[i][1].init(1);
		// dp[1][1] = 1;
		for (int k = 2; k <= K; k++) {
			for (int i = k; i <= n; i++) {
				for (int j = k - 1; j < i; j++) {
					if (arr[i] > arr[j]) {
						dp[i][k] = dp[i][k] + dp[j][k - 1];
					}
				}
			}
		}
		Num ans;
		ans.init(0);
		// cout << dp[3][2] << endl;
		for (int i = K; i <= n; i++) {
			// ans.print();
			ans = ans + dp[i][K];
		}
		ans.print();
	}


	return 0;
}
