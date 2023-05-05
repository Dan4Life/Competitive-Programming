#include <bits/stdc++.h>
using namespace std;
const int mxN = (int)3e5+10;
int mx=(int)1e9, segTree[mxN*40], lazy[mxN*40];
int L[mxN*40], R[mxN*40], IND = 1, q,c;
 
void prop(int p, int l, int r){
	if(!p or l==r or lazy[p]==-1) return;
	int mid = (l+r)/2;
	if(!L[p]) L[p]=++IND;
	if(!R[p]) R[p]=++IND;
	lazy[L[p]]=lazy[R[p]]=lazy[p]; lazy[p]=-1;
	segTree[L[p]] = (mid-l+1)*lazy[L[p]];
	segTree[R[p]] = (r-mid)*lazy[R[p]];
}
 
void upd(int i, int j, int v, int p=1, int l=1, int r=mx){
	if(i>r or j<l or i>j or !p) return; prop(p,l,r);
	if(i<=l and r<=j){ segTree[p] = v*(r-l+1); lazy[p] = v; return; }
	int mid = (l+r)/2;
	if(i<=mid){
		if(!L[p]) L[p]=++IND;
		upd(i,j,v,L[p],l,mid);
	}
	if(j>mid){
		if(!R[p]) R[p]=++IND;
		upd(i,j,v,R[p],mid+1,r);
	}
	segTree[p]=segTree[L[p]]+segTree[R[p]];
}
 
int query(int i, int j, int p=1, int l=1, int r=mx){
	if(i>r or j<l or i>j or !p) return 0; prop(p,l,r);
	if(i<=l and r<=j) return segTree[p];
	int mid = (l+r)/2;
	return query(i,j,L[p],l,mid)+query(i,j,R[p],mid+1,r);
}
 
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> q; memset(lazy,-1,sizeof(lazy));
    while(q--){
        int t, x, y; cin >> t >> x >> y; x+=c, y+=c;
        if(t==1) c = query(x,y), cout << c << "\n";
        else upd(x,y,1);
    }
}
