#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
const int N = (int)1e6+9;
vector<int> v;
array<int,2> adj[N*2];
int n, s=-1, T=1, ok=1, totE=1, adjH[N];
 
struct Dsu{
    bitset<N> bad;
    int deg[N], p[N], sz[N];
    int node, numBad, cycSz;
    void init(int N){
        node = -1; numBad=cycSz=0;
        for(int i = 0; i < N; i++)
            p[i]=i,sz[i]=1, bad[i]=deg[i]=0; 
    }
    int findSet(int i){ return i==p[i]?i:p[i]=findSet(p[i]); }
    void unionSet(int i, int j){
        if(i==node or j==node) return;
        deg[i]++, deg[j]++;
        int x = findSet(i), y = findSet(j);
        if(x==y){ 
            if(!bad[x]) numBad++, bad[x]=1;
            cycSz = sz[x]; return;
        }
        if(sz[x]<sz[y]) swap(x,y);
        p[y] = x; sz[x]+=sz[y];
        numBad-=bad[x]+bad[y];
        if(bad[x]||bad[y]||deg[i]>2||deg[j]>2)
            bad[x]=bad[y]=1, numBad++;
    }
} dsu[5];
 
void Init(int n_) { n = n_; for(int i=0; i<5;i++) dsu[i].init(n); }
 
void Link(int a, int b){
    adj[totE]={b,adjH[a]}; adjH[a]=totE; totE++;
    adj[totE]={a,adjH[b]}; adjH[b]=totE; totE++;
    for(int i=0;i<T;i++) dsu[i].unionSet(a,b);
    if(dsu[0].deg[a]==4 and sz(v)<=1) v.pb(a);
    if(dsu[0].deg[b]==4 and sz(v)<=1) v.pb(b);
    if(dsu[0].deg[a]==3 and s==-1) s=a;
    if(dsu[0].deg[b]==3 and s==-1) s=b;
}
 
int CountCritical(){
    if(sz(v)>=2 or dsu[0].numBad>=2) return 0;
    if(!dsu[0].numBad) return n;
    if(sz(v)==1){
        if(ok){
            dsu[T++].node = v[0]; ok=0;
            for(int i = 0; i < n; i++)
                for(int j = adjH[i]; j; j=adj[j][1])
                    if(i<adj[j][0]) dsu[1].unionSet(i,adj[j][0]);
        }
        return !dsu[1].numBad;
    }
    if(s==-1) return dsu[0].cycSz;
    if(ok){
        dsu[T++].node=s; ok = 0;
        for(int j = adjH[s]; j; j=adj[j][1]) dsu[T++].node=adj[j][0];
        for(int i = 0; i < n; i++)
            for(int j = adjH[i]; j; j=adj[j][1])
                if(i<adj[j][0]) for(int k = 1; k < T; k++) 
                    dsu[k].unionSet(i,adj[j][0]);
    }
    int ans=0;for(int i=1;i<T;i++)ans+=!dsu[i].numBad; return ans;
}
