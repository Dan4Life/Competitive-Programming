#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll // delete if causing problems
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define mod(a) (a+MOD)%MOD
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
 
const int mxN = (int)3e5+10; // change when needed!
int n, k, q, a[mxN];
int segTree[2*mxN];
 
void upd(int i, int j, int v, int t, int p=0, int l=1, int r=n){
    if(i>r or j<l or i>j) return;
    int m = (l+r)/2; int lp = p+1, rp = p+2*(m-l+1);
    if(t and !segTree[p]) return;
    if(i<=l and r<=j){
        if(!t){ segTree[p]=v; return; }
        if(l==r) { segTree[p]/=v; return; }
    }
    upd(i,j,v,t,lp,l,m),upd(i,j,v,t,rp,m+1,r);
    segTree[p] = segTree[lp]+segTree[rp];
}
 
int query(int i, int j, int p=0, int l=1, int r=n){
    if(i>r or j<l or i>j) return 0;
    if(i<=l and r<=j) return segTree[p];
    int m = (l+r)/2; int lp=p+1, rp = p+2*(m-l+1);
    return query(i,j,lp,l,m)+query(i,j,rp,m+1,r);
}
 
void solve()
{
    cin >> n >> q >> k;
    for(int i = 1; i <= n; i++) cin >> a[i], upd(i,i,a[i],0);
    while(q--){
        int t, x, y; cin >> t >> x >> y;
        if(t==1) upd(x, x, y, 0);
        else if(t==2){
            if(k>1) upd(x, y, k, 1);
        }
        else cout << query(x,y) << "\n";
    }
}
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
}
