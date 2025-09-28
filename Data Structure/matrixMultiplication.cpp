vector<vector<ll>> matmul(const vector<vector<ll>> &A,
                          const vector<vector<ll>> &B) {
    vector<vector<ll>> C(3, vector<ll>(3, 0));
    for (int i = 0; i < 3; i++)
        for (int k = 0; k < 3; k++)
            if (A[i][k])
                for (int j = 0; j < 3; j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}
 
vector<vector<ll>> matpow(vector<vector<ll>> n, ll k) {
    vector<vector<ll>> ans(3, vector<ll>(3, 0));
    for (int i = 0; i < 3; i++) ans[i][i] = 1;
 
    while (k > 0) {
        if (k & 1) ans = matmul(ans, n);
        n = matmul(n, n);
        k >>= 1;
    }
    return ans;
}
 
ll qp(ll a,ll b)
{
    ll x=1; a%=MOD;
    while(b)
    {
        if(b&1) x=x*a%MOD;
        a=a*a%MOD; b>>=1;
    }
    return x;
}
