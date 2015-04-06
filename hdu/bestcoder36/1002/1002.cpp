#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

int n, m;
int arr[1000010];
int shu[1000010];
int num[1000010];
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

void add(int i)
{
    int j=i;
    i=i%1000007;
    while (shu[i]!=0 && shu[i]!=j)
    {
        i=(i+1)%1000007;
    }
    shu[i]=j;
    num[i]++;
    return;
}
int find(int i)
{
    int j=i;
    i=i%1000007;
    while (shu[i]!=0 && shu[i]!=j)
    {
        i=(i+1)%1000007;
    }
    int t=num[i];
    num[i]=0;
    return t;
} 

int main() {
	freopen("1002.in", "r", stdin);
	freopen("1002.out", "w", stdout);
    while (~scanf("%d %d", &n, &m)) {
        memset(num, 0, sizeof(num));
        memset(shu, 0, sizeof(shu));
        int t;
        for (int i=1;i<=n;i++)
        {
            arr[i]=read();
            add(arr[i]);
        }
        int h;
        for (int i=1;i<=m;i++)
        {
            h=read();
            printf("%d\n",find(h));
        }
    }
    return 0;
}