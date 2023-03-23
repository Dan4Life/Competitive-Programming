/*
Solved by myself
The b part is just calculated by summation. Excluding the b part, the problem becomes:
Find the smallest x that makes |x-A0| + |x-A1| + ... + |x-Aq| as small as possible (+ B0...Bq) for qth query
We can think of all the A[] on a number line, and the optimal x is also on the number line.
The problem is now: Find the point which makes the total sum of distances to all other points A0...Aq minimum
This is a well know problem as the solution is just the median point!
If there are two median points tho, the x can be any number in between both median points(therefore we pick the left median as x in that case)
This can all be done with purely fenwick/segtree or order statistics tree+fenwick like shown below
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long

const int maxn = (int)3e5+10;

set<int> S;
int cnt = 1, q;
int fenwick[3][maxn];
unordered_map<int,int> ind;
int t[maxn], a[maxn], b[maxn], r_ind[maxn];
template<class T> using Tree = tree<T,null_type,less<T>,rb_tree_tag, tree_order_statistics_node_update>;

Tree<pair<int,int>> S2;

void update(int x, int v, int t){
    for(; x<maxn; x+=(x&-x))
        fenwick[t][x]+=v;
}

int sum(int x, int t){
    int tot = 0;
    for(; x>0; x-=(x&-x))
        tot+=fenwick[t][x];
    return tot;
}

int query(int l, int r, int t){
    if(l>r) return 0;
    return sum(r,t)-sum(l-1,t);
}

int32_t main(){
    cin >> q;
    for(int i = 0; i < q; i++){
        cin >> t[i];
        if(t[i]==1) cin >> a[i] >> b[i], S.insert(a[i]);
    }
    for(auto u : S) ind[u]=cnt++, r_ind[cnt-1]=u;
    int sum = 0;

    for(int i = 0; i < q; i++){
        if(t[i]==2){
            int l = S2.find_by_order(((int)S2.size()-1)/2)->first;
            int dist = query(1,l-1,0)*r_ind[l]-query(1,l-1,1);
            dist += query(l+1,maxn-1,1)-query(l+1,maxn-1,0)*r_ind[l];
            cout << r_ind[l] << " " << dist+sum << "\n";
        }
        else{
            sum+=b[i]; S2.insert({ind[a[i]],i});
            update(ind[a[i]], 1, 0);
            update(ind[a[i]], a[i], 1);
        }
    }
}