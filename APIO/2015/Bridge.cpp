#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define fi first
#define se second
#define pb push_back
using pii = pair<int,int>;
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
const int maxn = (int)1e5+10;
const int LINF = (int)1e18;
vector<int> v;
vector<pii> seg;
set<pii> bef,dur,aft;
int t, n, tot, ans=LINF;
int a[maxn], b[maxn];
priority_queue<int> p1; 
priority_queue<int,vector<int>,greater<int>> p2;
int sum, x;
void adjust(){
	while(!p1.empty() and sz(p1)>sz(p2)) 
		x=p1.top(), p1.pop(),p2.push(x), sum+=2*x;
	while(!p2.empty() and sz(p1)<sz(p2)) 
		x=p2.top(), p2.pop(),p1.push(x), sum-=2*x;
}
 
void add(int x){
	if(p1.empty() or p1.top()>=x) p1.push(x), sum-=x;
	else p2.push(x), sum+=x; adjust();
}
 
void chk(int a[]){
	while(!p1.empty())p1.pop(); while(!p2.empty())p2.pop(); sum=0;
	for(int i = 0; i < sz(seg); i++)
		add(seg[i].se), add(seg[i].fi-seg[i].se), a[i]=sum;
}
 
int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> t >> n; int ans = LINF;
	for(int i = 0; i < n; i++){
		char a, c; int b, d;
		cin >> a >> b >> c >> d;
		if(a==c) tot+=abs(b-d);
		else seg.pb({b+d, min(b,d)}), tot++;
	}
	sort(all(seg));
	if(!seg.empty()) chk(a), ans=a[sz(seg)-1];
	if(t==2){
		chk(a),reverse(all(seg)),chk(b);
		for(int i = 0; i < sz(seg); i++)
			ans = min(ans, a[i]+b[sz(seg)-i-2]);
	}
	if(seg.empty()) ans=0;
	cout << ans+tot;
}
