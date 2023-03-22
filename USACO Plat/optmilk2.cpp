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
struct Data{ int opt[4]; } segTree[mxN*2];

Data comb(Data &a, Data &b){
	Data c;
	for(int i = 0; i < 4; i++){ c.opt[i]=0;
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				if(j&1 and k&2) continue;
				if((i^j)&2 or ((i^k)&1)) continue;
				c.opt[i] = max(c.opt[i], a.opt[j]+b.opt[k]);
			}
		}
	}
	return c;
}

void upd(int x, int v, int p=0, int l=1, int r=n){
	if(l==r){ 
		fill(segTree[p].opt,segTree[p].opt+4,0);
		segTree[p].opt[3]=v; return; 
	}
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
		int i, v; cin >> i >> v; a[i]=v; upd(i,v); 
		ans+=*max_element(segTree[0].opt,segTree[0].opt+4);
	}
	cout << ans;
}
