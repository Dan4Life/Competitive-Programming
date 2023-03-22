#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
const int mxN = (int)5e5+10;
const int LINF = (int)1e18;
int n, q, ans, a[mxN], lazy[mxN*2];
struct Data{ int pre,suf,ans,sz; } segTree[mxN*2];

void prop(int p, int l, int r){
	if(l==r or lazy[p]==2) return;
	int mid = (l+r)>>1; int rp = p+2*(mid-l+1);
	lazy[p+1]=lazy[rp]=lazy[p]; lazy[p] = 2;
	if(!lazy[p+1]){
		segTree[p+1] = {mid-l+1,mid-l+1,mid-l+1,mid-l+1};
		segTree[rp] = {r-mid,r-mid,r-mid,r-mid};
	}
	else{
		segTree[p+1] = {0,0,0,mid-l+1};
		segTree[rp] = {0,0,0,r-mid};
	}
}

Data comb(Data &a, Data &b){
	Data c; c.sz=a.sz+b.sz;
	c.pre = a.pre; c.suf = b.suf;
	if(a.pre==a.sz) c.pre=a.pre+b.pre;
	if(b.suf==b.sz) c.suf=b.suf+a.suf;
	c.ans = max({a.ans,b.ans,a.suf+b.pre});
	return c;
}

void upd(int i, int j, int v, int p=0, int l=1, int r=n){
	if(i>r or j<l or i>j) return; prop(p,l,r);
	if(i<=l and r<=j){
		if(!v) segTree[p] = {r-l+1,r-l+1,r-l+1,r-l+1};
		else segTree[p] = {0,0,0,r-l+1};
		lazy[p]=v; return;
	}
	int mid = (l+r)>>1; int rp = p+2*(mid-l+1);
	upd(i,j,v,p+1,l,mid),upd(i,j,v,rp,mid+1,r);
	segTree[p] = comb(segTree[p+1],segTree[rp]);
}

int findIndex(int v, int p=0, int l=1, int r=n){
	if(l==r) return l; prop(p,l,r);
	int mid = (l+r)>>1; int rp = p+2*(mid-l+1);
	if(segTree[p+1].ans>=v) return findIndex(v,p+1,l,mid);
	if(segTree[p+1].suf+segTree[rp].pre>=v) return mid-segTree[p+1].suf+1;
	return findIndex(v,rp,mid+1,r);
}

int32_t main() {
	ifstream cin("seating.in"); ofstream cout("seating.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q; fill(lazy,lazy+2*mxN,2); upd(1,n,0);
	while(q--){
		char t; cin >> t; int l,r;
		if(t=='A'){
			int p,i; cin >> p;
			if(segTree[0].ans<p) ans++;
			else i = findIndex(p), upd(i,i+p-1,1);
		}
		else cin >> l >> r, upd(l,r,0);
	}
	cout << ans;
}
