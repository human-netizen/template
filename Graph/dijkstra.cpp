ll dis[N];
int pre[N];
vector<pair<int,int>>g[N];
void dijkstra(int s,int n)
{
    for(int i=0;i<=n;i++)dis[i]=M;
    dis[s]=0;
//priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>str;
    priority_queue<pair<ll,int>>str;
    str.push({-dis[s],s});
    while(!str.empty())
    {
        auto [st,s]=str.top();
        st=-st;
        str.pop();
	if(dis[s]<st)continue; 
        for(auto [it,w]:g[s])
        {
            if(dis[it]>st+w)
            {
                dis[it]=st+w;
                str.push({-dis[it],it});
                pre[it]=s;
            }
        }
    }
}