#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
using ll = long long;
using vi = vector<int>;
const int mxN = (int)5e5+10;
int n, best=-1, mx=-1;
long double w, x=1, sum,cost;
long double s[mxN], q[mxN];
set<array<ll,2>> S;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> w;
	for(int i = 0; i < n; i++) cin >> s[i] >> q[i];
	vi ord(n,0); iota(all(ord),0);
	sort(all(ord),[&](int i, int j){
		return s[i]*q[j] < s[j]*q[i];
	});
	for(int i : ord){
		x = s[i]/q[i];
		S.insert({q[i],i}),sum+=q[i];
		while(sz(S) and sum*x>w) 
			sum-=(*prev(end(S)))[0], S.erase(prev(end(S)));
		if(sz(S)>mx) mx=sz(S), best=i,cost=sum*x;
		else if(sz(S)==mx and sum*x < cost) best=i, cost=sum*x;
	}
	S.clear(); sum = 0;
	for(int i : ord){
		x = s[i]/q[i];
		S.insert({q[i],i}),sum+=q[i];
		while(sz(S) and sum*x>w) 
			sum-=(*prev(end(S)))[0], S.erase(prev(end(S)));
		if(sz(S)>mx) mx=sz(S), best=i,cost=sum*x;
		else if(sz(S)==mx and sum*x < cost) best=i, cost=sum*x;
		if(best==i){
			cout << sz(S) << "\n";
			for(auto [a,b] : S) cout << b+1 << "\n";
			return 0;
		}
	}
}
