#include <bits/stdc++.h>
using namespace std;
#define int long long
#define sz(a) (int)a.size()
const int mxN = (int)3e3+10;
int n, m, k, A, B, C, T, ans, S[mxN];
priority_queue<int> pq;
int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k >> A >> B >> C >> T; k-=m;
	for(int i = 0; i < m; i++) cin >> S[i];
	for(int i = 0; i < m; i++){
		int cost = (S[i]-1) * B; if(cost>T) break;
		ans++; if(i==m-1) break; int k2 = k;
		for(int l = S[i]; l < S[i+1] and k2; l++){
			int cost2 = cost+(l-S[i])*C; if(cost2>T) break;
			k2-=(l>S[i]);
			int As = min(S[i+1]-l-1, (T-cost2)/A); As++;
			if(l==S[i]) ans+=As-1;
			else pq.push(As);
			l+=As-1;
		}
	} 
	while(sz(pq) and k--) ans+=pq.top(), pq.pop();
	cout << ans-1;
}
