#include <bits/stdc++.h>
using namespace std;

//#define int long long
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
using pii = pair<int,int>;
const int maxn = (int)5e4+10;
const int maxlg = (int)20;
const int LINF = (int)1e18;

int n, q, ans;
int a[maxn], lev[maxn], jmp[maxlg][maxn];
vector<int> adj[maxn];

void dfs(int s, int p){
    if(p!=-1) lev[s] = lev[p]+1;
    jmp[0][s] = p;
    for(auto u : adj[s])
        if(u!=p) dfs(u,s);
}

int get_path(int x, int k){
    for(int i = maxlg-1; i>=0; i--)
        if(x!=-1 and (k>>i)&1) x=jmp[i][x];
    return x;
}

int lca(int a, int b){
    if(a==b) return a;
    if(jmp[0][a]==jmp[0][b]) return jmp[0][a];
    if(lev[a]>lev[b]) swap(a,b);
    b = get_path(b,lev[b]-lev[a]);
    for(int i = maxlg-1; i >= 0; i--)
        if(jmp[i][a]!=-1 and jmp[i][a]!=jmp[i][b])
            a=jmp[i][a], b=jmp[i][b];
    return lca(a,b);
}

int dfs2(int s, int p){
    int sum = a[s];
    for(auto u : adj[s])
        if(u!=p) sum+=dfs2(u,s);
    ans = max(ans, sum); return sum;
}

int32_t main() {
	ifstream cin("maxflow.in");
	ofstream cout("maxflow.out");
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q; memset(jmp,-1,sizeof(jmp));
    for(int i = 1; i < n; i++){
        int a, b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    dfs(1,-1);
    for(int i = 1; i < maxlg; i++)
        for(int j = 1; j <= n; j++)
            if(jmp[i-1][j]!=-1) 
                jmp[i][j] = jmp[i-1][jmp[i-1][j]];
    while(q--){
        int s, t, l;
        cin >> s >> t;
        l = lca(s,t);
        a[s]++, a[t]++, a[l]--;
        if(l>1) a[jmp[0][l]]--;
    }
    dfs2(1,-1); cout << ans << "\n";
}
