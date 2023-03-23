/*
Solved with help (editorial)
This problem is actually standard network flow problem
We can model the grid as a bipartite graph where the ith row is in group A and the jth col is in group B
A leaf node at the {i,j} is the same as matching row i to col j with capacity of 1
A new super-source node connects to {i,j} such that s[i][j]=S with INF capacity
Node i in group A and node j in group B such that s[i][j]=T connect to a new super-sink node with INF capacity
The problem boils down to: given the new graph, find the min-cut. (Min-cut=Max-flow, so just apply max-flow algo)
Algorithm used here is Edmond-Karp's.
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)2e2+10; 
const int INF = (int)1e9; 

int n,m,S,T;
int p[maxn];
string s[maxn];
bool vis[maxn];
int adj[maxn][maxn];

int bfs(int s, int t){
    queue<int> Q({s}); 
    fill(vis,vis+maxn,0); vis[s]=1;
    fill(p,p+maxn,-1);

    while(!Q.empty()){
        int a = Q.front(); Q.pop();
        if(a==t) goto here;
        for(int i = 0; i < maxn; i++)
            if(adj[a][i] and !vis[i])
                vis[i]=1, p[i]=a, Q.push(i);
    }
    
    here:; if(!vis[t]) return 0;
    int x = INF, y = t;
    while(t!=s) x = min(x, adj[p[t]][t]), t = p[t];
    t = y;
    while(t!=s)
        adj[p[t]][t]-=x, adj[t][p[t]]+=x, t = p[t];
    return x;
}

int edmond_karp(int s, int t){
    int flow = 0, x=1;
    while(x) x = bfs(s,t), flow+=x;
    if(flow>=INF) return -1;
    return flow;
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m; S=n+m,T=S+1;
    for(int i = 0; i < n; i++){
        cin >> s[i];
        for(int j = 0; j < m; j++){
            if(s[i][j]=='o') adj[i][n+j]=adj[n+j][i]=1;
            if(s[i][j]=='S') adj[S][i]=adj[S][n+j]=INF;
            if(s[i][j]=='T') adj[i][T]=adj[n+j][T]=INF;
        }
    }
    cout << edmond_karp(S, T);
}
