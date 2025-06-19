ll progSum(ll a , ll n , ll d){
    return (2 * a + (n - 1) * d) * n / 2;
}
const ll mx = 2e5 + 10;
struct 
{
    ll prop;
    ll sum;
    ll tempSum;
}seg[mx * 4];
 
void propagate(ll node , ll l , ll r){
    ll lnode = node * 2;
    ll rnode = node * 2 + 1;
    ll mid = (l + r) / 2;
    ll total_l = mid - l + 1;
    ll total_r = r - mid;
     
    seg[lnode].sum += ((((total_l * (total_l + 1)) / 2)) * seg[node].prop) ;
    seg[rnode].sum += ((((total_r * (total_r + 1)) / 2)) * seg[node].prop) ;
    seg[lnode].prop += seg[node].prop;
    seg[rnode].prop += seg[node].prop;
    seg[lnode].tempSum += (seg[node].prop * total_l);
    seg[rnode].tempSum += (seg[node].prop * total_r); 
    seg[node].prop = 0;
    
}
ll loop;
 
void update(ll node , ll l , ll r , ll L , ll R , ll d){
    //debug(node , l , r);
    if(R < l || r < L)return ;
    if(L <= l && r <= R){
        ll n = r - l + 1;
              
        seg[node].prop += d;      
        seg[node].sum += (((n * (n + 1))/2) * d);  
        seg[node].tempSum += (d * n);    
        debug(node , l , r , seg[node].sum , seg[node].prop , seg[node].tempSum);
        
        return ;
    }
    propagate(node , l , r);
    ll mid = (l + r) / 2;
    ll lnode = node * 2;
    ll rnode = node * 2 + 1;
    update(lnode , l , mid , L , R , d);
    update(rnode , mid + 1 , r , L , R , d);
    seg[node].sum = seg[lnode].sum + (seg[rnode].sum) + seg[rnode].tempSum * (mid + 1 - l);
    seg[node].tempSum = seg[lnode].tempSum + seg[rnode].tempSum;

}


////////////////Arithmetic progression
struct 
{
    ll hasLazy;
    ll cur_a;
    ll cur_d;
    ll sum;
}seg[800005];
 
void propagate(ll node , ll l , ll r){
    ll lnode = node * 2;
    ll rnode = node * 2 + 1;
    ll mid = (l + r) / 2;
    ll total_l = mid - l + 1;
    ll total_r = r - mid;
    ll temp_a_l = seg[node].cur_a + (l - l) * seg[node].cur_d;
    ll temp_a_r = seg[node].cur_a + (mid + 1 - l) * seg[node].cur_d;
 
 
    seg[lnode].cur_a += temp_a_l;
    seg[lnode].cur_d += seg[node].cur_d;
        
    seg[rnode].cur_a += temp_a_r;           
    seg[rnode].cur_d += seg[node].cur_d;
    
    seg[lnode].sum += progSum(temp_a_l , total_l , seg[node].cur_d);
    seg[rnode].sum += progSum(temp_a_r, total_r , seg[node].cur_d);
    seg[node].cur_a = seg[node].cur_d = 0;
 
    
}
 
void update(ll node , ll l , ll r , ll L , ll R , ll a , ll d){
    if(R < l || r < L)return ;
    if(L <= l && r <= R){
        ll temp_a = a + (l - L) * d;
        
        seg[node].cur_a += temp_a;
        seg[node].cur_d += d;
    
        ll n = r - l + 1;
        seg[node].sum += progSum(temp_a , n , d);
        return ;
    }
    propagate(node , l , r);
    ll mid = (l + r) / 2;
    ll lnode = node * 2;
    ll rnode = node * 2 + 1;
    update(lnode , l , mid , L , R , a , d);
    update(rnode , mid + 1 , r , L , R , a , d);
    seg[node].sum = seg[lnode].sum + seg[rnode].sum;
    //cout<<l<<" "<<r<<" "<<seg[node].sum<<endl;
}