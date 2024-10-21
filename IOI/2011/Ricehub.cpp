#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
ll pref[100010];
ll sum(int i, int j){ return pref[j+1]-pref[i]; }
 
int besthub(int n, int m, int a[], ll b)
{
    pref[0] = 0; int ans = 0;
    for(int i = 0; i < n; i++)
        pref[i+1] = pref[i]+a[i];
    for(int i = 0; i < n; i++){
        int l = i, r = n-1;
        while(l<r){
            int mid = (l+r+1)/2; int j = mid;
            int med = (i+mid)/2; ll mn = (ll)4e18;
            for(int x = med-1; x <= med+1; x++){
                if(x<i or x>j) continue;
                ll sum1 = (ll)a[x]*(x-i+1)-sum(i,x);
                ll sum2 = sum(x+1,j)-(ll)a[x]*(j-x);
                mn = min(mn, sum1+sum2);
            }
            if(mn<=b) l=mid;
            else r = mid-1;
        }
        ans = max(ans, l-i+1);
    }
    return ans;
}
