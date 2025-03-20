#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
using ll = long long;
using ar2 = array<ll,2>;
const int mxN = (int)5e5+10;
const ll LINF = (ll)2e18;

ll l[mxN], c[mxN];
vector<ar2> v[mxN];
ll n, U, D, s, ans, cnt=1;
ll best[mxN], pref[mxN], dp[mxN];

template<int SZ>
struct SegTree{
	ll seg[SZ*2];
	void init(){
		for(int i = 0; i < SZ*2; i++) seg[i]=-LINF;
	}
	
	void upd(int x, ll v, int p=0, int l=1, int r=SZ-1){
		if(l==r) { seg[p] = max(seg[p],v); return; }
		int mid = (l+r)/2; int rp = p+2*(mid-l+1);
		if(x<=mid) upd(x,v,p+1,l,mid);
		else upd(x,v,rp,mid+1,r);
		seg[p] = max(seg[p+1],seg[rp]);
	}
	
	ll query(int i, int j, int p=0, int l=1, int r=SZ-1){
		if(i>r or j<l or i>j) return -LINF;
		if(i<=l and r<=j) return seg[p];
		int mid = (l+r)/2; int rp = p+2*(mid-l+1);
		return max(query(i,j,p+1,l,mid),query(i,j,rp,mid+1,r));
	}
};

SegTree<mxN> seg1, seg2;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> D >> U >> l[0]; U*=-1, D*=-1;
	for(int i = 1; i < mxN; i++) dp[i]=best[i]=-LINF;
	for(int i = 0; i < n; i++){
		int t, l, m; 
		cin >> t >> l >> m; 
		v[t].pb({l,m});
	}
	v[mxN-1].pb({l[0],0});
	seg1.init(), seg2.init();
	seg1.upd(l[0], dp[0]-U*l[0]);
	seg2.upd(l[0], dp[0]+D*l[0]);
	for(int _ = 1; _ < mxN; _++){
		if(!sz(v[_])) continue; sort(all(v[_]));
		int lst = cnt; ll xd = -LINF; pref[lst-1] = 0;
		for(auto [x,m] : v[_]) l[cnt++]=x, c[cnt-1]=m; 
		for(int i = lst; i < cnt; i++) pref[i]=pref[i-1]+c[i];
		for(int i = lst; i < cnt; i++){
			dp[i] = max(dp[i], seg1.query(1,l[i])+U*l[i]+c[i]);
			dp[i] = max(dp[i], seg2.query(l[i],mxN-1)-D*l[i]+c[i]);
			best[i] = max(best[i], xd+U*l[i]+pref[i]);
			xd = max(xd, dp[i]-pref[i]-U*l[i]);
		}
		xd = -LINF;
		for(int i = cnt-1; i >= lst; i--){
			best[i] = max(best[i], xd-D*l[i]-pref[i-1]);
			xd = max(xd, dp[i]+pref[i-1]+D*l[i]);
		}
		for(int i = lst; i < cnt; i++){
			dp[i]=max(dp[i],best[i]);
			seg1.upd(l[i], dp[i]-U*l[i]);
			seg2.upd(l[i], dp[i]+D*l[i]);
		}
	}
	cout << dp[n+1] << "\n";
}
