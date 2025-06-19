struct DSU
{
    vector<int>tra;
    vector<int>tot;
    vector<pair<int,int>>str;
    bool rb;
    int cc;
    DSU(int n,bool rb=0)
    {
        cc=n;
        this->rb=rb;
        tra.resize(n+1);
        tot.resize(n+1,1);
        for(int i=0; i<=n; i++)tra[i]=i;
    }
    int par(int chi)
    {
        if(tra[chi]==chi)return chi;
        else if(rb)par(tra[chi]);
        else return tra[chi]=par(tra[chi]);
    }
    bool isjoint(int x,int y)
    {
        return par(x)==par(y);
    }
    int len()
    {
        set<int>tem;
        for(int i=1;i<tra.size();i++)tem.insert(par(i));
        return tem.size();
    }
    void join(int x,int y)
    {
        x=par(x);
        y=par(y);
        if(x==y)return;
        cc--;
        if(tot[x]>=tot[y])
        {
            tra[y]=x,tot[x]+=tot[y];
            if(rb)str.push_back({x,y});
        }
        else
        {
            tra[x]=y,tot[y]+=tot[x];
            if(rb)str.push_back({y,x});
        }
    }
    void pop()
    {
        auto [x,y]=str.back();
        str.pop_back();
        tot[x]-=tot[y];
        tra[y]=y;
        cc++;
    }
};