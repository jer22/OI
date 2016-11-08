#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for(int i=0;i<(n);++i)
#define rep(i,n) for(int i=1;i<=(n);++i)
#define pii pair<int,int> 
#define mp make_pair
typedef long long ll;
typedef long long ui;
struct Node{
    Node *s[2],*f,*loop;
    int rt;
    void init(){
        s[0]=s[1]=f=NULL;
        rt=1;
        loop=NULL;
    }
    Node *link(int lr,Node *q){
        s[lr]=q;
        if(q)q->f=this;
        return this;
    }
}lct[200005];
void Rotate(Node *p){
    Node *q=p->f;
    p->f=q->f;
    int lr=q->s[1]==p;
    p->link(!lr,q->link(lr,p->s[!lr]));
    if(q->rt) swap(p->rt,q->rt);
    else p->f->s[p->f->s[1]==q]=p;
}
void Splay(Node *p){
    while(!p->rt){
        Node *f=p->f,*ff=f->f;
        if(f->rt){
            Rotate(p);
        }
        else if((f->s[0]==p)==(ff->s[0]==f))
            Rotate(f),Rotate(p);
        else
            Rotate(p),Rotate(p);
    }
}
Node * Access(Node *p){
    Node *q=NULL;
    do{
        Splay(p);
        if(p->s[1])p->s[1]->rt=1;
        if(p->s[1]=q)q->rt=0;
        p=(q=p)->f;
    }while(p);
    return q;
}
void checkLoop(Node *p){
    while(p->f)p=p->f;
    Node *rt=p;
    while(p->s[0])p=p->s[0];
    if(!p->loop)return;

    Node *loop=p->loop;
    while(loop->f)loop=loop->f;    
    if(!rt->rt)printf("%d",*(int *)NULL); 
    if(loop!=rt){
        rt->f=p->loop;
        p->loop=NULL;
    }
}
void cut(Node *p){
    Splay(p);
    if(p->loop){
        p->loop=NULL;
        return;
    }
    Node *q=p->s[0];
    if(q){
        while(q->s[1])q=q->s[1];
    }
    else{
        q=p->f;
    }
    if(q==NULL)return;

    Access(q);
    Splay(p);
    if(p->s[0])printf("%d",*(int *)NULL);
    p->f=NULL;
    
    checkLoop(q);
    if(p->f)printf("%d",*(int *)NULL);    
}
void SetCall(Node *u,Node *v){
    cut(u);
    if(u->f)printf("%d",*(int *)NULL);
    Node *p=v;
    while(p->f)p=p->f;
    if(p==u){
        u->loop=v;
    }
    else{
        u->f=v;
    }
}
Node *getCall(Node *u){
    Access(u);
    Splay(u);
    while(u->s[0])u=u->s[0];
    if(u->loop)return NULL;
    return u;
}
void solve(){
    int n,m;
    cin>>n>>m;
    rep(i,n)lct[i].init();

    rep(i,n){
        int a;
        scanf("%d",&a);
        if(a)SetCall(lct+i,lct+a);
    }

    forn(i,m){
        int cmd;
        scanf("%d",&cmd);
        //if(clock()>CLOCKS_PER_SEC)exit(0);
        if(cmd==1){
            int x,y;
            scanf("%d%d",&x,&y);
            if(y) SetCall(lct+x,lct+y);
            else cut(lct+x);
        }
        else{
            int x;
            scanf("%d",&x);
            Node *p=getCall(lct+x);
            printf("%d\n",(int)(p?p-lct:-1));
        }        
    }
}

int main()
{
    freopen("5967.in","r",stdin);
    // freopen("std.out", "w", stdout);
    solve();
    return 0;
}
