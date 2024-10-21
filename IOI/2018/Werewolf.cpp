#include "werewolf.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
using vi = vector<int>;
using ll = long long;
using ar4 = array<int,4>;
const int mxN = (int)2e5+5;
const int mxLg = 19;
int n,m,q,dfs_timer;
int jmp[2][mxLg][mxN];
vector<ar4> query[mxN];
int st[2][mxN], en[2][mxN], A[2][mxN];
vi adj[mxN], euler[2], adj2[2][mxN];
 
template<int SZ> struct DSU{
    int p[SZ], root;
    void init(int n){ for(int i=0; i<n; i++) p[i]=i;}
    int findSet(int i){return p[i]==i?i:p[i]=findSet(p[i]);}
    bool isSameSet(int i, int j) {return findSet(i)==findSet(j);}
    void unionSet(int t, int i, int j){
        int x = findSet(i), y = findSet(j);
        if(x==y) return;
        adj2[t][x].pb(y); root=x, p[y]=x;
    }
};
DSU<mxN> dsu[2];
 
void dfs(int s, int p, int t){
    st[t][s] = dfs_timer++;
    euler[t].pb(s); jmp[t][0][s] = p;
    for(auto u : adj2[t][s]){
        if(u==p) continue;
        dfs(u,s,t);
    }
    en[t][s] = dfs_timer-1;
}
 
int fen[mxN];
void upd(int x, int v){for (x++;x<mxN;x+=x&-x)fen[x]+=v; }
int sum(int x){ int s=0;for(x++;x>0;x-=x&-x)s+=fen[x]; return s; }
 
vi check_validity(int _N, vi U, vi V, vi S, vi T, vi L, vi R) {
    n = _N, m = sz(U), q = sz(S);
    vi ans(q,0); memset(jmp,-1,sizeof(jmp));
    dsu[0].init(n), dsu[1].init(n);
    for(int i = 0; i < m; i++){
        int a = U[i], b = V[i];
        adj[a].pb(b), adj[b].pb(a);
    }
    for(int i = n-1; i >= 0; i--)
        for(auto u : adj[i]) if(u>i) 
            dsu[0].unionSet(0,i,u);
    for(int i = 0; i < n; i++)
        for(auto u : adj[i]) if(u<i) 
            dsu[1].unionSet(1,i,u);
    for(int t : {0,1}){
        dfs_timer = 0; dfs(dsu[t].root, -1, t);
        for(int i = 1; i < mxLg; i++)
            for(int j = 0; j < n; j++)
                jmp[t][i][j] = jmp[t][i-1][jmp[t][i-1][j]];
    }
    for(int i = 0; i < q; i++){
        int s = S[i], t = T[i], l = L[i], r = R[i];
        for(int j = mxLg-1; j>=0; j--){
            if(jmp[0][j][s]!=-1 and jmp[0][j][s]>=l) s = jmp[0][j][s];
            if(jmp[1][j][t]!=-1 and jmp[1][j][t]<=r) t = jmp[1][j][t];
        }
        query[en[1][t]].pb({st[0][s],en[0][s],i,1});
        query[st[1][t]-1].pb({st[0][s],en[0][s],i,0});
    }
    for(int j = 0; j < n; j++){
        upd(st[0][euler[1][j]],1);
        for(auto [l,r,i,t] : query[j])
            ans[i]+=(t?1:-1)*(sum(r)-sum(l-1));
    }
    for(auto &u : ans) u=!!u;
    return ans;
}
