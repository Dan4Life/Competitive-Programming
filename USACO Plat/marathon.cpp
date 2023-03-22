#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
const int mxN = (int)1e5+10;
int n, q, s1[mxN*2], s2[mxN*2];
pair<int,int> a[mxN];

void upd(int x, int v, int segTree[], int t=0, int p=0, int l=1, int r=n){
	if(l==r){ segTree[p]=v; return; }
	int mid = (l+r)>>1; int rp = p+(mid-l+1)*2;
	if(x<=mid) upd(x,v,segTree,t,p+1,l,mid);
	else upd(x,v,segTree,t,rp,mid+1,r);
	if(!t) segTree[p] = segTree[p+1]+segTree[rp];
	else segTree[p] = max(segTree[p+1],segTree[rp]);
}

int query(int i, int j, int segTree[], int t=0, int p=0, int l=1, int r=n){
	if(i>r or j<l or i>j) return 0;
	if(i<=l and r<=j) return segTree[p];
	int mid = (l+r)>>1; int rp = p+(mid-l+1)*2;
	if(t) return max(query(i,j,segTree,t,p+1,l,mid),query(i,j,segTree,t,rp,mid+1,r));
	return query(i,j,segTree,t,p+1,l,mid)+query(i,j,segTree,t,rp,mid+1,r);
}

int dis(int i, int j){
	return abs(a[i].fi-a[j].fi)+abs(a[i].se-a[j].se);
}

int32_t main() {
	ifstream cin("marathon.in"); ofstream cout("marathon.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		cin >> a[i].fi >> a[i].se;
		if(i>1) upd(i-1,dis(i-1,i),s1);
		if(i>2) upd(i-2,dis(i-2,i-1)+dis(i-1,i)-dis(i-2,i),s2,1);
	}
	while(q--){
		char t; int l, r, i; cin >> t;
		if(t=='U'){
			cin >> i >> l >> r; a[i] = mp(l,r); 
			if(i>1) upd(i-1,dis(i,i-1),s1);
			if(i<n) upd(i,dis(i,i+1),s1);
			if(i>2) upd(i-2,dis(i-2,i-1)+dis(i-1,i)-dis(i-2,i),s2,1);
			if(i>1 and i<n) upd(i-1,dis(i-1,i)+dis(i,i+1)-dis(i-1,i+1),s2,1);
			if(i<=n-2) upd(i,dis(i,i+1)+dis(i+1,i+2)-dis(i,i+2),s2,1);
		}
		else{
			cin >> l >> r; r--;
			cout << query(l,r,s1)-query(l,r-1,s2,1) << "\n";
		}
	}
}
