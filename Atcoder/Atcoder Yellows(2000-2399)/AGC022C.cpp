/*
Solved with help (editorial)
To reduce to O(N^3), just use a deque as shown below to prevent re-building graph every time
*/

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
const int LINF = (int)1e9+7;

int n, m;
bool vis[55];
int a[55], b[55];
deque<int> v, adj[55];

void dfs(int s){
    vis[s]=1;
    for(auto u : adj[s])
        if(!vis[u]) dfs(u);
}

int solve(){
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= 50; j++) vis[j]=0;
        dfs(a[i]); if(!vis[b[i]]) return LINF;
    }
    int ans = 0; for(auto u : v) ans+=(1ll<<u);
    return ans;
}

void rem(int x){
    v.pop_back(); 
    for(int i = 1; i <= 50; i++)
        adj[i].pop_back();
}

void add(int x){
    v.push_front(x);
    for(int i = 1; i <= 50; i++)
        adj[i].push_front(i%x);
}

int32_t main(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    for(int i = 1; i <= 50; i++) v.push_back(i);
    for(int i = 1; i <= 50; i++)
        for(auto u : v) adj[i].pb(i%u);
    if(solve()==LINF){ cout<<-1; return 0; }
    for(int i = 50; i >= 1; i--){
        rem(i); if(solve()==LINF) add(i);
    }
    cout << solve();
}