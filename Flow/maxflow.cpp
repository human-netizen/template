ll g[N][N];
int pre[N];
ll val[N];
//Edmonds–Karp BFS - ekbfs
void ekbfs(int st,int n)
{
    val[st]=inf;
    queue<int>str;
    str.push(st);
    while(!str.empty())
    {
        st=str.front();
        str.pop();
        for(int j=1;j<=n;j++)
        {
            if(g[st][j]>0&&pre[j]==0)
            {
                val[j]=min(g[st][j],val[st]);
                pre[j]=st;
                str.push(j);
            }
        }
    }
}
ll maxflow(int st,int ed,int n)
{
    ll sum=0;
    while(1)
    {
        set1(pre,n,0);
        ekbfs(st,n);
        if(pre[ed]==0)break;
        sum+=val[ed];
        int cur=ed;
        while(cur!=st)
        {
            g[pre[cur]][cur]-=val[ed];
            g[cur][pre[cur]]+=val[ed];
            cur=pre[cur];
        }
    }
    return sum;
}
//main
int main()
{
    int n,m;
    cin>>n>>m;
    int st,ed;
    cin>>st>>ed;
    set2(g,n,n,0);
    for(int i=0;i<m;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        g[x][y]=w;
    }
    cout<<maxflow(st,ed,n);
}