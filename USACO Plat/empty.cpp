#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define int long long
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
int a, b, n, m, x, y, tot[3000010];

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("empty.in");
    ofstream cout("empty.out");
    cin >> n >> m;
    while(m--){
        cin >> x >> y >> a >> b; a%=n,b%=n; int xd=b;
        for(int i = 1; i <= y; i++) xd+=a, xd-=(xd>=n?n:0), tot[xd]+=x;
    }
    int ans = 0, left = 0;
	for(int i = n-1; i >= 0; i--){
		left++;
		if(tot[i]>=left) tot[0]+=tot[i]-left, tot[i]=left, left=0;
		else left-=tot[i];
	}
    for(int i = 0; i < n; i++){
        ans+=tot[i]; if(ans<=i) {cout<<i;break;}
    }
}
