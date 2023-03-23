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
#define what_is(x) cerr << #x << " is " << x << "\n"
 
const int maxn = (int)3e5+10; // change when needed!
const int MOD = (int)1e9+7; // same!
const int INF = (int)1e9;
const ll LINF = (ll)4e18;
int n, m, x, y, l, r, k, q, t;
map<int, int> M, N;
multiset<int> S, SS;
string s, ss;
vector<int> segTree, lazy;
vector<pair<int,int>> child;
int IND = 0;
 
void add_node(int v=0, int le=-1, int ri=-1, int lz=LINF){
    segTree.pb(v); child.pb({le,ri}); lazy.pb(lz);
}
 
void propagate(int p, int l, int r){
    if(p==-1 or l==r or lazy[p]==LINF) return;
    int mid = (l+r)/2;
    if(child[p].fi!=-1) lazy[child[p].fi]=lazy[p], segTree[child[p].fi]=lazy[p]*(mid-l+1);
    else child[p].fi= ++IND, add_node(lazy[p]*(mid-l+1),-1,-1,lazy[p]);
    if(child[p].se!=-1) lazy[child[p].se]=lazy[p], segTree[child[p].se]=lazy[p]*(r-mid);
    else child[p].se= ++IND, add_node(lazy[p]*(r-mid),-1,-1,lazy[p]);
    lazy[p] = LINF;
}
 
void update(int i, int j, int v, int p=0, int l=1, int r=INF){
    if(i>r or j<l or i>j or p==-1) return; propagate(p,l,r);
    if(i<=l and r<=j){ segTree[p] = v*(r-l+1); lazy[p] = v; return; }
    int mid = (l+r)/2;
    if(child[p].fi==-1) child[p].fi= ++IND, add_node();
    update(i,j,v,child[p].fi,l,mid);
    if(child[p].se==-1) child[p].se= ++IND, add_node();
    update(i,j,v,child[p].se,mid+1,r);
    int left = child[p].fi==-1?0:segTree[child[p].fi];
    int right = child[p].se==-1?0:segTree[child[p].se];
    segTree[p] = left+right;
}
 
int query(int i, int j, int p=0, int l=1, int r=INF){
    if(i>r or j<l or i>j or p==-1) return 0; propagate(p,l,r);
    if(i<=l and r<=j) return segTree[p];
    int mid = (l+r)/2;
    return query(i,j,child[p].fi,l,mid)+query(i,j,child[p].se,mid+1,r);
}
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> q; int c = 0; add_node();
    while(q--){
        int t, x, y; cin >> t >> x >> y; x+=c, y+=c;
        if(t==1){ c = query(x,y); cout << c << "\n"; }
        else update(x,y,1);
    }
}
