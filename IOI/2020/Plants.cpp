#include "plants.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a), end(a)
using ar2 = array<int,2>;
const int mxN = (int)2e5+10;
const int mxLg = (int)19;
const int INF = (int)1e9;
int n, k, h[mxN*2];
int jmp[2][mxLg][mxN*2];
 
template<class T, int SZ> struct SegTree{
    T seg[SZ], lzy[SZ];
    
    void init(){ memset(seg,0,sizeof(seg)); memset(lzy,0,sizeof(lzy)); }
    
    void prop(int p, int l, int r){
        if(!lzy[p] or l==r) return;
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        seg[p+1]+=lzy[p]; seg[rp]+=lzy[p];
        lzy[p+1]+=lzy[p]; lzy[rp]+=lzy[p]; lzy[p]=0;
    }
    
    void upd(int i, int j, int v, int p=0, int l=0, int r=n-1){
        if(i>r or j<l or i>j) return; prop(p,l,r);
        if(i<=l and r<=j){ seg[p]+=v; lzy[p]+=v; return; }
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        if(i<=mid) upd(i,j,v,p+1,l,mid);
        if(j>mid) upd(i,j,v,rp,mid+1,r);
        seg[p] = min(seg[p+1],seg[rp]);
    }
    
    int findFirstMin(int i, int j, int p=0, int l=0, int r=n-1){
        if(i>r or j<l or i>j) return -1; prop(p,l,r);
        if(l==r) return l; 
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        if(i>mid) return findFirstMin(i,j,rp,mid+1,r);
        if(j<=mid) return findFirstMin(i,j,p+1,l,mid);
        if(query(i,mid)==query(i,j)) return findFirstMin(i,j,p+1,l,mid);
        return findFirstMin(i,j,rp,mid+1,r);
    }
    
    T query(int i, int j, int p=0, int l=0, int r=n-1){
        if(j<l or i>r or i>j) return INF; prop(p,l,r);
        if(i<=l and r<=j) return seg[p];
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        return min(query(i,j,p+1,l,mid), query(i,j,rp,mid+1,r)); 
    }
};
const int mxSeg = 2*mxN;
SegTree<int,mxSeg> segTree;
 
int cur;
void solve(int i){
    bool ok = 1;
    while(ok){
        ok = 0;
        if(i<k){
            int i1 = segTree.findFirstMin(n-k+i,n-1);
            if(i1!=-1 and !segTree.query(i1,i1)) solve(i1), ok=1;
        }
        int i1 = segTree.findFirstMin(max(0,i-k),i-1);
        if(i1!=-1 and !segTree.query(i1,i1)) solve(i1), ok=1;
    }
    if(i<k){
        segTree.upd(0,i-1,-1);
        segTree.upd(n-k+i,n-1,-1);
    }
    else segTree.upd(i-k,i-1,-1);
    segTree.upd(i,i,INF); h[i]=cur--;
}
 
void init(int K, vector<int> r){
    n = sz(r); k=K-1; cur = n; 
    memset(jmp,-1, sizeof jmp);
    segTree.init(); 
    for(int i = 0; i < n; i++) 
        segTree.upd(i,i,r[i]);
    while(!segTree.query(0,n-1)) 
        solve(segTree.findFirstMin(0,n-1));
    for(int i = n; i < 2*n; i++) h[i] = h[i-n];
    set<ar2> S; int j = 0;
    for(int i = 0; i < 2*n; i++){
        while(j<2*n and abs(i-j)<=k)
            S.insert({h[j],j}),j++;
        S.erase({h[i],i});
        auto itr = S.lower_bound({h[i],i});
        if(itr!=end(S)) jmp[0][0][i]=(*itr)[1];
        if(itr!=begin(S)) jmp[1][0][i]=(*prev(itr))[1];
    }
    for(int t = 0; t < 2; t++)
        for(int i = 1; i < mxLg; i++)
            for(int j = 0; j < 2*n; j++)
                if(jmp[t][i-1][j]!=-1) jmp[t][i][j]
                    =jmp[t][i-1][jmp[t][i-1][j]];
}
 
int comp(int x, int y, bool g){
    for(int i = mxLg-1; i>=0; i--){
        int j = jmp[g][i][x];
        if(j!=-1 and j<=y) x=j;
    }
    return y-x<=k and (g?h[x]>=h[y]:h[x]<=h[y]);
}
 
int compare_plants(int x, int y){
    if(comp(x,y,1) or comp(y,x+n,0)) return 1;
    if(comp(x,y,0) or comp(y,x+n,1)) return -1;
    return 0;
}
