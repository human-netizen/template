vector<int>g[N];
int b[N],a[N];
int parent[N], depth[N], heavy[N], head[N], pos[N];
int timer=0;
int dfs(int node)
{
    int msi=0,si=1;
    heavy[node]=0;
    for(auto it:g[node])
    {
        if(it==parent[node])continue;
        parent[it]=node;
        depth[it]=depth[node]+1;
        int csi=dfs(it);
        si+=csi;
        if(csi>msi)
        {
            msi=csi;
            heavy[node]=it;
        }
    }
    return si;
}
void decompose(int node,int h)
{
    head[node]=h;
    timer++;
    pos[node]=timer;
    b[timer]=a[node];
    if(heavy[node]!=0)
    {
        decompose(heavy[node],h);
    }
    for(auto it:g[node])
    {
        if(it==parent[node]||it==heavy[node])continue;
        decompose(it,it);
    }
}
//segemtn tree start
int tree[4*N];
int  make(int node,int i,int n)
{
    if(i==n)
    {
        tree[node]=b[i];
        //cout<<tree[node]<<" ";
        return tree[node];
    }
    int mid=(i+n)/2;
    int p=make(node*2,i,mid);
    int q=make(node*2+1,mid+1,n);
    tree[node]=(p+q);
    return tree[node];
}
int upd(int node,int i,int n,int ind)
{
    if(i==n&&ind==i)
    {
        return tree[node]=b[ind];
    }
    if(n<ind||i>ind)return tree[node];
    int mid=(i+n)/2;
    return tree[node]=(upd(node*2,i,mid,ind)+upd(node*2+1,mid+1,n,ind));
}
int ans(int node,int i,int n,int p,int q)
{
    if(n<p||i>q)return 0;
    if(i>=p&&n<=q)
    {
        return tree[node];
    }
    int mid=(i+n)/2;
    int pp=ans(node*2,i,mid,p,q);
    int qq=ans(node*2+1,mid+1,n,p,q);
    //cout<<min(pp,qq)<<" ";
    return (pp+qq);
}
//segment tree end
int query(int x,int y,int n)
{
    int res = 0;
    for (; head[x] != head[y]; y = parent[head[y]])
    {
        if (depth[head[x]] > depth[head[y]])
            swap(x, y);
        int cur_heavy_path_max = ans(1,1,n,pos[head[y]], pos[y]);
        res = (res+ cur_heavy_path_max);
    }
    if (depth[x] > depth[y])
        swap(x, y);
    int last_heavy_path_max = ans(1,1,n,pos[x], pos[y]);
    res = (res+ last_heavy_path_max);
    return res;
}