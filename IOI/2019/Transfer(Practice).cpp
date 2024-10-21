#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
#define sz(a) a.size()
 
vi get_attachment(vi v) {
	int x = 0, y = 0; vi a;
	for(int i = 0; i < sz(v); i++) if(v[i]) x^=i+1;
	for(int i = 0; i < __lg(sz(v)+1); i++) a.push_back((x>>i)&1), y^=(x>>i)&1;
	a.push_back(y); return a;
}
 
vi retrieve(vi v){
	int x = 0, xx = 0, y = 0, n=sz(v)<99?63:255;
	for(int i = 0; i < n; i++) if(v[i]) x^=i+1;
	for(int i = 0; i < __lg(n+1); i++) if(v[n+i]) xx^=1<<i, y^=1;
	if(v.back()==y and x!=xx) v[(x^xx)-1]^=1; return vi(begin(v),begin(v)+n);
}
