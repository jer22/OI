#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int t;

int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int main() {
	freopen("e.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int a = 0;
		for (int i = 0; i < n; i++) {
			t = read();
			a ^= t;
		}
		if (a) {
			printf("Win\n");
		} else {
			printf("Lose\n");
		}
	}


	return 0;
}
