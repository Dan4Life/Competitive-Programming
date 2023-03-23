#include <bits/stdc++.h>
using namespace std;
#define all(a) a.begin(),a.end()
#define se second
#define pb push_back
pair<int, int> a[100000];
vector<int> v;

int main() {
	iostream::sync_with_stdio(false); cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].se;
	sort(a, a + n, greater<pair<int, int>>());
	for (int i = 0; i < n; i++) {
		if (upper_bound(all(v),a[i].se)==end(v)) v.pb(a[i].se);
		else *upper_bound(all(v),a[i].se)=a[i].se;
	}
	cout << (int)v.size();
}
