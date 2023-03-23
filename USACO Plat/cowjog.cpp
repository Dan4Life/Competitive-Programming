#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()

const int mxN = (int)5e2+10;
const int LINF = (int)1e9;

int n, T, x, y;

int32_t main() {
	ifstream cin("cowjog.in"); ofstream cout("cowjog.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> T; vector<int> v;
	for(int i = 0; i < n; i++){
		cin >> x >> y; x+=T*y; x*=-1;
		if(upper_bound(all(v),x)==end(v)) v.pb(x);
		else *upper_bound(all(v),x)=x;
	}
	cout << sz(v) << "\n";
}
