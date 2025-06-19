struct sparse_table {
private:
    ll maxn;
    ll k;
    vector<vector<ll>> TABLE;
    vector<ll> logs;
 
public:
    sparse_table (ll n) {
        maxn = n;
        logs.resize(maxn+1, 0);
        for (ll i = 2; i <= maxn; i++) logs[i] = logs[i >> 1] + 1;
        k = logs[maxn] + 1;
        TABLE.resize(maxn, vector<ll> (k));
    }
    void create_table (vector<ll> &A) {
        for (ll i = 0; i < maxn; i++) TABLE[i][0] = A[i];
        for (ll i = 1; i < k; i++) {
            for (ll j = 0; j + (1 << i) - 1 < maxn; j++) {
                TABLE[j][i] = min(TABLE[j][i-1] , TABLE[j + (1 << (i-1))][i-1]);
            }
        }
    }
    // indexing should be zero based
 
    ll query (ll x, ll y) {
        ll gap = (y - x) + 1;
        ll lg = logs[gap];
        return min(TABLE[x][lg], TABLE[y - (1 << lg) + 1][lg]);
    }
 
    ll query_sum (ll x, ll y) {
        long long ans = 0;
        ll gap = y - x + 1;
        ll log_gap = logs[gap];
        for (ll i = log_gap; i >= 0; i--) {
            if ((1 << i) <= (y - x + 1)) {
                ans += (long long) TABLE[x][i];
                x += (1 << i);
            }
        }
        return ans;
    }
 
};
 
typedef struct sparse_table sparse;
class SuffixArray {
private:
 
    void countSort(vector<ll>& p, vector<ll>& c) {
        ll n = p.size();
        vector<ll> cnt(n);
        for (auto x : c) {
            cnt[x]++;
        }
 
        vector<ll> p_new(n);
        vector<ll> pos(n);
        pos[0] = 0;
        for (ll i = 1; i < n; i++) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        for (auto x : p) {
            ll i = c[x];
            p_new[pos[i]] = x;
            pos[i]++;
        }
        p = p_new;
    }
 
public:
    string s;
    ll n;
    int totk = 0;
    vector<ll> p;
    vector<vector<ll> > ck;
    vector<ll>lcp;
    SuffixArray(){}
 
    void build(string s) {
        s += " ";
        this->s = s;
        n = this->s.size();
        p.resize(n);
        
        lcp.resize(n);
        ck.resize(32);
        for(auto &row:ck){
            row.resize(n);
        }
        
        // k = 0
        vector<pair<char, ll>> a(n);
        for (ll i = 0; i < n; i++) a[i] = {s[i], i};
        sort(a.begin(), a.end());
 
        for (ll i = 0; i < n; i++) p[i] = a[i].second;
        ck[0][p[0]] = 0;
        
        for (ll i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first) {
                ck[0][p[i]] = ck[0][p[i - 1]];
            } else {
                ck[0][p[i]] = ck[0][p[i - 1]] + 1;
            }
        }
 
        ll k = 0;
        while ((1 << k) < n) {
            // k -> k + 1
            for (ll i = 0; i < n; i++) {
                p[i] = (p[i] - (1 << k) + n) % n;
            }
 
            countSort(p, ck[k]);
            ck[k + 1][p[0]] = 0;
            for (ll i = 1; i < n; i++) {
                pair<ll, ll> prev = {ck[k][p[i - 1]], ck[k][(p[i - 1] + (1 << k)) % n]};
                pair<ll, ll> now = {ck[k][p[i]], ck[k][(p[i] + (1 << k)) % n]};
                if (now == prev) {
                    ck[k + 1][p[i]] = ck[k + 1][p[i - 1]];
                } else {
                    ck[k + 1][p[i]] = ck[k + 1][p[i - 1]] + 1;
                }
            }
            k++;
        }
        
        totk = k;
        k = 0;
 
        //p[i] hocche amar sorted array.
        //c[i] hocche p[i] er inv => c[p[i]] = i;
        //c[i] hocche suffix array er kon index
        for(ll i = 0 ; i < n - 1 ; i++){
            ll pi = ck[totk][i];
            ll j = p[pi - 1];
            while(s[i + k] == s[j + k]){
                
                k++;
            }
            
            lcp[pi] = k;
            k = max(0LL , k - 1);
        } 
        for(int i = 1 ; i < n ; i++){
            debug(lcp[i] , s.substr(p[i]));
        }
 
 
    }
}suffix_array;
int cnt = 0;
ll upper(ll lo , ll hi , ll cur , ll val , sparse_table&sp){
 
    if(lo == hi)return lo;
    ll mid = (lo + hi) / 2;
    if(sp.query(cur , mid) >= val)return upper(mid + 1 , hi , cur , val , sp);
    return upper(lo , mid , cur , val , sp);
}
ll upper_l(ll lo , ll hi , ll cur , ll val , sparse_table&sp){
 
    if(lo == hi)return lo;
    ll mid = (lo + hi) / 2;
    if(sp.query(mid + 1 , cur) >= val)return upper_l(lo , mid , cur , val , sp);
    return upper_l(mid + 1 , hi , cur , val , sp);
}