#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
const int mxN = (int)1e5+10;
int n;
double a[mxN], pr[mxN], suf[mxN];

bool chk(double x){
    for(int i = 1; i <= n; i++)
        pr[i]=pr[i-1]+a[i]-x; suf[n] = -1e9;
    for(int i = n-1; i >= 1; i--) suf[i] = max(suf[i+1], pr[i]);
    for(int l = 1; l < n-1; l++)
        if(suf[l+1] >= pr[n]+pr[l]) return 1;
    return 0;
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("sabotage.in");
    ofstream cout("sabotage.out");
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    double l = 0, r = 1e9;
    for(int itr = 0; itr < 300; itr++){
        double mid = (l+r)/2;
        if(chk(mid))r=mid;
        else l=mid;
    }
    cout << fixed << setprecision(3) << l;
}
