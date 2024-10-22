#include <bits/stdc++.h>
using namespace std;
#define sz(a) (int)a.size()
const int mxN = (int)1e5+10;
using ll = long long;
int n, p, w; ll ans;
vector<int> adj[mxN];
int c[mxN],l[mxN],su[mxN];
multiset<pair<int,int>> S[mxN];

void dfs(int s, int p){
    su[s]=c[s]; S[s].insert({c[s],s});
    for(auto u : adj[s]){
        if(u==p) continue; dfs(u,s);
        if(sz(S[s])<sz(S[u])) S[s].swap(S[u]),swap(su[s],su[u]);
        for(auto v : S[u]){
            S[s].insert(v),su[s]+=v.first;
            while(su[s]>w) su[s]-=(--end(S[s]))->first,S[s].erase(--end(S[s]));
        }
    }
    ans = max(ans, (ll)l[s]*sz(S[s]));
}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> w; int s =-1;
    for(int i = 1; i <= n; i++){
        cin >> p >> c[i] >> l[i];
        if(p==0) s=i;
        else adj[p].push_back(i);
    }
    dfs(s,-1); cout << ans;
}
