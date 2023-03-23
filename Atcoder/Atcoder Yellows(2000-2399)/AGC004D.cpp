/*
Solved by myself
First off: You can prove there will never be a solution if a[1]!=1(check what happens when there's a cycle of length>1)
Now, as the graph is functional(all nodes have exactly 1 outgoing edge), it will definitely be a rooted directed tree + an edge going from the root
In this case, node 1 is the root, and the edge going from the root comes back to itself(cycle of length 1)
So we can ignore the extra edge and take the graph as a tree when using the reverse edges
Second off: Since a[1]=1, if for other nodes, we can reach the root in x steps(x<=k), we can make it exactly k by looping in node 1 in k-x steps
This means, we have to make sure all other nodes can go to node 1 in <= k steps
It is always possible to do so as worst case scenario, we just make an edge from node x to 1

Basically, we can pick some nodes, then break the tree into a forest of smaller trees of depth at most k-1, 
where each tree is rooted at the nodes we picked. Now each rooted tree has its edge pointing to node 1
Why does this work: These nodes can reach node 1 by going to their roots in <=k-1 steps, then from root to 1, in 1 step

We can do this greedily by:
Sort all nodes by depth in decreasing order
For current node, if node is marked OR node depth <=k, continue(as we can reach node 1 from here already)
Else, keep going up the tree, to parent node. If after k-1 upward steps, we didnt reach a node that has been marked, then:
Let the current node be X. Mark 'X', change its edge to point to node 1 instead of parent thereby disconnecting the tree and choosing X
Dfs from X, marking all nodes that are not marked(Notice that depth of new tree will be at most k-1)

This makes the amortized complexity of the dfs = O(N) as we mark all nodes once. Total Complexity: O(NlogN)
Impl note: You don't need to actually change the edges, just make sure the depths dont pass k-1 and stop search when meeting a marked node 
           in the dfs(all nodes under marked nodes are marked)
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define all(a) a.begin(), a.end()

const int maxn = (int)2e5+10; 
const int INF = (int)1e9; 

int n, k, ans;
bool vis[maxn];
vector<int> r_adj[maxn];
vector<pair<int,int>> v;
int a[maxn], par[maxn], lev[maxn];

void dfs2(int s, int p=-1, int depth=-1){
    if(vis[s] or depth<0) return; vis[s]=1;
    for(auto u : r_adj[s])
        if(!vis[u]) dfs2(u,s,depth-1);
}

void dfs(int s, int p=-1){
    if(p!=-1) lev[s] = lev[p]+1;
    par[s] = p, vis[s]=1;
    for(auto u : r_adj[s])
        if(!vis[u]) dfs(u,s);
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k; vis[1]=true;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(i==1 and a[i]!=1) ans++, a[i]=1;
        else if(i!=1) r_adj[a[i]].pb(i);
    }
    dfs(1);
    for(int i = 2; i <= n; i++){
        if(lev[i]>k) v.pb({lev[i],i}); 
        vis[i]=0;
    }
    sort(all(v)); reverse(all(v));
    for(auto u : v){
        if(vis[u.second]) continue;
        int x = u.second, cnt = k-1;
        while(!vis[x] and cnt--) x=par[x];
        if(!vis[x]) dfs2(x,par[x],k-1), ans++;
    }
    cout << ans;
}