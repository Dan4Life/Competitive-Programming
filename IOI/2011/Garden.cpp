#include "garden.h"
#include "gardenlib.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define se second
#define sz(a) (int)a.size()
 
const int mxN = (int)3e5+10;
int n, m, t;
bool vis[2][mxN];
vector<int> adj[mxN];
int mov[2][mxN], dis[2][mxN], c[2];
vector<pair<int,int>> adj2[mxN];
 
void dfs(int s, int i, int dep=0){
    dis[i][s] = dep; vis[i][s] = 1;
    for(auto u : adj[s]){
        if(u==i*n+t) c[i] = dep+1;
        if(!vis[i][u]) dfs(u,i,dep+1);
    }
}
 
void count_routes(int N, int M, int P, int R[][2], int q, int G[]){
    n = N, m = M; t = P;
    memset(dis,-1,sizeof(dis)); c[0]=c[1]=-1;
    for(int i = 0; i < m; i++){
        adj2[R[i][0]].pb({i,R[i][1]});
        adj2[R[i][1]].pb({i,R[i][0]});
    }
    for(int i = 0; i < n; i++){
        sort(begin(adj2[i]),end(adj2[i]));
        mov[0][i] = adj2[i][0].se;
        mov[1][i] = adj2[i][sz(adj2[i])>1].se;
    }
    for(int i = 0; i < n; i++){
        bool ok = (i==mov[0][mov[0][i]]);
        adj[n*ok+mov[0][i]].pb(i);
        ok = (i==mov[0][mov[1][i]]);
        adj[n*ok+mov[1][i]].pb(n+i);
    }
    dfs(t,0); dfs(n+t,1);
    for(int i = 0; i < q; i++){
        int k = G[i], tot = 0;
        for(int j = 0; j < n; j++){
            for(int l = 0; l < 2; l++){
                bool ok = 1;
                if(dis[l][j]==-1) ok=0;
                else if(c[l]==-1) ok = (dis[l][j]==k);
                else{
                    int rem = k-dis[l][j];
                    ok = (rem%c[l]==0 and rem>=0);
                }
                if(ok) {tot++; break;}
            }
        }
        answer(tot);
    }
}
