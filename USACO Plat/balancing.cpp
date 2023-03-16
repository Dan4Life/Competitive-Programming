#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
const int mxN = (int)1e6+4;
const int INF = (int)1e9;

int n;
pair<int,int> v[mxN];

struct fenwick{
	int n; vector<int> fen;
	void init(int N){  n=N; fen.resize(N,0); }
	void upd(int x, int v){ for(;x<n; x+=x&-x) fen[x]+=v; }
	int sum(int x){ int s=0; for(;x;x-=x&-x) s+=fen[x]; return s; }
	int sum(int l, int r){ return l<=r?sum(r)-sum(l-1):0; }
} f1, f2;

int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	ifstream cin("balancing.in");
	ofstream cout("balancing.out");
	cin >> n; int ans = mxN; 
	f1.init(mxN), f2.init(mxN);
	for(int i = 0; i < n; i++)
		cin >> v[i].fi >> v[i].se, f2.upd(v[i].se,1);
	sort(v,v+n); int j = 0;
	for(int i = 0; i < mxN; i+=2){
		while(j<n and v[j].fi<i)
			f1.upd(v[j].se,1), f2.upd(v[j].se,-1),j++;
		int Lside = f1.sum(mxN-1);
		int Rside = n-Lside, l = 0, r = mxN-1;
		//binsearch on derivative
		while(r-l>4){
			int mid = (l+r)/2;
			int xl = f1.sum(mid), yl = f2.sum(mid);
			int xr = Lside-xl, yr = Rside-yl;
			bool down;
			if(max(xl,xr)<max(yl,yr)) down=(yl>yr);
			else down = (xl>xr);
			if(down) r=mid+1;
			else l=mid-1;
		}
		
		for(int i = l; i <= r; i++){
			int x = f1.sum(i), y = f2.sum(i);
			ans = min(ans, max({x,Lside-x,y,Rside-y}));
		}
	}
	cout << ans;
}
