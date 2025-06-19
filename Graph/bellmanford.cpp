struct Edge
{
    int a, b, cost;
};
int n, m, u,v;
vector<Edge> edges(N);
const int INF=2e9;
void solve()
{
    vector<int> d(n+1, INF);
    d[u] = 0;
    vector<int> p(n+1, -1);
    int x=0;
    for (int i = 0; i < n; ++i)
    {
        for (Edge e : edges)
            if (d[e.a] < INF)
                if (d[e.b] > d[e.a] + e.cost) {
                    d[e.b] = max(-INF, d[e.a] + e.cost);
                    p[e.b] = e.a
                    x=i;
                }
    }
    if (x <n-1)
        cout<<-d[v]<<"\n";
    else
    {
        cout<<"Negative loop!\n";
    }
}