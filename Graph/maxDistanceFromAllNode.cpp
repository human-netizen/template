vector<int>g[N];
int ma2[N][2];
int madis[N];
int dfs1(int node,int par)
{
    ma2[node][0]=ma2[node][1]=0;
    for(auto it:g[node])
    {
        if(it==par)continue;
        ma2[node][1]=max(ma2[node][1],1+dfs1(it,node));
        if(ma2[node][1]>ma2[node][0])swap(ma2[node][1],ma2[node][0]);
    }
    return ma2[node][0];
}
void dfs2(int node,int par,int pre)
{
    madis[node]=pre;
    for(auto it:g[node])
    {
        if(it==par)continue;
        madis[node]=max(madis[node],ma2[it][0]+1);
        if(ma2[node][0]==ma2[it][0]+1)dfs2(it,node,max(pre+1,ma2[node][1]+1));
        else dfs2(it,node,max(pre+1,ma2[node][0]+1));
    }
}