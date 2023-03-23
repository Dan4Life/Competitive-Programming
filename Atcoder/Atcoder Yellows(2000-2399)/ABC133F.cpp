/*
Solved by myself
There are multiple solutions in cf blog
1. Euler tour + Binary Search 
2. Sqrt Decomposition of tree (Interesting Concept)
3. LCA with preprocessing <- My solution 
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define int ll // delete if causing problems
#define pb push_back
#define fi first
#define se second
#define mod(a) (a+MOD)%MOD
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()

const int maxn = (int)2e5+10; // change when needed!
const int MOD = (int)998244353; // same!
const int INF = (int)2e9;
const ll LINF = (ll)4e18;

int n, q;
int jmp[maxn][25];
vector<int> v[maxn];
vector<tuple<int,int,int>> adj[maxn];
unordered_map<int,pair<int,int>> M[maxn];
int x[maxn], y[maxn], a[maxn], b[maxn], sum[maxn], num[maxn], tot[maxn], depth[maxn];


void dfs2(int s, int p, int sum[], int num[]){
    for(auto a : adj[s]){
        int u = get<0>(a), c = get<1>(a), w = get<2>(a);
        if(u==p) continue;
        sum[c]+=w, num[c]++, tot[u]=tot[s]+w;

        for(auto x : v[u]) M[u][x]={sum[x],num[x]};

        dfs2(u,s,sum,num);
        sum[c]-=w, num[c]--;
    }
}

void dfs(int s, int p=-1){
    jmp[s][0]=p;
    if(p!=-1) depth[s] = depth[p]+1;
    for(auto a : adj[s])
        if(get<0>(a)!=p) dfs(get<0>(a),s);
}

int getNode(int x, int k){
    for(int i = 19; i >= 0; i--)
        if(k&(1ll<<i) and x!=-1) x = jmp[x][i];
    return x;
}

int lca(int a, int b){
    if(a==b) return a;
    if(jmp[a][0]==jmp[b][0]) return jmp[a][0];
    if(depth[a] > depth[b]) swap(a,b); 
    if(depth[a]!=depth[b]) 
        return lca(getNode(b, depth[b]-depth[a]),a);
    for(int i = 19; i >= 0; i--)
        if(jmp[a][i]!=jmp[b][i] and jmp[a][i]!=-1) 
            return lca(jmp[a][i],jmp[b][i]);
}

int f(int x, int y, int z){
    return tot[x]-M[x][y].fi+M[x][y].se*z;
}

void solve()
{
    cin >> n >> q;
    for(int i = 1; i < n; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        adj[a].pb(make_tuple(b,c,d));
        adj[b].pb(make_tuple(a,c,d));
    }
    for(int j = 0; j < 20; j++)
        for(int i = 1; i <= n; i++)
            jmp[i][j]=-1;
    dfs(1);
    for(int j = 1; j < 20; j++)
        for(int i = 1; i <= n; i++)
            if(jmp[i][j-1]!=-1) jmp[i][j] = jmp[jmp[i][j-1]][j-1];

    for(int i = 0; i < q; i++){
        cin >> x[i] >> y[i] >> a[i] >> b[i];
        v[a[i]].pb(x[i]); v[b[i]].pb(x[i]);
        v[lca(a[i],b[i])].pb(x[i]);
    } 
    dfs2(1,-1,sum,num);
    for(int i = 0; i < q; i++)
        cout << f(a[i],x[i],y[i])+f(b[i],x[i],y[i])-2*f(lca(a[i],b[i]),x[i],y[i]) << "\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
}
