#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
 
#define pb push_back
#define int long long
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
const int mxN = (int)2e5+10, LINF = (int)1e18;
 
vector<int> v, w[mxN];
int n, m, q, mxSz, sum;
unordered_map<int,int> ind;
int a[mxN], b[mxN], t[mxN];
int orig[3*mxN], fenwick[3*mxN+10], segTree[6*mxN];
 
void upd(int i, int v, int p=0, int l=0, int r=mxSz-1){
	if(l==r){ segTree[p]=max(segTree[p],v); return; }
	int mid = (l+r)/2; int lp = p+1, rp = p+2*(mid-l+1);
	if(i<=mid) upd(i,v,lp,l,mid);
	else upd(i,v,rp,mid+1,r);
	segTree[p] = max(segTree[lp],segTree[rp]);
}
 
int query(int i, int j, int p=0, int l=0, int r=mxSz-1){
	if(i>r or j<l or i>j) return 0;
	if(i<=l and r<=j) return segTree[p];
	int mid = (l+r)/2; int lp = p+1, rp = p+2*(mid-l+1);
	return max(query(i,j,lp,l,mid),query(i,j,rp,mid+1,r));
} 
 
void upd2(int x, int v){ for(;x<=3*mxN; x+=x&-x) fenwick[x]+=v; }
 
int sum2(int x){ int s=0;for(;x;x-=x&-x) s+=fenwick[x]; return s; }
int sum2(int l, int r){
	if(l>r) return 0;
	return sum2(r)-sum2(l-1);
}
 
main() {
	cin >> n >> q;
	for(int i = 1; i <= n; i++)
		cin >> a[i] >> b[i], v.pb(a[i]), v.pb(b[i]);
	for(int i = 1; i <= q; i++) cin >> t[i], v.pb(t[i]);
	sort(all(v)); v.erase(unique(all(v)),v.end());
	for(mxSz = 0; auto u : v) ind[u]=mxSz++, orig[mxSz-1]=u;
	for(int i = 1; i <= n; i++) a[i]=ind[a[i]],b[i]=ind[b[i]];
	for(int i = 1; i <= q; i++) t[i]=ind[t[i]], upd(t[i],i);
	for(int i = 1; i <= n; i++)
		w[query(min(a[i],b[i]),max(a[i],b[i])-1)].pb(i);
	for(int i = q; i>=0; upd2(t[i--]+1,1)){
		for(auto j : w[i]){
			int x = a[j], y = b[j];
			bool switched = (x<y and i)^((sum2(max(x,y)+1,3*mxN))%2);
			sum+=orig[switched?y:x];
		}
	}
	cout << sum << "\n";
}
