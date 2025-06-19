#include<bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    vector<int> g, l, r; int ans;
    HopcroftKarp(int n, int m, const vector<pair<int,int>> &e)
    : g(e.size()), l(n, -1), r(m, -1), ans(0) {
        vector<int> deg(n + 1), a, p, q(n);
        for (auto &[x, y] : e) deg[x]++;
        for (int i = 1; i <= n; i++) deg[i] += deg[i - 1];
        for (auto &[x, y] : e) g[--deg[x]] = y;
        for (bool match=true; match;) {
            a.assign(n,-1), p.assign(n,-1); int t=0; match=false;
            for (int i = 0; i < n; i++)
                if (l[i] == -1) q[t++] = a[i] = p[i] = i;
            for (int i = 0; i < t; i++) {
                int x = q[i];
                if (~l[a[x]]) continue;
                for (int j = deg[x]; j < deg[x + 1]; j++) {
                    int y = g[j];
                    if (r[y] == -1) {
                        while (~y) r[y] = x, swap(l[x], y), x = p[x];
                        match = true; ans++; break;
                    }
                    if(p[r[y]]==-1)q[t++]=y=r[y],p[y]=x,a[y]=a[x];
                }
            }
        }
    }
};

void solve(int t){
    int l,r,m;
    cin>>l>>r>>m;
    
    vector<pair<int,int>> edges;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        edges.push_back({a,b});
    }
    mt19937 rng(0);
    shuffle(edges.begin(),edges.end(),rng);
    
    HopcroftKarp ds(l,r,edges);
    cout<<ds.ans<<"\n";
    for(int i=0;i<l;i++){
        if(ds.l[i]!=-1){
            cout<<i<<" "<<ds.l[i]<<"\n";
            assert(ds.r[ds.l[i]]==i);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t=1;
    //cin>>t;
    for(int i=1;i<=t;i++)solve(i);
    
    return 0;
}