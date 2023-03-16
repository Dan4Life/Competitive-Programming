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

const int maxn = (int)1e5+10; // change when needed!
const int MOD = (int)1e9+7; // same!
const int INF = (int)2e9;
const ll LINF = (ll)4e18;
int n, q, st[maxn], en[maxn], a[maxn], segTree[maxn*4], segTree2[maxn*4], segSum[maxn*4], timer=1;
vector<int> adj[maxn];
set<pair<int,int>> M[maxn];
void update(int i, int j, int c, int p=1, int l=1, int r=n){
    if(l>r or j<l or i>r) return;
    if(i<=l and r<=j){
        segTree2[p]+=c, segSum[p]+=(r-l+1)*c;
        return;
    }
    int mid = (l+r)/2;
    update(i,j,c,p*2,l,mid);
    update(i,j,c,p*2+1,mid+1,r);
    segSum[p]=segSum[p*2]+segSum[p*2+1]+segTree2[p]*(r-l+1);
}

int query(int i, int j, int p=1, int l=1, int r=n){
    if(l>r or j<l or i>r) return 0;
    if(i<=l and r<=j) return segSum[p];
    int mid = (l+r)/2;
    return query(i,j,p*2,l,mid)+query(i,j,p*2+1,mid+1,r)+segTree2[p]*(min(j,r)-max(i,l)+1);
}

void update2(int i, int j, int c, int p=1, int l=1, int r=n){
    if(l>r or j<l or i>r) return;
    if(M[c].count({l,r})) return;
    if(i<=l and r<=j){
        while(1){
            auto itr = M[c].lower_bound({l,-1});
            if(itr!=M[c].end() and itr->fi<=r){
                update(itr->fi,itr->se,-1);
                M[c].erase(itr);
            }
            else break;
        }
        update(l,r,1); M[c].insert({l,r}); return;
    }
    int mid = (l+r)/2;
    update2(i,j,c,p*2,l,mid);
    update2(i,j,c,p*2+1,mid+1,r);
}

void dfs(int s, int p){
    st[s]=timer++; a[timer-1]=s;
    for(auto u : adj[s])
        if(u!=p) dfs(u,s);
    en[s]=timer-1;
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("snowcow.in");
    ofstream cout("snowcow.out");
    cin >> n >> q;
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    dfs(1,-1);
    while(q--){
        int t, x, c; cin >> t >> x;
        if(t==1){
            cin >> c; update2(st[x],en[x],c);
        }
        else cout << query(st[x],en[x]) << "\n";
    }
}
