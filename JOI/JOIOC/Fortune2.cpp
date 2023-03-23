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
int a[mxN], b[mxN], t[mxN], orig[3*mxN], segTree[6*mxN];
template<class T> using ordered_set = tree<T,null_type, less<T>,
				rb_tree_tag,tree_order_statistics_node_update>;
					
ordered_set<pair<int,int>> S; 
 
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
	for(int i = q; i>=0; S.insert({t[i],i}), i--){
		for(auto j : w[i]){
			int x = a[j], y = b[j], tot = q-i;
			bool switched = (x<y and i);
			int pos = S.order_of_key({max(x,y),-1});
			pos = sz(S)-pos, switched^=pos%2;
			sum+=orig[switched?y:x];
		}
	}
	cout << sum << "\n";
}
