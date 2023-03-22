#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
const int mxN = (int)4e4+10;
const int LINF = (int)1e18;
int n, q, a[mxN];
struct Data{
	int opt, optl, optr, optlr, optnone, sz;
} segTree[mxN*2];

Data comb(Data &a, Data &b){
	Data c; c.sz = a.sz+b.sz;
	c.optl = max(a.optlr+b.optnone,a.optl+max(b.optl,b.optnone));
	c.optr = max(a.optr+b.optr,a.optnone+max(b.optlr,b.optr));
	c.optlr = a.optl + max(b.optr,b.optlr);
	c.optlr = max(c.optlr, a.optlr+b.optr);
	c.optnone = max(a.optr+b.optnone, a.optnone+b.optl);
	c.opt = max({c.optl,c.optr,c.optlr,c.optnone});
	return c;
}

void upd(int x, int v, int p=0, int l=1, int r=n){
	if(l==r){ segTree[p] = {v,0,0,v,0,1}; return; }
	int mid = (l+r)>>1; int rp = p+(mid-l+1)*2; 
	if(x<=mid) upd(x,v,p+1,l,mid);
	else upd(x,v,rp,mid+1,r);
	segTree[p] = comb(segTree[p+1],segTree[rp]);
}

int32_t main() {
	ifstream cin("optmilk.in"); ofstream cout("optmilk.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q; int ans = 0;
	for(int i = 1; i <= n; i++)
		cin >> a[i], upd(i,a[i]);
	while(q--){
		int i, v; cin >> i >> v; a[i]=v;
		upd(i,v), ans+=segTree[0].opt;
	}
	cout << ans;
}
