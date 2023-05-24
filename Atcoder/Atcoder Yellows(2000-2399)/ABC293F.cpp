/*
Solved by myself
The problem can be restated as follows:
Find all xs such that there is a sequence 0 <= a < b < c... such that x^a + x^b + x^c.... = n
Notice that the powers get big quickly, so we can bruteforce all subsets of powers <=9 (9 is arbitrary)
We also need to find the smaller numbers that require huge powers >9 (roughly < 100)
That's easy with normal bruteforce, then we remove duplicates.
*/

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
#define all(a) a.begin(),a.end()

void solve(){
	int n; cin >> n; vector<int> ans; ans.clear();
	for(int i = 2; i <= 100; i++){
		int xd = n, ok = 1; 
		while(xd) ok&=xd%i < 2, xd/=i;
		if(ok) ans.pb(i);
	}
	for(int mask = 1; mask < (1<<9); mask++){
		vector<int> v; v.clear();
		for(int i = 0; i < 9; i++)
			if((mask>>i)&1) v.pb(i);
		int l = 1, r = n;
		while(l<r){
			int mid = (l+r+1)/2, sum=0, ok=1;
			for(auto u : v){
				int xd = 1; 
				for(int i = 1; i <= u and ok; i++){
					if(xd>n/mid) ok=0;
					else xd*=mid;
				}
				if(sum>n-xd) ok = 0;
				else sum +=xd;
				if(!ok) break;
			}
			if(!ok) r=mid-1;
			else l=mid;
		}
		int sum = 0;
		for(auto u : v){
			int xd = 1; 
			for(int i = 1; i <= u; i++) xd*=l;
			sum+=xd;
		}
		if(sum==n and l!=1) ans.pb(l);
	}
	sort(all(ans)); ans.erase(unique(all(ans)),end(ans));
	cout << (int)ans.size() << "\n";
}

int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) solve();
}
