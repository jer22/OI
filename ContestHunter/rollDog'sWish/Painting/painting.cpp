

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 1000000000000000000

using namespace std;

int n, k;
int cntA, cntB;
long long edges[100][100];
long long A[100], B[100];
bool visA[100], visB[100];
int mat[100];
long long d;

bool dfs(int i) {
    visA[i] = 1;
    for (int j = 1; j <= n * n; j++) {
        if (!visB[j]) {
            long long t = edges[i][j] - A[i] - B[j];
            if (!t) {
                visB[j] = 1;
                if (!mat[j] || dfs(mat[j])) {
                    mat[j] = i;
                    return true;
                }
            } else d = min(d, t);
        }
    }
    return false;
}

int match1() {
    memset(B, 0, sizeof(B));
    for (int i = 1; i <= n; i++) {
        A[i] = -INF;
        // A[i] = INF;
        for (int j = 1; j <= n; j++)
            // A[i] = min(A[i], edges[i][j]);
            A[i] = max(A[i], edges[i][j]);
    }
    memset(mat, 0, sizeof(mat));
    for (int i = 1; i <= n; i++) {
        while (true) {
            memset(visA, 0, sizeof(visA));
            memset(visB, 0, sizeof(visB));
            d = INF;
            if (dfs(i)) break;
            for (int j = 1; j <= n; j++)
                if (visA[j])
                    // A[j] += d;
                    A[j] -= d;
            for (int j = 1; j <= n; j++)
                if (visB[j])
                    // B[j] -= d;
                    B[j] += d;
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += edges[mat[i]][i];
    return ans;
}

long long match2() {
    memset(B, 0, sizeof(B));
    for (int i = 1; i <= n; i++) {
        A[i] = INF;
        // A[i] = -INF;
        for (int j = 1; j <= n; j++)
            // A[i] = max(A[i], edges[i][j]);
            A[i] = min(A[i], edges[i][j]);
    }
    memset(mat, 0, sizeof(mat));
    for (int i = 1; i <= n; i++) {
        while (true) {
            memset(visA, 0, sizeof(visA));
            memset(visB, 0, sizeof(visB));
            d = INF;
            if (dfs(i)) break;
            for (int j = 1; j <= n; j++)
                if (visA[j])
                    A[j] += d;
                    // A[j] -= d;
            for (int j = 1; j <= n; j++)
                if (visB[j])
                    B[j] -= d;
                    // B[j] += d;
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += edges[mat[i]][i];
    return ans;
}

long long gg[105][105];
long long hh[105][105];
int main() {
    freopen("painting.in", "r", stdin);
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%lld", &gg[i][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%lld", &hh[i][j]);
                edges[i][j] = hh[i][j] * gg[i][j];
            }
        }

        long long ans1 = match1();
        // match2();
        long long ans2 = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
               ans2 += gg[i][j] * hh[i][j];
            }
        }

        if (ans1 < ans2) printf("No\n");
        if (ans1 == ans2) printf("Equal\n");
        if (ans1 > ans2) printf("Yes\n");
    }
    return 0;
}