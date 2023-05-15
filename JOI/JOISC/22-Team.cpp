#include <bits/stdc++.h>
using namespace std;
#define fr(i) for(int i = 0; i < 3; i++)
#define V(x,y) V[x][i[x]][y]
#define pb push_back
#define all(a) a.begin(),a.end()
const int mxN = (int)1.5e5+10;
using ar = array<int,4>;
vector<ar> V[3];
bool bad[mxN];
int n;
 
int32_t main() {
	cin >> n; int i[] = {n-1,n-1,n-1};
	for(int i = 0; i < n; i++){
		int x,y,z; cin >>x>>y>>z;
		fr(j) V[j].pb({x,y,z,i});
	}
	fr(j) sort(all(V[j]),[&](ar a, ar b){ return a[j] < b[j]; });
	while(1){
		fr(j){
			while(i[j]>=0 and bad[V(j,3)]) i[j]--; 
			if(i[j]<0){cout<<-1;return 0;}
		}
		vector<int> v; v.clear();
		fr(j) v.pb(V(j,j));
		fr(I) fr(j) if(I!=j and V(I,j)==v[j]) bad[V(I,3)]=1;
		bool ok = 1; fr(j) ok&=!bad[V(j,3)];
		if(ok){ cout << v[0]+v[1]+v[2]; return 0; }
	}
}
