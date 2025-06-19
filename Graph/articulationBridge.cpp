l n,m;
ll ans;
vector<int>g[N];
int co[N];
vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    co[v]=1;
    visited[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;
    for (int to : g[v]) {
        if (to == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            co[v]+=co[to];
            low[v] = min(low[v], low[to]);

            if (low[to] > tin[v])
            {
                ll rem=co[to];
                ll cur=n-co[to];
                ans=min(ans,(rem*(rem-1))/2+(cur*(cur-1))/2);
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n+1, false);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    for (int i = 1; i <=n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}
