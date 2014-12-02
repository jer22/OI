#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

/**
	伸展树节点

	value: 节点保存的值
	left: 左子树
	right: 右子树
*/
struct SplayNode {
	int value;
	SplayNode *left;
	SplayNode *right;
};

/**
	右旋

	@param k: 当前顶点
	@return k1: 新顶点
*/
SplayNode * rotateRight(SplayNode *k) {
	// 将k的左子树作为新的顶点
	SplayNode *k1 = k -> left;
	// 将原左子树的右子树移到k的左子树
	k -> left = k1 -> right;
	// k作为新树的右子树
	k1 -> right = k;
	return k1;
}

/**
	左旋

	@param k: 当前顶点
	@return k1: 新顶点
*/
SplayNode * rotateLeft(SplayNode *k) {
	// 将k的右子树作为新顶点
	SplayNode *k1 = k -> right;
	// 将原右子树的左子树作为k的右子树
	k -> right = k1 -> left;
	// k作为新树的左子树
	k1 -> left = k;
	return k1;
}

/**
	伸展操作

	将伸展树T中值与value最近的节点调整至树的根部
	@param T：伸展树指针
	@param value：元素的值
	@return T：新树的根
*/
SplayNode * splay(SplayNode *T, int value) {
	// header为左树与右树的根
	static SplayNode header;
	header.left = header.right = NULL;
	// 左树，右树
	// 右树的所有值都比T大，左树的所有值都比T小
	// 左树与右树都是伸展树
	SplayNode *leftTree, *rightTree;
	leftTree = rightTree = &header;

	// 直到找到value或树空
	while (T != NULL && value != T -> value) {
		// 当value小于T的值，说明value在T的左子树中
		if (value < T -> value) {
			if (T -> left == NULL) { break; }
			// 当value小于T的左子树的值，说明value在T的左子树的左子树中
			// 即zig-zig
			if (value < T -> left -> value) {
				// 右旋
				T = rotateRight(T);
			}
			if (T -> left == NULL) { break; }
			// 右连接
			// 即将T与T的右子树连接到rightTree的左子树上
			// T的左子树作为新的T的根
			rightTree -> left = T;
			// rightTree的左子树，即移过来T，将作为新的rightTree
			// 但是注意此时T的左子树并未删去，
			// 因为下一次的右连接操作将会连接到移过来T的左子树，
			// 覆盖掉原来的左子树
			rightTree = T;
			T = T -> left;
		}
		// 否则说明value在T的右子树中
		else {
			if (T -> right == NULL) { break; }
			// 说明value在T的右子树的右子树中
			// 即zig-zig
			if (value > T -> right -> value) {
				// 左旋
				T = rotateLeft(T);
			}
			if (T -> right == NULL) { break; }
			// 左连接
			leftTree -> right = T;
			leftTree = T;
			T = T -> right;
		}
		/*
			此时还原树，做法如下：
			将leftTree作为T的左子树，rightTree作为T的右子树
			T的原左子树作为leftTree的右子树，原右子树作为rightTree的左子树
		*/
		// 将T的左子树连接到leftTree的右子树，同时覆盖掉未删去的右子树
		leftTree -> right = T -> left;
		// 将T的右子树连接到rightTree的左子树，同时覆盖掉未删去的左子树
		rightTree -> left = T -> right;
		// header.right即为最初的leftTree，即整棵leftTree
		T -> left = header.right;
		// header.left即为整棵rightTree
		T -> right = header.left;
		return T;
	}
}

/**
	插入操作

	将一个值插入树中
	@param T 树
	@param value 待插入的值
	@return 新树的根
*/
SplayNode * insert(SplayNode *T, int value) {
	// 新节点
	static SplayNode* newNode = NULL;

	if (newNode == NULL) {
		newNode = new SplayNode;
	}
	newNode -> value = value;

	// 当T是空树，就返回newNode
	if(T == NULL) {
		newNode -> left = newNode -> right = NULL;
		T = newNode;
	}
	// 否则
	else {
		// 当value小于T的值，即应将value插入到T的左子树
		if (value < T -> value) {
			// 将T的左子树连接到newNode的左子树
			newNode -> left = T -> left;
			// newNode的右子树为T与T的右子树
			newNode -> right = T;
			T -> left = NULL;
			// newNode将作为新的树根
			T = newNode;
		}
		// 当value大于T的值，即应将value插入到T的右子树
		else if (value > T -> value) {
			// 将T的右子树连接到newNode的右子树
			newNode -> right = T -> right;
			// newNode的左子树为T与T的左子树
			newNode -> left = T;
			T -> right = NULL;
			// newNode将作为新的树根
			T = newNode;
		}
		// 否则说明value以存在于T中
		else {
			// 销毁newNode
			delete newNode;
		}
	}
	newNode = NULL;
	return T;
}

/**
	删除操作

	将指定节点删除
	@param T：树
	@param value：要删除的节点的值
	@return：新树
*/
SplayNode * remove(SplayNode *T, int value) {
	// 新树
	SplayNode * newTree;
	// 如果T非空
	if (T != NULL) {
		// 将指定节点调整至树根
		T = splay(T, value);
		// 当该节点为要删除的节点
		// 如果不是，说明要删除的节点不再树中
		if (value == T -> value) {
			// 如果T的左子树为空，则新树为T的右子树
			if (T -> left == NULL) { newTree = T -> right; }
			// 否则
			else {
				// 先将T的左子树作为新树
				newTree = T -> left;
				// 此时value比newTree中的所有节点都大，
				// 所以此次伸展将进行多次左旋，使newTree的右子树为空
				newTree = splay(newTree, value);
				// 将T的右子树作为newTree的右子树
				newTree -> right - T -> right;
			}
			// 销毁原来的T
			delete T;
			// newTree作为T将被返回
			T = newTree;
		}
	}
	return T;
}

/**
	删除所有节点
*/
void removeAll(SplayNode * T) {
	if (T != NULL) {
		removeAll(T -> left);
		removeAll(T -> right);
		delete T;
	}
}

void print(SplayNode * T) {
	if(T == NULL)
		return;
	print(T -> left);
	printf("%d\n", T -> value);
	print(T -> right);
}

SplayNode * tree = NULL;
int main( void ) {
	int a;
	for (int i = 0; i < 10; i++) {
		scanf("%d", &a);
		tree = insert(tree, a);
		print(tree);
	}

	return 0;
}
