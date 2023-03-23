#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
const int mxN = (int)1e5+10;
int n, m, a[mxN];
pair<int,int> v[mxN];
 
bool chk(int mid){
	queue<int> q; while(!q.empty()) q.pop();
	for(int i = 0; i < n; i++) q.push(v[i].se);
	for(int i = m-mid; i < m; i++){
		while(!q.empty() and q.front()>a[i]) q.pop();
		if(!q.empty()) q.pop();
		else return false;
	}
	return true;
}
 
int main() {
	cin >> n >> m;
	for(int i = 0; i < n; i++) cin >> v[i].se >> v[i].fi;
	for(int i = 0; i < m; i++) cin >> a[i];
	sort(v,v+n), sort(a,a+m);
	int l = 0, r = m;
	while(l<r){
		int mid = (l+r+1)/2;
		if(chk(mid)) l=mid;
		else r=mid-1;
	}
	cout << l;
}
