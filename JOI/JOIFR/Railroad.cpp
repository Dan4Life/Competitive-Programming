#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for (int i = (int)(a); i < (int)(n); i++)
#define ll long long
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<char> vc;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;
//Not my code, mindsolved this tho.
int main() {
    int N, M;
    cin >> N >> M;
    vl A(N), B(N), C(N), ent(N), plan(M);
    rep(i, 0, M) cin >> plan[i];
    rep(i, 0, N) cin >> A[i] >> B[i] >> C[i];
    
    ll mi, ma;
    rep(i, 0, M - 1) {
        mi = min(plan[i], plan[i + 1]);
        ma = max(plan[i], plan[i + 1]);
        ent[mi - 1]++;
        ent[ma - 1]--;
    }
    
    ll ans = 0;
    rep(i, 1, N) ent[i] += ent[i - 1];
    
    rep(i, 0, N) ans += min(ent[i] * A[i], ent[i] * B[i] + C[i]);
    cout << ans << endl;
}
