#include "horses.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mxN = (int)5e5+10;
const int MOD = (int)1e9+7;
struct Data{ double sum, ans; int i; } segTree[2*mxN];
ll n, X[mxN], Y[mxN], segTree2[2*mxN];
 
Data comb(Data &a, Data &b){
	Data c = {a.sum+b.sum,a.ans,a.i};
	if(a.ans <= a.sum+b.ans) c.i=b.i;
	c.ans = max(a.ans, a.sum+b.ans);
	return c;
}
 
void upd2(int x, ll v, int p=0, int l=0, int r=n-1){
	if(l==r){ segTree2[p] = v; return; }
	int mid = (l+r)/2; int rp = p+2*(mid-l+1);
	if(x<=mid) upd2(x,v,p+1,l,mid);
	else upd2(x,v,rp,mid+1,r);
	segTree2[p] = (segTree2[p+1]*segTree2[rp])%MOD;
}
 
ll query(int i, int j, int p=0, int l=0, int r=n-1){
	if(i>r or j<l or i>j) return 1ll;
	if(i<=l and r<=j) return segTree2[p];
	int mid = (l+r)/2; int rp = p+2*(mid-l+1);
	return (query(i,j,p+1,l,mid)*query(i,j,rp,mid+1,r))%MOD;
}
 
void upd(int x, ll v, int p=0, int l=0, int r=n-1){
	if(l==r){
		segTree[p] = {log(v),log(v)+log(Y[x]),x};
		X[x] = v; upd2(x,v); return;
	}
	int mid = (l+r)/2; int rp = p+2*(mid-l+1);
	if(x<=mid) upd(x,v,p+1,l,mid);
	else upd(x,v,rp,mid+1,r);
	segTree[p] = comb(segTree[p+1],segTree[rp]);
}
 
int init(int N, int x[], int y[]) {
	n = N;
	for(int i = 0; i < n; i++)
		X[i] = x[i], Y[i] = y[i], upd(i,X[i]);
	int i = segTree[0].i;
	return (query(0,i)*Y[i])%MOD;
}
 
int updateX(int x, int v) {
	upd(x,v);
	int i = segTree[0].i;
	return (query(0,i)*Y[i])%MOD;
}
 
int updateY(int x, int v) {
	Y[x] = v; upd(x,X[x]);
	int i = segTree[0].i;
	return (query(0,i)*Y[i])%MOD;
}
