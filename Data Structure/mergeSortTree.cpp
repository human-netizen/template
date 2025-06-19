vector<pair<int,int>>tree[4*N];
vector<ll>pre[4*N];
int nxt[N]; 
vector<pair<int,int>>  make(int node,int i,int n)
{
    if(i==n)
    {
        tree[node].push_back({nxt[i],i});
        pre[node].push_back(nxt[i]-i);
        return tree[node];
    }
    int mid=(i+n)/2;
    vector<pair<int,int>>p=make(node*2,i,mid);
    vector<pair<int,int>>q=make(node*2+1,mid+1,n);
    int s=0,t=0;
    while(1)
    {
        if(s==p.size())
        {
            while(t!=q.size())tree[node].push_back(q[t]),t++;
            break;
        }
        else if(t==q.size())
        {
            while(s!=p.size())tree[node].push_back(p[s]),s++;
            break;
        }
        else if(p[s]<q[t])tree[node].push_back(p[s]),s++;
        else tree[node].push_back(q[t]),t++;
    }
    for(int i=0; i<tree[node].size(); i++)
    {
        pre[node].push_back(0);
        pre[node][i]=tree[node][i].first-tree[node][i].second;
        if(i)pre[node][i]+=pre[node][i-1];
    }
    return tree[node];
}
ll ans(int node,int i,int n,int p,int q,int last)
{
    if(n<p||i>q)return 0;
    if(i>=p&&n<=q)
    {
        int st=0,ed=n-i,mid;
        ll res=0;
        while(st<=ed)
        {
            mid=(st+ed)/2;
            if(tree[node][mid].first<=last)
            {
                res=pre[node][mid];
                st=mid+1;
            }
            else
            {
                ed=mid-1;
            }
        }
        return res;
    }
    int mid=(i+n)/2;
    ll pp=ans(node*2,i,mid,p,q,last);
    ll qq=ans(node*2+1,mid+1,n,p,q,last);
    return (pp+qq);
}