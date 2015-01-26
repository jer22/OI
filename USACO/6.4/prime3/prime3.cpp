

/*
ID: shijiey1
PROG: prime3
LANG: C++
*/
 
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
 
using namespace std;
 
#define FOR(x,b,e) for (x=b; x<=e; x++)
#define NUM(a1,a2,a3,a4,a5) (a1*10000+a2*1000+a3*100+a4*10+a5)
#define NEND(x) ((x)%2==0 || (x)==5)
 
ofstream fout ("prime3.out");
ifstream fin ("prime3.in");
 
int SUM, BEG;
int a[6][6];
int rec[500][25], recn=0;
bool prime[100000];
int  c[5000], cn=0;
bool h[100000] = {false};
 
int  getsum(int x){
    return x%10 + (x/10)%10 + (x/100)%10 + (x/1000)%10 + x/10000;
}
void gen_prime(){
    memset(prime, true, sizeof(prime));
    for (int i=2; i<100000; i++)
        if (prime[i])
            for (int j=i*2; j<100000; j+=i) prime[j]=false;
 
    for (int i=10001; i<100000; i++)
        if (prime[i] && getsum(i)==SUM){
            c[cn++] = i;
            h[i/10]   = true;
            h[i/100]  = true;
            h[i/1000] = true;
        }
}
 
void record(){
    for (int i=0; i<5; i++)
        for (int j=0; j<5; j++)
            rec[recn][i*5+j] = a[i+1][j+1];
    recn++;
}
bool comp(int x, int y){
    int i;
    for (i=0; rec[x][i]==rec[y][i]; i++);
    if (i == 25) return true;
    return rec[x][i]<=rec[y][i];
}
void Swap(int x, int y){
    int t[25];
    for (int i=0; i<25; i++) t[i] = rec[x][i];
    for (int i=0; i<25; i++) rec[x][i] = rec[y][i];
    for (int i=0; i<25; i++) rec[y][i] = t[i];
}
void output(){
    if (recn == 0) {fout<<"NONE"<<endl; return;}
    // sort
    for (int i=0; i<recn; i++)
        for (int j=i+1; j<recn; j++)
            if (!comp(i, j)) Swap(i, j);
 
    for (int k=0; k<recn; k++){
        for (int i=0; i<25; i++){
            if (i%5 == 0 && i > 0) fout<<endl;
            fout<<rec[k][i];
        }
        fout<<endl;
        if (k != recn-1) fout<<endl;
    }
}
 
