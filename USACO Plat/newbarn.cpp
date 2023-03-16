#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#define int ll // delete if causing problems
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
int n, m, x, y, l, r, k, q, t;
int a[maxn], sub[maxn], par[maxn];
multiset<pair<int,int>> S[maxn];
unordered_map<int, int> dist[maxn];
vector<int> roots, adj[maxn];
bool vis[maxn], on[maxn];
char T[maxn];

int dfs2(int s, int p, int pp, int cnt){
    dist[pp][s]=dist[s][pp]=cnt;
    for(auto u : adj[s])
        if(u!=p and !vis[u])
            dfs2(u,s,pp,cnt+1);
}

int dfs(int s, int p){
	sub[s] = 1;
	for(auto u : adj[s])
		if(u!=p and !vis[u])
            sub[s]+=dfs(u, s);
	return sub[s];
}

int find_centroid(int s, int p, int sz){
    for(auto u : adj[s])
        if(u!=p and !vis[u] and sub[u]>sz/2)
            return find_centroid(u,s,sz);
    return s;
}

void centroid_decomp(int s, int p){
    int sz = dfs(s,p);
    int centroid = find_centroid(s,p,sz);
    vis[centroid] = true; par[centroid] = p;
    dfs2(centroid,p,centroid,0ll);
    for(auto u : adj[centroid])
        if(!vis[u]) centroid_decomp(u,centroid);
}

void update(int s){
    int x = s, pre=0; on[x] = 1;
    while(x!=-1){
        bool same_sub = false;
        for(auto u : S[x]){
            if(u.se!=pre) continue;
            same_sub = true;
            if(u.fi<dist[x][s]){
                S[x].erase(u);
                S[x].insert({dist[x][s],u.se});
                break;
            }
        }
        if(!same_sub){
            S[x].insert({dist[x][s],pre});
            if(sz(S[x])>2) S[x].erase(S[x].begin());
        }
        pre=x, x = par[x];
    }
}

int query(int s){
    int x = s, pre=0, ans = 0;
    while(x!=-1){
        int d = 0;
        for(auto u :S[x])
            if(u.se!=pre) d = max(d,u.fi);
        if(on[x]) ans = max(ans, dist[x][s]+d);
        pre=x, x = par[x];
    }
    return ans;
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("newbarn.in"); ofstream cout("newbarn.out");
    cin >> t; n = 0;
    for(int i = 0; i < t; i++){
        cin >> T[i] >> a[i];
        if(T[i]!='B') continue; n++;
        if(a[i]!=-1) adj[n].pb(a[i]),adj[a[i]].pb(n);
        else roots.pb(n);
    }
    for(int i = 0; i <= n; i++) vis[i]=on[i]=false;
    for(auto u : roots) centroid_decomp(u,-1);
    int xx = 0;
    for(int i = 0; i < t; i++){
        if(T[i]=='B') xx++, update(xx);
        else cout << query(a[i]) << "\n";
    }
}
