const int BB=501;//n*m<=2*10^5;// O(min(n,m)*log(max(n,m)) queries
vector<ll>a[BB];
vector<ll>tree[BB];
bool ok;
ll  make(int node,int i,int n,int pos)
{
    if(i==n)
    {
        tree[pos][node]=a[pos][i];
        //cout<<tree[node]<<" ";
        return tree[pos][node];
    }
    int mid=(i+n)/2;
    ll p=make(node*2,i,mid,pos);
    ll q=make(node*2+1,mid+1,n,pos);
    tree[pos][node]=(p+q);
    return tree[pos][node];
}
void make(int n,int m)
{
    for(int i=1;i<=n;i++)make(1,1,m,i);
}
ll upd(int node,int i,int n,int ind,ll v,int pos)
{
    if(i==n&&ind==i)
    {
        return tree[pos][node]=v;
    }
    if(n<ind||i>ind)return tree[pos][node];
    int mid=(i+n)/2;
    return tree[pos][node]=(upd(node*2,i,mid,ind,v,pos)+upd(node*2+1,mid+1,n,ind,v,pos));
}
ll up(int n,int m,int x,int y,ll v)
{
        upd(1,1,m,y,v,x);
}
vector<int>tem;
void anss(int node,int i,int n,int p,int q)
{
    if(n<p||i>q)return ;
    if(i>=p&&n<=q)
    {
        tem.push_back(node);
        return ;
    }
    int mid=(i+n)/2;
    anss(node*2,i,mid,p,q);
    anss(node*2+1,mid+1,n,p,q);
}
ll an(int n,int m,int x1,int x2,int y1,int y2)
{
    ll sum=0;
    tem.clear();
    anss(1,1,m,y1,y2);
    for(auto node:tem)for(int pos=x1;pos<=x2;pos++)sum+=tree[pos][node];
    return sum;
}
//main
int main()
{
    int n,m;
    cin>>n>>m;
    ok=(n>=m);
    if(ok)
    {
        for(int i=1;i<=m;i++)tree[i].resize(n*4+5,0),a[i].resize(n+1);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                cin>>a[j][i];
            }
        }
        swap(n,m);
    }else
    {
        for(int i=1;i<=n;i++)tree[i].resize(m*4+5,0),a[i].resize(m+1);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                cin>>a[i][j];
            }
        }
    }
    make(n,m);
    while(1)
    {
        int op;
        cin>>op;
        if(op==1)
        {
            int x,y;
            ll v;
            cin>>x>>y>>v;
            if(ok)swap(x,y);
            up(n,m,x,y,v);
        }else
        {
            int x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            if(ok)swap(x1,y1),swap(x2,y2);
            cout<<an(n,m,x1,x2,y1,y2)<<"\n";
        }
    }
}
