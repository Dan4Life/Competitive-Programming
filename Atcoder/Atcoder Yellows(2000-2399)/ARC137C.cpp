/*
Solved with editorial
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[300010];

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a, a+n); int x = a[0];
    for(int i = 0; i < n-1; i++) x+=a[i+1]-a[i]-1; //This is actually pointless, same as x = a[n-1]-n+1
    cout << (x%2 or a[n-1]>a[n-2]+1?"Alice":"Bob");
}
