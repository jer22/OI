#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>
#include <set>

#define INF 0x7fffffff

using namespace std;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		return x < p.x;
	}
};

int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int d, n, m;
map<int, bool> p;
int main() {
	freopen("mht.in", "r", stdin);
	int data;
	scanf("%d", &data);
	cin >> d >> n >> m;
	int x, y, z;
	long long cnt = 0;
	for (int k = 0; k < n; k++) {
		x = read();
		y = read();
		
		for (int i = x - y; i <= x + y; i++) {
			p[i] = 1;
		}
	}
	int ans = 0;
	for (int i = -m; i <= m; i++)
		if (p[i]) ans++;
	printf("%d\n", ans);
	// cout << p.size();
	return 0;
}
