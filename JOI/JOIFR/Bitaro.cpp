#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define all(a) a.begin(),a.end()
const int mxN = (int)3e3+10;
string a[mxN];
int n, m, ans, r[mxN][mxN], c[mxN][mxN];
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        for(int j = m-1; j>=0; j--)
            r[i][j]=r[i][j+1]+(a[i][j]=='O');
    }
    for(int j = 0; j < m; j++)
        for(int i = n-1; i>=0; i--)
            c[i][j]=c[i+1][j]+(a[i][j]=='I');
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(a[i][j]=='J') ans+=r[i][j+1]*c[i+1][j];
    cout << ans;
}
