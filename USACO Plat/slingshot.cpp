#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
//#define int long long
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;
using vi = vector<int>;
using ar2 = array<int,2>;
using ar3 = array<int,3>;

const int mxN = (int)1e5+10;
const int INF = (int)1e9;
const ll LINF = (ll)2e18;

template<int _MX>
struct SparseMinSegTree{
    const static int MX = _MX;
    const static int SZ = __lg(MX)*4*mxN;
    
    ll seg[SZ];
    int L[SZ], R[SZ], IND;
    
    void newNode(int p, int l, int r){ seg[p] = LINF; }

    void init(){
        for(int i = 0; i < SZ; i++) L[i]=R[i]=0;
        IND = 1; newNode(1,0,MX);
    }

    void upd(int x, ll v, int p=1, int l=0, int r=MX){
        if(!p) return;
        if(l==r){ seg[p]=min(seg[p],v); return; }
        int mid = (l+r)/2;
        if(!L[p]) L[p]=++IND,newNode(L[p],l,mid);
        if(!R[p]) R[p]=++IND,newNode(R[p],mid+1,r);
        if(x<=mid) upd(x,v,L[p],l,mid);
        else upd(x,v,R[p],mid+1,r);
        seg[p] = min(seg[L[p]],seg[R[p]]);
    }

    ll query(int i, int j, int p=1, int l=0, int r=MX){
        if(!p or i>r or j<l or i>j) return LINF;
        if(i<=l and r<=j) return seg[p];
        int mid = (l+r)/2;
        if(!L[p]) L[p]=++IND,newNode(L[p],l,mid);
        if(!R[p]) R[p]=++IND,newNode(R[p],mid+1,r);
        return min(query(i,j,L[p],l,mid),query(i,j,R[p],mid+1,r));
    }
};

SparseMinSegTree<INF> seg;

int n, m, j;
ll a[mxN], b[mxN], c[mxN];
ll x[mxN], y[mxN], ans[mxN];

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("slingshot.in");
    ofstream cout("slingshot.out");
    cin >> n >> m;
    for(int i = 0; i < n; i++) 
        cin >> a[i] >> b[i] >> c[i];
    for(int i = 0; i < m; i++){
        cin >> x[i] >> y[i];
        ans[i]=abs(x[i]-y[i]);
    }
    vi ord1(n,0); iota(all(ord1),0);
    vi ord2(m,0); iota(all(ord2),0);
    sort(all(ord1),[&](int i, int j){return a[i]<a[j];});
    sort(all(ord2),[&](int i, int j){return x[i]<x[j];});

    seg.init(); j = 0;
    for(auto i : ord2){
        while(j<n and a[ord1[j]]<=x[i]){
            int J = ord1[j]; j++;
            seg.upd(b[J],c[J]-a[J]-b[J]);
        }
        ans[i] = min(ans[i], seg.query(0,y[i])+x[i]+y[i]);
    }

    seg.init(); j = 0;
    for(auto i : ord2){
        while(j<n and a[ord1[j]]<=x[i]){
            int J = ord1[j]; j++;
            seg.upd(b[J],c[J]+b[J]-a[J]);
        }
        ans[i] = min(ans[i], seg.query(y[i],seg.MX)+x[i]-y[i]);
    }
    
    reverse(all(ord1)); reverse(all(ord2)); 
    
    seg.init(); j = 0;
    for(auto i : ord2){
        while(j<n and a[ord1[j]]>=x[i]){
            int J = ord1[j]; j++;
            seg.upd(b[J],c[J]+a[J]-b[J]);
        }
        ans[i] = min(ans[i], seg.query(0,y[i])-x[i]+y[i]);
    }

    seg.init(); j = 0;
    for(auto i : ord2){
        while(j<n and a[ord1[j]]>=x[i]){
            int J = ord1[j]; j++;
            seg.upd(b[J],c[J]+b[J]+a[J]);
        }
        ans[i] = min(ans[i], seg.query(y[i],seg.MX)-x[i]-y[i]);
    }

    for(int i = 0; i < m; i++) cout << ans[i] << "\n";
}
