#include "shoes.h"
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
 
using ll = long long;
using vi = vector<int>;
using ar2 = array<int,2>;
 
const int mxN = (int)2e5+10;
int n, fen[mxN];
void upd(int x, int v){
	for(++x;x<mxN; x+=x&-x)fen[x]+=v;
}
 
int sum(int x){
	int s = 0;
	for(++x;x>0;x-=x&-x) s+=fen[x];
	return s;
}
 
map<int,deque<int>> v;
ll count_swaps(vector<int> a) {
	n = sz(a); v.clear(); ll ans = 0;
	set<ar2> S; S.clear();
	for(int i = 0; i < n; i++) 
		v[a[i]].pb(i), S.insert({i,a[i]});
	while(sz(S)){
		int i = (*S.begin())[0]; 
		int I = i+sum(i);
		int x = -(*S.begin())[1];
		
		int j = v[x][0];
		int J = j+sum(j);
		upd(i,-1); upd(j,-1);
		
		ans+=J-I-(x>0);
		v[x].pop_front();
		v[-x].pop_front();
		S.erase(S.begin());
		S.erase({j,a[j]});
	}
	return ans;
}
