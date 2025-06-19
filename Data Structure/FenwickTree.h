/* * Description: Computes partial sums a[1] + a[2] + ... + a[pos], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 * Note: 1-based indexing
 */
#pragma once

struct FT {
    vector<ll> s;
    FT(int n) : s(n + 1) {} // size + 1 for 1-based indexing
    
    void update(int pos, ll dif) { // a[pos] += dif
        for (; pos < sz(s); pos += pos & -pos) 
            s[pos] += dif;
    }
    
    ll query(int pos) { // sum of values in [1, pos]
        ll res = 0;
        for (; pos > 0; pos -= pos & -pos)
            res += s[pos];
        return res;
    }
    
    int lower_bound(ll sum) { // min pos st sum of [1, pos] >= sum
        // Returns n if no sum is >= sum, or 0 if empty sum is.
        if (sum <= 0) return 0;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw < sz(s) && s[pos + pw] < sum)
                pos += pw, sum -= s[pos];
        }
        return pos + 1;
    }
};