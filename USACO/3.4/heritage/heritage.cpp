/*
ID:shijiey1
PROG:heritage
LANG:C++
*/

/*
已知树的前序，中序遍历，求后序遍历。
中序遍历(in)：左-根-右
前序遍历(pre)：根-左-右
后序遍历(post)：左-右-根
可以发现，整棵树的根，在前序遍历的第一个字符，也是后序遍历的最后一个字符'R'

	  l1   l2
in:  ----R***
	   l1  l2
pre: R----***
	  l1  l2
post:----***R

先把后序遍历的最后一位R，然后再在中序遍历里找到了R，可以发现中序遍历里，R的左边都是树的左子树，R的右边都是树的右子树。
我们记下左子树和右子树的长度（l1, l2），然后在前序遍历里从R的后一位开始，长为l1的前半段为左子树，长为l2的后半段为右子树，
从后序遍历的第1位开始，长为l1的前半段为左子树，长为l2的后半段为右子树。
然后分别递归处理左子树与右子树，这里以左子树为例：

in:  --C-

pre:  C---

post:---C
当前递归到的树的前序遍历的第一个字符'C'即为该树的根，先将它填道后序遍历的最后一位。
然后在中序遍历里找到C，则C之前长度为2的串就是该树的左子树的中序遍历，C之后长度为1的串就是该树的右子树的中序遍历。
然后在前序和后序里分别划出长度为2和1的串，递归处理。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int cnt = 0;
int pre[29];
int in[29];
int post[29];
int n = 0;

// 递归到的子树的中序遍历在原树的中序遍历中的位置：[in1, in2]
// 前序后序同理
void dfs(int in1, int in2, int pre1, int pre2, int post1, int post2) {
	// 将后序遍历的最后一位填为前序遍历的第一位
	post[post2] = pre[pre1];
	int w1;
	// 找到该字符在中序遍历里的位置
	for (int i = in1; i <= in2; i++) {
		if (in[i] == pre[pre1]) {
			w1=i;
			break;
		}
	}

	// 左子树的长度
	int len=w1-in1;
	// 有左子树（长度不为0）
	if (len!=0) {
		dfs(in1,in1+len-1,pre1+1,pre1 + len, post1, post1 + len - 1);
	}
	// 有右子树
	if (len != in2 - in1) {
		dfs(w1 + 1, in2, pre1 + len + 1, pre2, post1 + len, post2 - 1);
	}

}

int main() {
	freopen("heritage.in", "r", stdin);
	freopen("heritage.out", "w", stdout);
	char c;
	while ((c = getchar()) != '\n') {
		in[n++] = c - 'A' + 1;
	}
	n = 0;
	while ((c = getchar()) != '\n') {
		pre[n++] = c - 'A' + 1;
	}
	dfs(0, n - 1, 0, n - 1, 0, n - 1);
	for (int i = 0; i < n; i++) {
		printf("%c", post[i] + 'A' - 1);
	}
	printf("\n");
	return 0;
}
