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

const int mxN = (int)5e4+2;
const int INF = (int)1e9+2;
const ll LINF = (ll)2e18;
const int mxLg = 16;

int n, m;
vi adj[mxN];
vector<ar2> edges;
int dfs_tim, st[mxN], en[mxN], sub[mxN], rt[mxN];
int jmp[mxLg][mxN];

bool isAnc(int a, int b){
    return st[a]<=st[b] and en[a]>=en[b];
}

int lca(int a, int b){
    if(isAnc(a,b)) return a;
    if(isAnc(b,a)) return b;
    for(int i = mxLg-1; i>=0; i--)
        if(jmp[i][a] and !isAnc(jmp[i][a],b))
            a = jmp[i][a];
    return jmp[0][a];
}

void dfs(int s, int p){
    sub[s] = 1; jmp[0][s] = p;
    for(auto &u : adj[s]){
        if(u==p) continue;
        dfs(u,s); sub[s]+=sub[u];
        int x = adj[s][0]; 
        if(x==p or sub[u]>sub[x]) 
            swap(adj[s][0],u); 
    }
}

void dfsHld(int s, int p){
    if(!p) rt[s]=s,dfs_tim=1;
    st[s] = dfs_tim++;
    for(auto u : adj[s]){
        if(u==p) continue;
        rt[u]=(u==adj[s][0]?rt[s]:u);
        dfsHld(u,s);
    }
    en[s] = dfs_tim-1;
}

template<int SZ>
struct LazyMinSegTree{
    int seg[SZ*2], lz[SZ*2];

    void init(int n=SZ){
        for(int i = 0; i < n*2; i++) 
            seg[i]=lz[i]=INF;
    }

    void apply(int p, int l, int r, int v){
        seg[p] = min(seg[p], v);
        lz[p] = min(lz[p],v);
    }

    void prop(int p, int l, int r){
        if(lz[p]==INF or l==r) return;
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        apply(p+1,l,mid,lz[p]);
        apply(rp,mid+1,r,lz[p]);
        lz[p] = INF;
    }

    void upd(int i, int j, int v, int p=0, int l=1, int r=n){
        if(i>r or j<l or i>j) return; prop(p,l,r);
        if(i<=l and r<=j){ apply(p,l,r,v); return;  }
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        upd(i,j,v,p+1,l,mid); upd(i,j,v,rp,mid+1,r);
        seg[p] = min(seg[p+1],seg[rp]);
    }

    int query(int i, int j, int p=0, int l=1, int r=n){
        if(i>r or j<l or i>j) return INF; prop(p,l,r);
        if(i<=l and r<=j) return seg[p];
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        return min(query(i,j,p+1,l,mid),query(i,j,rp,mid+1,r));
    }
};
LazyMinSegTree<mxN> seg;

void upd(int a, int b, int c){
    if(st[a]>st[b]) swap(a,b);
    int x = b;
    while(rt[a]!=rt[b]){
        seg.upd(st[rt[b]],st[b],c);
        b = jmp[0][rt[b]];
    }
    seg.upd(st[a]+1,st[b],c);
}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("disrupt.in");
    ofstream cout("disrupt.out");
    cin >> n >> m;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; 
        edges.pb({a,b}); adj[a].pb(b); adj[b].pb(a);
    }
    dfs(1,0); dfsHld(1,0); seg.init();
    for(int i = 1; i < mxLg; i++)
        for(int j = 1; j <= n; j++)
            jmp[i][j] = jmp[i-1][jmp[i-1][j]];
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c;
        int z = lca(a,b); upd(z,a,c); upd(z,b,c);
    }
    for(int i = 0; i < n-1; i++){
        auto [a,b] = edges[i];
        if(st[a]>st[b])swap(a,b);
        int ans = seg.query(st[b],st[b]);
        cout << (ans==INF?-1:ans) << "\n";
    }
}
