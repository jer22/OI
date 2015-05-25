#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

const int MAXN = 100005;

int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int n, m;
int arr[MAXN];
map<int, int> first;
map<int, int> last;
int nex[MAXN];
int main() {
	freopen("1002.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		int x;
		first.clear();
		memset(nex, 0, sizeof(nex));
		last.clear();
		for (int i = 1; i <= n; i++) {
			arr[i] = read();
			if (!first[arr[i]]) first[arr[i]] = i;
			else {
				nex[last[arr[i]]] = i;
			}
			last[arr[i]] = i;
		}
		for (int i = 0; i < m; i++) {
			x = read();
			if (!first[x]) printf("-1\n");
			else {
				printf("%d\n", first[x]);
				first[x] = nex[first[x]];
			}
		}
	}


	return 0;
}
