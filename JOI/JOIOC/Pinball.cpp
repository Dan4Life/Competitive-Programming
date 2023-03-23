#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
#define int long long
const int mxN = (int)2e5+10, LINF = (int)1e18;
int n, m, a[mxN], b[mxN], c[mxN], d[mxN];
unordered_map<int,int> ind;
int segTree[2][4*mxN];
vector<int> v;
int mxM;
 
void upd(int i, int v, int t, int p=0, int l=0, int r=mxM){
	if(l==r){ segTree[t][p]=min(segTree[t][p],v); return; }
	int mid = (l+r)/2; int lp = p+1, rp = p+2*(mid-l+1);
	if(i<=mid) upd(i,v,t,lp,l,mid);
	else upd(i,v,t,rp,mid+1,r);
	segTree[t][p] = min(segTree[t][lp],segTree[t][rp]);
}
 
int query(int i, int j, int t, int p=0, int l=0, int r=mxM){
	if(i>r or j<l or i>j) return LINF;
	if(i<=l and r<=j) return segTree[t][p];
	int mid = (l+r)/2; int lp = p+1, rp = p+2*(mid-l+1);
	return min(query(i,j,t,lp,l,mid),query(i,j,t,rp,mid+1,r));
} 
 
main() {
	cin >> m >> n; int ans = LINF;
	for(int i = 1; i <= m; i++){
		cin >> a[i] >> b[i] >> c[i] >> d[i];
		v.pb(a[i]), v.pb(b[i]), v.pb(c[i]);
	} v.pb(1), v.pb(n);
	sort(all(v)); v.erase(unique(all(v)),v.end());
	for(int x = 0; auto u : v) ind[u]=x++; mxM = sz(v);
	for(int i = 1; i <= m; i++) a[i]=ind[a[i]],b[i]=ind[b[i]],c[i]=ind[c[i]];
	for(int i = 0; i < 2; i++) fill(segTree[i],segTree[i]+mxN*4,LINF);
	upd(0,0,0), upd(sz(v)-1,0,1);
	for(int i = 1; i <= m; i++){
		int L = query(a[i],b[i],0)+d[i]; upd(c[i],L,0); 
		int R = query(a[i],b[i],1)+d[i]; upd(c[i],R,1);
		ans = min(ans, L+R-d[i]);
	}
	cout << (ans==LINF?-1:ans) << "\n";
}
