//const int N=24;
ll mat[N][N];
ll dp[1<<N];
ll det(int mask,int n)
{
    if(mask==0)return 1;
    if(dp[mask]!=-1)return dp[mask];
    int used=n-__builtin_popcount(mask);
    dp[mask]=0;
    int co=0;
    for(int i=0;i<n;i++)
    {
        if(mask&(1<<i))
        {
            co++;
            if(co%2)
            {
                dp[mask]+=mat[used][i]*det(mask^(1<<i),n);
            }else
            {
                dp[mask]-=mat[used][i]*det(mask^(1<<i),n);
            }
        }
    }
    return dp[mask];
}