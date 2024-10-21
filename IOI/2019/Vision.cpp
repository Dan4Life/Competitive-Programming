#include "vision.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
using ll = long long;
using vi = vector<int>;
using ar2 = array<int,2>;
const int mxN = 205;
int n, m;
vi diag[2][mxN*2];
 
int atLeast(int n, int m, int K){
	for(int i = 0; i <= n+m; i++) 
		diag[0][i].clear(), diag[1][i].clear();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			diag[0][i+j].pb(i*m+j);
			diag[1][i-j+m-1].pb(i*m+j);
		}
	}
	vi pos, x[2], y[2]; pos.clear();
	for(int i : {0,1}) x[i].clear(), y[i].clear();
	for(int i = 0; i < n+m-1; i++){
		x[0].pb(add_or(diag[0][i]));
		y[0].pb(add_or(diag[1][i]));
		x[1].pb(add_or(x[0]));
		y[1].pb(add_or(y[0]));
		if(i>=K){
			pos.pb(add_and({x[0][i],x[1][i-K]}));
			pos.pb(add_and({y[0][i],y[1][i-K]}));
		}
	}
	return add_or(pos);
}
 
void construct_network(int n, int m, int K) {
	if(K==n+m-2) atLeast(n,m,K);
	else add_xor({atLeast(n,m,K),atLeast(n,m,K+1)});
}
