#include <bits/stdc++.h>
using namespace std;
 
const int mxN = (int)2e6+10;
const int INF = (int)1e9;
 
int n, q, x[mxN];
array<int,2> seg[mxN*2], Init={INF,-INF};
 
void apply(int p, int a, int b){
    seg[p][0] = min(a, max(seg[p][0], b));
    seg[p][1] = max(seg[p][1], b);
}
 
void prop(int p, int l, int r){
    if(l==r or seg[p]==Init) return;
    int mid = (l+r)/2; int rp = p+2*(mid-l+1);
    auto [a,b] = seg[p]; // push down
    apply(p+1,a,b), apply(rp,a,b); seg[p] = Init;
}
 
void upd(int i, int j, int a, int b, int p=0, int l=0, int r=n-1){
    if(i>j or i>r or j<l) return;
    if(i<=l and r<=j){ apply(p,a,b); return; }
    prop(p,l,r);
    int mid = (l+r)/2; int rp = p+2*(mid-l+1);
    upd(i,j,a,b,p+1,l,mid); upd(i,j,a,b,rp,mid+1,r);
}
 
int query(int i, int p=0, int l=0, int r=n-1){
    if(l==r) return min(seg[p][0],max(x[l],seg[p][1]));
    prop(p,l,r);
    int mid = (l+r)/2; int rp = p+2*(mid-l+1);
    if(i<=mid) return query(i,p+1,l,mid);
    return query(i,rp,mid+1,r);
}
 
void buildWall(int N, int k, int o[], int l[], int r[], int h[], int ans[]){
    n = N; fill(seg,seg+2*n,Init);
    for(int i = 0; i < k; i++){
        int a, b;
        if(o[i]==1) a = INF, b = h[i];
        else a = h[i], b = -INF;
        upd(l[i],r[i],a,b);
    }
    for(int i = 0; i < n; i++) ans[i] = query(i);
}
