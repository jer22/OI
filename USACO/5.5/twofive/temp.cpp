/*
ID:shijiey1
LANG:C++
PROG:twofive
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
 
const int SIZE = 26;
const double EPS = 1e-6;
int MAX = 99999999;
 

int nways[6][6][6][6][6];
int maxr[5];
int maxc[5];
bool used[26];
int calc(int a, int b, int c, int d, int e,int l)
{
    int cur = 0;
    if( nways[a][b][c][d][e] )
        return nways[a][b][c][d][e];
 
    if( used[l] )
        return nways[a][b][c][d][e] = calc(a,b,c,d,e,l+1);
 
    if( a < 5 && l > maxr[0] && l > maxc[a] ) cur += calc(a+1,b,c,d,e,l+1);
    if( a > b && l > maxr[1] && l > maxc[b] ) cur += calc(a,b+1,c,d,e,l+1);
    if( b > c && l > maxr[2] && l > maxc[c] ) cur += calc(a,b,c+1,d,e,l+1);
    if( c > d && l > maxr[3] && l > maxc[d] ) cur += calc(a,b,c,d+1,e,l+1);
    if( d > e && l > maxr[4] && l > maxc[e] ) cur += calc(a,b,c,d,e+1,l+1);
 
    return nways[a][b][c][d][e] = cur;
}
int cal(int a[],int n)
{
    memset(nways,0,sizeof(nways));
    memset(maxr,-1,sizeof(maxr));
    memset(maxc,-1,sizeof(maxc));
    memset(used,0,sizeof(used));
    nways[5][5][5][5][5] = 1;
    int in[5] = {0};
    for(int i = 0;i < n;i++)
    {
        int r = i / 5;
        int c = i % 5;
        in[r]++;
        if(a[i] < maxr[r] || a[i] < maxc[c])
            return 0;
        maxr[r] = a[i];
        maxc[c] = a[i];
        used[a[i]] = 1;
    }
    int ans = calc(in[0],in[1],in[2],in[3],in[4],0);
    return ans;
}
int stoa(char s[])
{
    int a[SIZE];
    int ans = 0;
    a[0] = 0;
    bool used[26] = {0};
    used[0] = 1;
    for(int i = 1;i < 25;i++)
    {
        int j;
        for(j = 0;j < s[i] - 'A';j++)
            if(!used[j])
            {
                a[i] = j;
                int temp = cal(a,i+1);
                ans += temp;
            }
        used[j] = 1;
        a[i] = j;
    }
    return ans + 1;
}
void atos(int num,char s[])
{
    int a[SIZE];
    a[0] = 0;
    bool used[26] = {0};
    used[0] = 1;
    s[0] = 'A';
    int now = 0;
    for(int i = 1;i < 25;i++)
    {
        int j;
        for(j = 0;j < 25;j++)
            if(!used[j])
            {
                s[i] = j + 'A';
                a[i] = j;
                int temp = cal(a,i+1);
                if(now + temp >= num)
                    break;
                now += temp;
            }
        used[j] = 1;
    }
    s[25] = '\0';
}
 
int main()
{
    freopen("twofive.in", "r", stdin);
    freopen("twofive.out", "w", stdout);
    string way;
    char s[27];
    int n;
 
    while(cin >> way)
    {
        if(way == "W")
        {
            cin >> s;
            int n = stoa(s);
            cout << n << endl;
        }
        else
        {
            cin >> n;
            atos(n,s);
            cout << s << endl;
        }
    }
    return 0;
}