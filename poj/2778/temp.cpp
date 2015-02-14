#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;

#define D(x) 

#define MAX_LEN 20
#define MAX_CHILD_NUM 4
#define MAX_NODE_NUM 100005

int st_num, len;
int matrix_size;
int node_cnt;

struct node
{
    node *fail;
    node *next[MAX_CHILD_NUM];
    int count; //how many words are matched when reach this node
}trie[MAX_NODE_NUM], *root = trie;

void ac_init()
{
    memset(trie, 0, sizeof(trie));
    node_cnt = 1;
}

int get_id(char ch)
{
    if (ch == 'A')
        return 0;
    if (ch == 'C')
        return 1;
    if (ch == 'T')
        return 2;
    return 3;
}

void insert(node *root, char *str)
{
    node *p = root;
    int index;
    for (int i = 0; str[i]; i++)
    {
        index = get_id(str[i]);
        if (p->next[index] == NULL)
        {
            p->next[index] = trie + node_cnt;
            node_cnt++;
        }
        p = p->next[index];
    }
    p->count++;
}

void build_ac_automation(node *root)
{
    queue<node*> q;
    int i;
    root->fail = NULL;
    q.push(root);
    while (!q.empty()) {
        node *p = q.front();
        q.pop();
        node *temp = NULL;
        for (i = 0; i < MAX_CHILD_NUM; i++) {
            temp = p->fail;
            while (temp != NULL && temp->next[i] == NULL)
                temp = temp->fail;
            if (p->next[i] != NULL) {
                if (temp == NULL)
                    p->next[i]->fail = root;
                else {
                    p->next[i]->fail = temp->next[i];
                    p->next[i]->count += temp->next[i]->count;
                }
                q.push(p->next[i]);
            } 
            else {
                if (temp == NULL)
                    p->next[i] = root;
                else
                    p->next[i] = temp->next[i];
            }
        }
    }
}

int query(node *root, char* str)
{
    int cnt = 0, index;
    node *p = root;
    for (int i = 0; str[i]; i++)
    {
        index = get_id(str[i]);
        p = p->next[index];
        p = (p == NULL) ? root : p;
        node *temp = p;
        cnt += temp->count;
        //marks count as -1 to prevent from matching again
        while (temp != root && temp->count != -1)
        {
            temp->count = -1;
            temp = temp->fail;
        }
    }
    return cnt;
}

void input()
{
    scanf("%d%d", &st_num, &len);
    for (int i = 0; i < st_num; i++)
    {
        char st[MAX_LEN];
        scanf("%s", st);
        insert(root, st);
    }
}

#define MAX_MATRIX_SIZE 101
#define MOD 100000

struct Matrix
{
    int order;
    int num[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

    Matrix()
    {}

    Matrix(int ord)
    {
        order = ord;
    }

    void init()
    {
        for (int i = 0; i < order; i++)
        {
            for (int j = 0; j < order; j++)
            {
                num[i][j] = 0;
            }
        }
    }
    void output()
    {
        for (int i = 0; i < order; i++)
        {
            for (int j = 0; j < order; j++)
            {
                printf("%d ", num[i][j]);
            }
            puts("");
        }
    }
};

Matrix operator*(Matrix ma, Matrix mb)
{
    int ord = ma.order;
    Matrix numc(ord);
    numc.init();
    int i, j, k;
    for (i = 0; i < ord; i++)
    {
        for (k = 0; k < ord; k++)
        {
            if (ma.num[i][k] == 0)
                continue;
            for (j = 0; j < ord; j++)
            {
                long long temp = ma.num[i][k] * (long long)mb.num[k][j];
                temp %= MOD;
                numc.num[i][j] += temp;
                numc.num[i][j] %= MOD;
                D(printf("%d %d %d\n", i, j, numc.num[i][j]);)
            }
        }
    }
    return numc;
}

Matrix matrix_power(Matrix ma, int x)
{
    int ord = ma.order;
    Matrix numc(ord);
    numc.init();
    for (int i = 0; i < ord; i++)
    {
        numc.num[i][i] = 1;
    }
    for (; x; x >>= 1)
    {
        if (x & 1)
        {
            numc = numc * ma;
        }
        ma = ma * ma;
    }
    return numc;
}

void extract_matrix(Matrix &matrix)
{
    matrix.order = node_cnt;
    matrix.init();
    for (int i = 0; i < node_cnt; i++)
    {
        for (int j = 0; j < MAX_CHILD_NUM; j++)
        {
            if (trie[i].next[j] == NULL)
                continue;
            int temp = trie[i].next[j] - trie;
                // cout << i << ' ' << j << ' ' << temp << endl;
            if (trie[temp].count == 0)
            {
                matrix.num[i][temp] += 1;
                // printf("%d %d\n", i, temp);
            }
        }
    }
}

int main()
{
    freopen("2778.in", "r", stdin);
    ac_init();
    input();
    build_ac_automation(root);
    Matrix matrix;
    extract_matrix(matrix);
    D(matrix.output();)
    Matrix power = matrix_power(matrix, len);
    int ans = 0;
    for (int i = 0; i < node_cnt; i++)
        ans = (ans + power.num[0][i]) % MOD;
    D(power.output();)
    printf("%d\n", ans);
    return 0;
}