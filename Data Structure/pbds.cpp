#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
ordered_set oset;
for(int i=0;i<n;i++)oset.insert(i);
int nxt=*oset.find_by_order(x+1);
oset.erase(oset.find(nxt));
int q=oset.order_of_key(p);
