/*
Solved with editorial
Basically, first create any forest of spanning trees (cuz extra edges that form a cycle are redundant)
For each tree in the forest, fix the nodes in decreasing order of depth to ensure fixing leaves first
If any node cannot be fixed, it means they are not in the same tree and therefore ans = -1
Why do we do it in this order? This ensures we don't reuse any edge more times than necessary
As we fix each position, the edge for that leave will definitely never be used again
So in worst case for a tree, we use all edges in (M+M-1+M-2....+1) times < M*(M-1)/2
If there are multiple trees, the total sum will definitely be < total_M *(total_M-1)/2
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define pii pair<int,int>
const int maxn = (int)1e3+10;
int n, m;
int a[maxn], p[maxn], level[maxn];
vector<int> adj[maxn];
int ind[maxn][maxn];
vector<int> ans;
vector<pii> swaps; 

int findSet(int i){return p[i]==i?i:p[i]=findSet(p[i]);}
bool isSameSet(int i, int j){return findSet(i)==findSet(j); }
void unionSet(int i, int j){
    int x = findSet(i), y = findSet(j);
    if(x==y) return; p[y] = x;
}

bool dfs(int s, int t, int p=-1, int depth=0){
    if(s==t) return true;
    level[s]=depth;
    for(auto u : adj[s]){
        if(u==p) continue; 
        if(dfs(u,t,s,depth+1)){
            swaps.pb({u,s});
            return true;
        }
    }
    return false;
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i], p[i]=i;
    cin >> m;
    for(int i = 1; i <= m; i++)
    {
        int a, b; cin >> a >> b;
        if(isSameSet(a,b)) continue;  //adding this edge causes a cycle and is therfore redundant
        unionSet(a,b);
        adj[a].pb(b), adj[b].pb(a); 
        ind[a][b] = ind[b][a] = i;
    }
    for(int i = 1; i <= n; i++) dfs(i,-1,-1,0);
    vector<int> order(n,0); iota(order.begin(),order.end(),1);
    sort(order.begin(), order.end(), [&](int a, int b){
        return level[a]>level[b];
    });
    for(auto i : order){ //sorted in order of depth to enable leafs processed first
        int x = -1; swaps.clear(); // x is the position we want to swap 'i' with
        for(int j = 1; j <= n; j++) if(a[j]==i) x=j;
        if(!dfs(i,x)){ cout<<-1; return 0; } //not in same connected component
        for(auto u : swaps)
            swap(a[u.fi],a[u.se]),
            ans.pb(ind[u.fi][u.se]);   
    }
    cout << (int)ans.size() << "\n";
    for(auto u : ans) cout << u << " ";
}
