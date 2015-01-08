#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
long long ans;
int n;
char s[1000005];
int nex[1000005];
int cnt[1000005];
void getNext() {
	int i = 0, j = -1;
	int lens = strlen(s);
	nex[0] = -1;
	cnt[0] = 0;
	int flag=0;
	while (i != lens) {
		if (j == -1 || s[i] == s[j])
		{
			nex[++i] = ++j;
		}
		else
		{
			j = nex[j];
			continue;
		}
		cnt[i]=cnt[j] + 1;
	}
}

void getNext2() {
	int i = 0, j = -1;
	int tt = -1;
	int lens = strlen(s);
	nex[0] = -1;
	int flag=0;
	while (i != lens) {
		if (j == -1 || s[i] == s[j])
			{
				i++;
				j++;
			}
		else {
				j = nex[j];
				continue;
			}
		while (j>i/2) j=nex[j];
		ans*=cnt[j]+1;
		ans%=1000000007;
	}
}

long long getNum(int i) {
	long long ans = 0ll;
	int x = i;
	while (nex[x] > i / 2) {
		x = nex[x];
	}
	while (nex[x] >= 1) {
		ans++;
		x = nex[x];
	}
	return ans;
}

int main() {
	//freopen("3670.in","r",stdin);
	scanf("%d", &n);
	while (n--) {
		scanf("%s", s);
		getNext();
		ans = 1ll;
		int lens = strlen(s);
		// for (int i = 1; i <= lens; i++) {
		// 	ans *= (getNum(i) + 1);
		// 	ans %= 1000000007;
		// }
		getNext2();
		cout << ans << endl;
	}


	return 0;
}