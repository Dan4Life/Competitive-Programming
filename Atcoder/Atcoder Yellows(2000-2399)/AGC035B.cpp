/*
Solved with editorial
ngl this constructive solution was genius as fuck
AGCs are goated
*/

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxn = (int)1e5+10;

int n, m;
vector<int> adj[maxn];
int out[maxn], p[maxn];
vector<pair<int,int>> ans;

int findSet(int i){return p[i]==i?i:p[i]=findSet(p[i]);}
bool isSameSet(int i, int j){return findSet(i)==findSet(j); }
void unionSet(int i, int j){
    int x = findSet(i), y = findSet(j);
    if(x==y) return; p[y] = x;
}

void dfs(int s, int p=-1){
    for(auto u : adj[s]) if(u!=p) dfs(u,s);
    if(p!=-1){
        if(out[s]%2) ans.pb({s,p}), out[s]++;
        else ans.pb({p,s}), out[p]++;
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) p[i] = i;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        if(isSameSet(a,b)) ans.pb({a,b}), out[a]++;
        else unionSet(a,b), adj[a].pb(b), adj[b].pb(a);
    }
    if(m%2){ cout<<-1; return 0; } dfs(1);
    for(auto u : ans) cout << u.first << " " << u.second << "\n";
}
