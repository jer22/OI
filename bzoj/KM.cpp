#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x7fffffff

using namespace std;

int n, m;
int cntA, cntB;
int edges[100][100];
int A[100], B[100];
bool visA[100], visB[100];
int mat[100];
int d;

bool dfs(int i) {
    visA[i] = 1;
    for (int j = 1; j <= n * m; j++) {
        if (!visB[j]) {
            int t = edges[i][j] - A[i] - B[j];
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

int match() {
    memset(B, 0, sizeof(B));
    for (int i = 1; i <= n; i++) {
        A[i] = INF; // A[i] = -INF;
        for (int j = 1; j <= m; j++)
            A[i] = min(A[i], edges[i][j]); // A[i] = max(A[i], edges[i][j])
    }
    memset(mat, 0, sizeof(mat));
    for (int i = 1; i <= n; i++) {
        while (true) {
            memset(visA, 0, sizeof(visA));
            memset(visB, 0, sizeof(visB));
            d = INF;
            if (dfs(i)) break;
            for (int j = 1; j <= n; j++)
                if (visA[j]) A[j] += d;  //A[j] -= d;
            for (int j = 1; j <= m; j++)
                if (visB[j]) B[j] -= d;  //B[j] += d;
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans += edges[mat[i]][i];
    return ans;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d %d", &n, &m);
        int t;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &edges[i][j]);
            }
        }
        int ans = match();
        printf("%d\n", ans);
    }
    return 0;
}