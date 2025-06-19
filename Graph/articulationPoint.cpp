vector<int>g[N];
bool vis[N];
set<int>str;
int tin[N],low[N],T;
void dfs(int v,int pa)
{
    vis[v]=1;
    tin[v]=low[v]=++T;
    int child=0;
    for(auto it:g[v])
    {
        if(it==pa)continue;
        if(vis[it]==1)
        {
            low[v]=min(low[v],tin[it]);
        }
        else
        {
            dfs(it,v);
            low[v]=min(low[v],low[it]);
            child++;
            if(tin[v]<=low[it]&&pa!=0)
            {
                str.insert(v);
            }
        }
    }
    if(pa==0&&child>1)
    {
        str.insert(v);
    }
}

