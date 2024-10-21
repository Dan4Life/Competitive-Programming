#include "parks.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
using vi = vector<int>;
using ll = long long;
using ar2 = array<int,2>;
using ar3 = array<int,3>;
 
const int mxN = (int)2e5+10;
int n;
vector<ar3> A, origA;
vector<int> adj[mxN];
set<ar2> usedB, S[mxN];
 
template<int SZ> struct DSU{
    int p[SZ], sz[SZ];
    void init(int n){
        for(int i = 0; i < n; i++) p[i]=i, sz[i]=1;
    }
    
    int findSet(int i){return p[i]==i?i:p[i]=findSet(p[i]);}
    bool isSameSet(int i, int j) {return findSet(i)==findSet(j);}
    void unionSet(int i, int j){
        adj[i].pb(j); adj[j].pb(i);
        int x = findSet(i), y = findSet(j);
        if(x==y) return;
        if(sz[x] < sz[y]) swap(x,y);
        p[y]=x; sz[x]+=sz[y];
    }
    int findSz(int i) { return sz[findSet(i)]; }
};
DSU<mxN> dsu;
 
int construct_roads(vi x, vi y) {
    vi U, V, W, Z; n = sz(x); dsu.init(n);
    if (n==1){ build({}, {}, {}, {}); return 1; }
    for(int i = 0; i < n; i++){
        A.pb({x[i],y[i],i});
        origA.pb({x[i],y[i],i});
    }
    sort(all(A),[&](ar3 a, ar3 b){ 
        if(a[0]!=b[0]) return a[0]<b[0];
        return a[1]<b[1]; 
    });
    for(int i = sz(A)-1; i>=0; i--)
        S[A[i][0]].insert({A[i][1], A[i][2]});
    for(int i = 1; i < sz(A); i++){
        if(A[i][0]!=A[i-1][0]) continue;
        if(A[i][1]-A[i-1][1]==2){
            auto [x1,y1,a] = A[i-1];
            auto [x2,y2,b] = A[i];
            dsu.unionSet(a,b);
        }
    }
    for(int i = 0; i < sz(A); i++){
        auto [x1,y1,a] = A[i];
        auto itr = S[x1+2].lower_bound({y1,-1});
        if(itr==end(S[x1+2]) or (*itr)[0]!=y1) continue;
        int b = (*itr)[1]; dsu.unionSet(a,b);
    }
    if(dsu.findSz(0)!=n) return 0;
    for(auto [_1,_2,I] : A){
        int choice = ((_1+_2)%4==0);
        for(auto j : adj[I]){
            auto [x1,y1,i] = origA[I];
            auto [x2,y2,_] = origA[j];
            int ver = 0;
            if(x1==x2){
                if(y1>y2) continue;
                ver = 1;
            }
            else if(x1>x2) continue;
            if(choice){
                if(ver) x1++, y1++;
                else x1++, y1--;
            }
            else{
                if(ver) x1--, y1++;
                else x1++, y1++;
            }
            if(!usedB.count({x1,y1})){
                usedB.insert({x1,y1});
                U.pb(i); V.pb(j); W.pb(x1); Z.pb(y1);
            }
        }
    }
    build(U,V,W,Z); return 1;
}
