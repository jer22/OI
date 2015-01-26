/*
PROG: betsy
LANG: C++
*/
 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
/*
终点和起点间连一条“[”形的边，将哈密顿路转换成哈密顿回路，就不需要独立插头和一大堆繁琐的判断了
再将棋盘顺时针旋转90度，更加简化了问题
 
0 #
1 (
2 )
3 附加数据，无实意
*/
 
long a[330]; // 合法状态
int brk[330][8] /* 匹配括号 */, br[8], tot = 0;
long f[8][66000]; // 当前行第i个格子，状态集合为S的合法状态总数，可以压成f[8][400]，懒得压了
int n;
 
int j, k, p, q;
long i, m, x;
 
int main() {
    freopen("betsy.in", "rt", stdin);
    // freopen("betsy.out", "wt", stdout);
    scanf("%d", &n);
    
    if (n == 1) {
        printf("1\n");
        return 0;
    }
    m = 1 << ((n + 1) << 1);
    for (i = 0; i < m; ++i) {
        for (x = i, k = 0, j = 0; j <= n; ++j, x >>= 2) {
            if ((x & 3) == 1) br[k++] = j;
            else if ((x & 3) == 2)
                if (k--) brk[tot][j] = br[k], brk[tot][br[k]] = j;
                else break;
            else if ((x & 3) == 3) {
                k = -1;
                break;
            }
        }
        if (!k) a[tot++] = i;
    }

    memset(f, 0, sizeof f), f[n][1 | (2 << ((n - 1) << 1))] = 1;
    for (m = 0, k = 1; k <= n; ++k) {
        for (i = 0; i < tot; ++i) f[0][a[i]] = a[i] & 3 ? 0 : f[n][a[i] >> 2]; // 第0格，第一个插头必然不存在，状态最后一位必须为0
        for (i = 1, x = 0; i <= n; ++i, x += 2) {
            memset(f[i], 0, sizeof f[i]);
            for (j = 0; j < tot; ++j) {
                p = (a[j] >> x) & 3, q = (a[j] >> (x + 2)) & 3;
                if (!p && !q) f[i][a[j] | (9 /* (21)4 */ << x)] += f[i - 1][a[j]]; // ## -> ()
                else if (p && q) {
                    if (p == q)
                        if (p == 1) f[i][a[j] ^ (5 /* 11 */ << x) ^ (3 /* 2 -> 1 */ << (brk[j][i] << 1))] += f[i - 1][a[j]]; // ((...)) -> ##...()
                        else f[i][a[j] ^ (10 /* 22 */ << x) ^ (3 /* 1 -> 2 */ << (brk[j][i - 1] << 1))] += f[i - 1][a[j]]; // ((...)) -> ()...##
                    else
                        if (p == 1) {
                            
                            if (k == n && i == n /* 在右下角 */ && a[j] == (9 << x) /* 只有一条回路 */) m += f[i - 1][a[j]]; // () -> ##
                        } else f[i][a[j] ^ (6 /* 12 */ << x)] += f[i - 1][a[j]]; // )( -> ##
                } else {
                    f[i][a[j]] += f[i - 1][a[j]]; // 拐弯向右
                    f[i][a[j] ^ (p << x) ^ (q << (x + 2)) | (p << (x + 2)) | (q << x)] += f[i - 1][a[j]]; // 垂直向下  #( -> (# 依此类推
                }
            }
        }
    }
 
    printf("%ld\n", m);
    return 0;
}