
/*
  OR convolution (indices are bitmasks 0..(1<<nbits)-1)
*/
struct ORConv {
    static void zeta(vector<ll>& a, int nbits){
        int N = 1<<nbits;
        for(int b=0;b<nbits;b++){
            for(int mask=0;mask<N;mask++){
                if(mask & (1<<b)) a[mask] += a[mask ^ (1<<b)];
            }
        }
    }
    static void mobius(vector<ll>& a, int nbits){
        int N = 1<<nbits;
        for(int b=0;b<nbits;b++){
            for(int mask=0;mask<N;mask++){
                if(mask & (1<<b)) a[mask] -= a[mask ^ (1<<b)];
            }
        }
    }
    static vector<ll> convolve(vector<ll> A, vector<ll> B, int nbits){
        int N = 1<<nbits;
        if((int)A.size() != N || (int)B.size() != N) throw runtime_error("ORConv: size mismatch");
        zeta(A, nbits); zeta(B, nbits);
        vector<ll> C(N);
        for(int i=0;i<N;i++) C[i] = A[i] * B[i];
        mobius(C, nbits);
        return C;
    }
};

/*
  AND convolution
*/
struct ANDConv {
    static void zeta_superset(vector<ll>& a, int nbits){
        int N = 1<<nbits;
        for(int b=0;b<nbits;b++){
            for(int mask=0;mask<N;mask++){
                if(!(mask & (1<<b))) a[mask] += a[mask | (1<<b)];
            }
        }
    }
    static void mobius_superset(vector<ll>& a, int nbits){
        int N = 1<<nbits;
        for(int b=0;b<nbits;b++){
            for(int mask=0;mask<N;mask++){
                if(!(mask & (1<<b))) a[mask] -= a[mask | (1<<b)];
            }
        }
    }
    static vector<ll> convolve(vector<ll> A, vector<ll> B, int nbits){
        int N = 1<<nbits;
        if((int)A.size() != N || (int)B.size() != N) throw runtime_error("ANDConv: size mismatch");
        zeta_superset(A, nbits); zeta_superset(B, nbits);
        vector<ll> C(N);
        for(int i=0;i<N;i++) C[i] = A[i] * B[i];
        mobius_superset(C, nbits);
        return C;
    }
};

/*
  XOR convolution (FWHT)
*/
struct XORConv {
    static void fwht(vector<ll>& a, bool inverse=false){
        int N = (int)a.size();
        for(int len=1; len<N; len<<=1){
            for(int i=0;i<N;i += (len<<1)){
                for(int j=0;j<len;j++){
                    ll u = a[i+j];
                    ll v = a[i+j+len];
                    a[i+j] = u + v;
                    a[i+j+len] = u - v;
                }
            }
        }
        if(inverse){
            // divide by N
            for(int i=0;i<N;i++) {
                // for integer arrays, result should be divisible by N if original convolution is integral.
                a[i] /= N;
            }
        }
    }
    static vector<ll> convolve(vector<ll> A, vector<ll> B){
        int N = (int)A.size();
        if(N != (int)B.size()) throw runtime_error("XORConv: size mismatch");
        vector<ll> fa=A, fb=B;
        fwht(fa, false);
        fwht(fb, false);
        for(int i=0;i<N;i++) fa[i] = fa[i] * fb[i];
        fwht(fa, true);
        return fa;
    }
};


/*
  GCD Convolution
*/
struct GCDConv {
    static vector<int> mobius_sieve(int M){
        vector<int> mu(M+1, 1), primes; vector<int> mind(M+1,0);
        mu[0]=0; if(M>=1) mu[1]=1;
        for(int i=2;i<=M;i++){
            if(!mind[i]) { mind[i]=i; primes.push_back(i); mu[i] = -1; }
            for(int p: primes){
                long long v = 1LL * p * i;
                if(v> M) break;
                mind[v] = p;
                if(i % p == 0){ mu[v]=0; break;}
                else mu[v] = -mu[i];
            }
        }
        return mu;
    }
    static vector<ll> convolve(const vector<ll>& A, const vector<ll>& B){
        int M = (int)A.size()-1;
        if((int)B.size()-1 != M) throw runtime_error("GCDConv: size mismatch");
        vector<ll> tA(M+1,0), tB(M+1,0);
        for(int d=1; d<=M; d++){
            for(int k=d; k<=M; k+=d){
                tA[d] += A[k];
                tB[d] += B[k];
            }
        }
        vector<ll> tC(M+1);
        for(int d=1; d<=M; d++) tC[d] = tA[d] * tB[d];
        // Möbius for multiples inversion: C[i] = sum_{t: i*t <= M} mu[t] * tC[i*t]
        vector<int> mu = mobius_sieve(M);
        vector<ll> C(M+1,0);
        for(int i=1;i<=M;i++){
            ll val = 0;
            for(int t=1; i*t<=M; t++){
                val += (ll)mu[t] * tC[i*t];
            }
            C[i] = val;
        }
        return C;
    }
};

/*
  LCM Convolution
*/
struct LCMConv {
    static vector<int> mobius_sieve(int M){
        vector<int> mu(M+1, 1), primes; vector<int> mind(M+1,0);
        mu[0]=0; if(M>=1) mu[1]=1;
        for(int i=2;i<=M;i++){
            if(!mind[i]) { mind[i]=i; primes.push_back(i); mu[i] = -1; }
            for(int p: primes){
                long long v = 1LL * p * i;
                if(v> M) break;
                mind[v] = p;
                if(i % p == 0){ mu[v]=0; break;}
                else mu[v] = -mu[i];
            }
        }
        return mu;
    }
    static vector<ll> convolve(const vector<ll>& A, const vector<ll>& B){
        int M = (int)A.size()-1;
        if((int)B.size()-1 != M) throw runtime_error("LCMConv: size mismatch");
        vector<ll> tA(M+1,0), tB(M+1,0);
        for(int m=1;m<=M;m++){
            for(int d=1; d*d<=m; d++){
                if(m % d == 0){
                    tA[m] += A[d];
                    if(d*d != m) tA[m] += A[m/d];
                }
            }
            for(int d=1; d*d<=m; d++){
                if(m % d == 0){
                    tB[m] += B[d];
                    if(d*d != m) tB[m] += B[m/d];
                }
            }
        }
        vector<ll> tC(M+1);
        for(int m=1;m<=M;m++) tC[m] = tA[m] * tB[m];
        vector<int> mu = mobius_sieve(M);
        vector<ll> C(M+1,0);
        for(int m=1;m<=M;m++){
            ll val = 0;
            // sum_{d|m} mu[d] * tC[m/d]
            for(int d=1; d*d<=m; d++){
                if(m % d == 0){
                    val += (ll)mu[d] * tC[m/d];
                    int d2 = m/d;
                    if(d2 != d) val += (ll)mu[d2] * tC[m/d2];
                }
            }
            C[m] = val;
        }
        return C;
    }
};
