ll a[N];
ll tree[4*N][2];
void make(int node,int i,int n)
{
    tree[node][1]=0;
    tree[node][0]=0;
    if(i==n)return ;
    make(node*2,i,(i+n)/2);
    make(node*2+1,(i+n)/2+1,n);
}
void lazyup(int node,int i,int n,int l,int r,int val)
{
    if(l<=i&&r>=n)tree[node][1]+=val;
    if(tree[node][1])
    {
        if(i!=n)
        {
            tree[node*2][1]+=tree[node][1];
            tree[node*2+1][1]+=tree[node][1];
        }
        tree[node][0]+=(tree[node][1]*(n-i+1));
        tree[node][1]=0;
    }
    if(n<l||i>r)return ;
    if(l<=i&&r>=n)return ;
    lazyup(node*2,i,(i+n)/2,l,r,val);
    lazyup(node*2+1,(i+n)/2+1,n,l,r,val);
    tree[node][0]=tree[node*2][0]+tree[node*2+1][0];
}
ll res(int node,int i,int n,int l,int r)
{
    if(n<l||i>r)return 0;
    if(tree[node][1])
    {
        if(i!=n)
        {
            tree[node*2][1]+=tree[node][1];
            tree[node*2+1][1]+=tree[node][1];
        }
        tree[node][0]+=(tree[node][1]*(n-i+1));
        tree[node][1]=0;
    }
    if(l<=i&&r>=n)return tree[node][0];
    return res(node*2,i,(i+n)/2,l,r)+res(node*2+1,(i+n)/2+1,n,l,r);
}

***************Dynamic****************
struct node
{
    ll val,lazy;
    node *left,*right;
    node()
    {
        val=0;
        lazy=0;
        left=NULL;
        right=NULL;
    }
};
void lazyupdd(ull i,ull n,ull p,ull q,ll val,node *cur)
{
    if(i>=p&&n<=q)cur->lazy+=val;
    if(cur->lazy)
    {
        if(i!=n)
        {
            if(cur->left==NULL)cur->left=new node();
            if(cur->right==NULL)cur->right=new node();
            cur->left->lazy+=cur->lazy;
            cur->right->lazy+=cur->lazy;
        }
        cur->val+=((cur->lazy)*(n-i+1));
        cur->lazy=0;
    }
    if(n<p||i>q)return;
    if(i>=p&&n<=q)return;
    ull mid=n-i;
    mid=i+mid/2;
    if(cur->left==NULL)cur->left=new node();
    if(cur->right==NULL)cur->right=new node();
    lazyupdd(i,mid,p,q,val,cur->left);
    lazyupdd(mid+1,n,p,q,val,cur->right);
    cur->val=cur->left->val+cur->right->val;
}
ll ansd(ull i,ull n,ull p,ull q,node *cur)
{
    if(cur==NULL)return 0;
    if(n<p||i>q)return 0;
    if(cur->lazy)
    {
        if(i!=n)
        {
            if(cur->left==NULL)cur->left=new node();
            if(cur->right==NULL)cur->right=new node();
            cur->left->lazy+=cur->lazy;
            cur->right->lazy+=cur->lazy;
        }
        cur->val+=((cur->lazy)*(n-i+1));
        cur->lazy=0;
    }
    if(i>=p&&n<=q)
    {
        return cur->val;
    }
    ull mid=n-i;
    mid=i+mid/2;
    return ansd(i,mid,p,q,cur->left)+ansd(mid+1,n,p,q,cur->right);
}