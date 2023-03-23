#include <bits/stdc++.h>
#include "gap.h"
using namespace std;
using ll = long long;
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
const int maxn = 5e5+10;
const ll LINF = (ll)2e18;
 
ll ans=1,mn=-1,mx=-1;
 
ll findGap(int T, int n)
{
	ll s=0, t=LINF; ans=1;
	if(T==1){
		vector<ll> v; v.clear(); int x = (n+1)/2;
		while(x--) MinMax(s,t,&mn,&mx), v.pb(mn), v.pb(mx), s=mn+1, t=mx-1;
		sort(all(v));
		for(int i = 0; i < sz(v)-1; i++) 
			ans = max(ans, v[i+1]-v[i]);
		return ans;
	}
	MinMax(s,t,&mn,&mx); 
	ll x, y, i=mn, p=mn, num=(mx-mn+n-2)/(n-1); ans=num;
	for(; ; i+=num+1){
		MinMax(i,min(mx,i+num),&x,&y);
		if(x!=-1) ans = max(ans, x-p),p=y;
		if(i+num>=mx) break;
	}
	return ans;
}
