class SuffixArray {
private:
    string s;
    int n;
    vector<int> p, c;
    vector<int> lcp;
    
    vector<int> sort_cyclic_shifts() {
        const int alphabet = 256;
        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
        
        // Count sort for the first character
        for(int i = 0; i < n; i++) cnt[s[i]]++;
        for(int i = 1; i < alphabet; i++) cnt[i] += cnt[i-1];
        for(int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
        
        c[p[0]] = 0;
        int classes = 1;
        for(int i = 1; i < n; i++) {
            if(s[p[i]] != s[p[i-1]]) classes++;
            c[p[i]] = classes - 1;
        }
        
        // Iterate through powers of 2
        vector<int> pn(n), cn(n);
        for(int h = 0; (1 << h) < n; h++) {
            for(int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if(pn[i] < 0) pn[i] += n;
            }
            
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for(int i = 0; i < n; i++) cnt[c[pn[i]]]++;
            for(int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
            for(int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
            
            cn[p[0]] = 0;
            classes = 1;
            for(int i = 1; i < n; i++) {
                pair<int,int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int,int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
                if(cur != prev) ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        return p;
    }

    int cmp(int i, string &pat) {
        for(int j = i; j < n - 1; j++) {
            if(j - i == pat.size()) return 0;
            if(s[j] > pat[j - i]) return 1;
            if(s[j] < pat[j - i]) return -1;
        }
        if(pat.size() == (n - i - 1)) return 0;
        return -1;
    }

public:
    SuffixArray() {}
    
    void build(string &input) {
        s = input;
        n = s.size();
        p = sort_cyclic_shifts();
        c.resize(n);
        lcp.resize(n);
        
        for(int i = 0; i < n; i++) c[p[i]] = i;
        int k = 0;
        for(int i = 0 ; i < n - 1 ; i++){ //0123$
            int pi = c[i];
            int j = p[pi - 1];
            while(s[i + k] == s[j + k])k++;
            lcp[pi] = k;
            k = max(0 , k - 1);
        }
        // for(int i = 1 ; i < n ; i++){
        //     debug(i , s.substr(p[i]) ,lcp[i]);
        // }
    }
    
    int upper_bound(int lo, int hi, string &pat) {
        if(lo == hi) return lo;
        int mid = (lo + hi) / 2;
        int cc = cmp(p[mid], pat);
        if(cc > 0) return upper_bound(lo, mid, pat);
        return upper_bound(mid + 1, hi, pat);
    }
    
    int lower_bound(int lo, int hi, string &pat) {
        if(lo == hi) return lo;
        int mid = (lo + hi) / 2;
        if(cmp(p[mid], pat) >= 0) return lower_bound(lo, mid, pat);
        return lower_bound(mid + 1, hi, pat);
    }
};