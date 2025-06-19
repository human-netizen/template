ll pow(ll base,ll po,int M)
{
    ll ans=1;
    while(po)
    {
        if(po%2)
        {
            ans=(ans*base)%M;
        }
        base=(base*base)%M;
        po/=2;
    }
    return ans;
}
int phi(int n)
{
    int ans=1;
    int q=sqrt(n);
    for(int i=2;i<=q;i++)
    {
        if(n%i==0)
        {
            int tem=1;
            while(n%i==0)
            {
                tem*=i;
                n/=i;
            }
            ans=ans*tem/i*(i-1);
            q=sqrt(n);
        }
    }
    if(n>1)ans=ans*(n-1);
    return ans;
}
bool issolvable(vector<pair<int,int>>&str)
{
    int n=str.size();
    ll mm=1;
    for(int i=0;i<n;i++)
    {
        if(__gcd(mm,(ll)str[i].second)!=1)return 0;
        mm*=str[i].second;
    }
    return 1;
}
ll CRT(vector<pair<int,int>>&str)
{
    ll mm=1;
    int n=str.size();
    for(int i=0;i<n;i++)mm=mm*str[i].second;
    ll x=0;
    for(int i=0;i<n;i++)
    {
        x=x+str[i].first*mm/str[i].second*pow(mm/str[i].second,phi(str[i].second)-1,str[i].second);
    }
    return x=((x%mm)+mm)%mm;
}
//main
int main()
{
    fastio
    int n;
    cin>>n;
    vector<pair<int,int>>str;
    for(int i=0;i<n;i++)
    {
        int a,m;
        cin>>a>>m;
        str.push_back({a,m});
    }
    if(issolvable(str))
    {
        yes(1);
        cout<<CRT(str);
    }else yes(0);
}