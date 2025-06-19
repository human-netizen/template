struct edge
{
    int x,y;
    ll w;
    edge() {}
    edge(int x,int y,ll w)
    {
        this->x=x;
        this->y=y;
        this->w=w;
    }
    bool operator <(edge b)
    {
        return w<b.w;
    }
};
ll MST(vector<edge>&str,int n)
{
    sort(str.begin(),str.end());
    ll sum=0;
    DSU dsu(n);
    for(auto it:str)
    {
        if(dsu.isjoint(it.x,it.y)==0)
        {
            sum+=it.w;
            dsu.join(it.x,it.y);
        }
    }
    if(dsu.cc>1)sum=-1;
    return  sum;
}
//main
int main()
{
    int n,m;
    cin>>n>>m;
    vector<edge>str(m);
    for(int i=0; i<m; i++)
    {
        cin>>str[i].x>>str[i].y>>str[i].w;
    }
    cout<<MST(str,n);
}