int n=0, m=0;
void solve()//枚举，down-right, right row, line1, line2, line 3, line4
{
    int t;
    a[1][1] = BEG;
    FOR(a[2][2],0,9) FOR(a[3][3],0,9) FOR(a[4][4],0,9){// down-right
        a[5][5] = SUM - a[1][1] - a[2][2] - a[3][3] - a[4][4];
        if (a[5][5]<0 || a[5][5]>9 || NEND(a[5][5])) continue;
        t = NUM(a[1][1], a[2][2], a[3][3], a[4][4], a[5][5]);
        if (!prime[t]) continue;
 
        FOR(a[4][5],1,9) FOR(a[3][5],1,9) FOR(a[2][5],1,9){// right row
            if (NEND(a[4][5]) || NEND(a[3][5]) || NEND(a[2][5])) continue;
            a[1][5] = SUM - a[5][5] - a[4][5] - a[3][5] - a[2][5];
            if (a[1][5]<0 || a[1][5]>9 || NEND(a[1][5])) continue;
            t = NUM(a[1][5], a[2][5], a[3][5], a[4][5], a[5][5]);
            if (!prime[t]) continue;
 
            FOR(a[1][2],1,9) FOR(a[1][3],1,9){// line 1
                a[1][4] = SUM - a[1][1] - a[1][2] - a[1][3] - a[1][5];
                if (a[1][4]<1 || a[1][4]>9) continue;
                t = NUM(a[1][1], a[1][2], a[1][3], a[1][4], a[1][5]);
                if (!prime[t]) continue;
 
                FOR(a[2][1],1,9) FOR(a[2][3],0,9){// line 2
                    a[2][4] = SUM - a[2][1] - a[2][2] - a[2][3] - a[2][5];
                    if (a[2][4]<0 || a[2][4]>9) continue;
                    t = NUM(a[2][1], a[2][2], a[2][3], a[2][4], a[2][5]);
                    if (!prime[t]) continue;
 
                    FOR(a[3][1],1,9) FOR(a[3][2],0,9){
                        a[3][4] = SUM - a[3][1] - a[3][2] - a[3][3] - a[3][5];
                        if (a[3][4]<0 || a[3][4]>9) continue;
                        t = NUM(a[3][1], a[3][2], a[3][3], a[3][4], a[3][5]);
                        if (!prime[t]) continue;
 
                        // cut
                        n++;
                        if (!h[a[1][1]*100+a[2][1]*10+a[3][1]]){m++; continue;}
                        if (!h[a[1][2]*100+a[2][2]*10+a[3][2]]){m++; continue;}
                        if (!h[a[1][3]*100+a[2][3]*10+a[3][3]]){m++; continue;}
                        if (!h[a[1][4]*100+a[2][4]*10+a[3][4]]){m++; continue;}
                        //if (!h[a[1][5]*100+a[2][5]*10+a[3][5]]){m++; continue;}
 
                        FOR(a[4][1],1,9) FOR(a[4][2],0,9){
                            a[4][3] = SUM - a[4][1] - a[4][2] - a[4][4] - a[4][5];
                            if (a[4][3]<0 || a[4][3]>9) continue;
                            t = NUM(a[4][1], a[4][2], a[4][3], a[4][4], a[4][5]);
                            if (!prime[t]) continue;
 
                            a[5][1] = SUM - a[1][1] - a[2][1] - a[3][1] - a[4][1];
                            if (a[5][1]<1 || a[5][1]>9) continue;
                            t = NUM(a[1][1], a[2][1], a[3][1], a[4][1], a[5][1]);
                            if (!prime[t]) continue;
                            t = a[5][1] + a[4][2] + a[3][3] + a[2][4] + a[1][5];
                            if (t != SUM) continue;
                            t = NUM(a[5][1], a[4][2], a[3][3], a[2][4], a[1][5]);
                            if (!prime[t]) continue;
 
                            a[5][2] = SUM - a[1][2] - a[2][2] - a[3][2] - a[4][2];
                            if (a[5][2]<0 || a[5][2]>9) continue;
                            t = NUM(a[1][2], a[2][2], a[3][2], a[4][2], a[5][2]);
                            if (!prime[t]) continue;
 
                            a[5][3] = SUM - a[1][3] - a[2][3] - a[3][3] - a[4][3];
                            if (a[5][3]<0 || a[5][3]>9) continue;
                            t = NUM(a[1][3], a[2][3], a[3][3], a[4][3], a[5][3]);
                            if (!prime[t]) continue;
 
                            a[5][4] = SUM - a[1][4] - a[2][4] - a[3][4] - a[4][4];
                            if (a[5][4]<0 || a[5][4]>9) continue;
                            t = NUM(a[1][4], a[2][4], a[3][4], a[4][4], a[5][4]);
                            if (!prime[t]) continue;
 
                            t = NUM(a[5][1], a[5][2], a[5][3], a[5][4], a[5][5]);
                            if (!prime[t]) continue;
 
                            record();
                        }
 
                    }
 
                }
 
            }
 
        }
 
    }
}
 
int main()
{
    fin>>SUM>>BEG;
 
    gen_prime();
 
    solve();
 
    output();
 
    cout<<n<<" "<<m<<endl;
 
    //system("pause");
    return 0;
}