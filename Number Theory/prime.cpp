****************Linear*******************
std::vector <int> prime;
bool is_composite[MAXN];

void sieve (int n) {
	std::fill (is_composite, is_composite + n, false);
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) prime.push_back (i);
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}



void largepri(int N)
{
    int n=sqrt(N);
    normalsieve(n);
    int st=n+1;
    int ed=st+n;
    bool vis[n+1];
    while(st<N)
    {
        if(ed>N)ed=N;
        for(int i=0;i<=n;i++)vis[i]=1;
        for(auto it:pri)
        {
            for(int i=((st-1)/it+1)*it-st;i<=n;i+=it)
            {
                //cout<<i+st<<" ";
                vis[i]=0;
            }
        }
        for(int i=0;i<=ed-st;i++)
        {
            if(vis[i])
            {
                //cout<<i+st<<" ";
                allpri.push_back(i+st);
            }
        }
        st=ed+1;
        ed=st+n;
    }
}
