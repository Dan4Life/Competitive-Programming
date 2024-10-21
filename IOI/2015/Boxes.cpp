#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll delivery(int n, int k, int l, int a[])
{
    ll left[n+1], right[n+1];
    left[0]=right[0]=0ll;
    for(int i = 1; i <= n; i++)
    {
        left[i] = 2*a[i-1];
        if(i>=k)left[i] += left[i-k];
    } reverse(a, a+n);
    for(int i = 1; i <= n; i++)
    {
        right[i] = 2*(l-a[i-1]);
        if(i>=k)right[i]+=right[i-k];
    }
    ll ans = 1e18;
    for(int i = 0; i <= n; i++)
        ans = min(ans, left[i]+right[n-i]);
    for(int i = 0; i <= n-k; i++)
        ans = min(ans, left[i]+right[n-i-k]+l);
    return ans;
}
