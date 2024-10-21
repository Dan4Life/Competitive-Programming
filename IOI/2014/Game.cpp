#include <bits/stdc++.h>
using namespace std;
int c[1501][1501];
int n, z, p[1501], s[1501], v[1501];
 
int f(int i){return i==p[i]?i:p[i]=f(p[i]);}
 
int unionSet(int x, int y){
    fill(v,v+n,0); z=f(0);
    if(s[x]<s[y]) swap(x,y);
    p[y]=x; s[x]+=s[y]; v[x]=v[y]=1;
    for(int i = 0; i < n; z=f(i), i++)
        if(!v[z]) c[z][x]+=c[z][y], c[x][z]+=c[y][z], v[z]=1;
    return 1;
}
 
void initialize(int N){
    n = N; fill(s,s+n,1); iota(p,p+n,0);
}
 
int hasEdge(int u, int v){
    u = f(u), v = f(v), c[u][v]++, c[v][u]++;
    if(c[u][v]!=s[u]*s[v]) return 0;
    return unionSet(u,v);
}
