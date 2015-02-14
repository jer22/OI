#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node{
	int num, pos;
	bool operator < (const Node &n) const {
		if (num != n.num)
			return num < n.num;
		else return pos < n.pos;
	}
};

int arr[10005];
int vis[505][505];
vector<Node> v;
void fuck(int i,int j,int now)
{
	if (vis[i][j]==1) return;
	cout<<i<<' '<<j<<' '<<now<<endl;
	vis[i][j]=1;
}
int main() {
	freopen("nm10.in", "r", stdin);
	freopen("10.out", "w", stdout);
	int n, k, p,num=0;
	scanf("%d %d %d", &n, &k, &p);
	printf("%d %d %d\n", n, p, k);

	int pre=0,now=1;
	for (int i = 1; i <= p; i++) {
		cin >> arr[i];
		pre++;
		if (pre!=1) fuck(arr[i-1],arr[i],);
		else fuck(now,arr[i],now);
		if (arr[i]==now)
		{
			now++;
			continue;
		}
	}
	return 0;
}
