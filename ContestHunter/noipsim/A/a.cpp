/**
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <set>
 
using namespace std;
 
const double INF = 1e20;
const int eps = 1e-8;
 
int n;
int arr[2005], temp[2005];
int main() {
    freopen("a.in", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    int mi = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            temp[j] = arr[j];
        int tot = 0;
        for (int j = i - 1; j >= 1; j--) {
            if (temp[j] < temp[j + 1]) {
                tot += temp[j + 1] - temp[j];
                temp[j] = temp[j + 1];
            }
        }
        for (int j = i + 1; j <= n; j++) {
            if (temp[j] > temp[j - 1]) {
                tot += temp[j] - temp[j - 1];
                temp[j] = temp[j - 1];
            }
        }
        mi = min(mi, tot);
        tot = 0;
        for (int j = 1; j <= n; j++)
            temp[j] = arr[j];
        for (int j = i - 1; j >= 1; j--) {
            if (temp[j] > temp[j + 1]) {
                tot += temp[j] - temp[j + 1];
                temp[j] = temp[j + 1];
            }
        }
        for (int j = i + 1; j <= n; j++) {
            if (temp[j] < temp[j - 1]) {
                tot += temp[j - 1] - temp[j];
                temp[j] = temp[j - 1];
            }
        }
        mi = min(mi, tot);
    }
    cout << mi << endl;

    return 0;
}