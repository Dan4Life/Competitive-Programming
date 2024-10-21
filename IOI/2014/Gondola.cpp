#include "gondola.h"
#include <bits/stdc++.h>
using namespace std;
 
int valid(int n, int a[])
{
    int sm = INT_MAX, pos = -1;
    map<int,int> M; M.clear();
    for(int i = 0; i < n; i++)
    {
        M[a[i]]++;
        if(M[a[i]]>=2)return 0;
    }
    for(int i = 0; i < n; i++)
        if(sm>a[i] and a[i]<=n)sm=a[i], pos=i;
    if(sm==INT_MAX)return 1;
    int x = n;
    while(x--){
        if(a[pos]==n and a[(pos+1)%n]<=n and a[(pos+1)%n]!=1)return 0;
        else if(a[pos]<n and a[(pos+1)%n]<=n and a[pos]!=a[(pos+1)%n]-1) return 0;
        pos++, pos%=n;
    }
    return 1;
}
 
int replacement(int n, int a[], int b[])
{
    map<int,int> M; M.clear();
    set<int> S; S.clear();
    vector<int> v; v.clear();
    int x = n, pos = 0, mx = 0;
    for(int i = 0; i < n; i++) S.insert(a[i]), mx = max(mx, a[i]);
    for(int i = 0; i < n; i++)
        if(a[i]<=n) pos = (i-a[i]+n+1)%n;
    int z = 1; while(x--) M[a[pos]]=z, z++, pos++, pos%=n;
    for(int i = n+1; i <= mx; i++){
        if(S.count(i)) v.push_back(M[i]), M[i]=i;
        else{
            int x = *S.lower_bound(i);
            v.push_back(M[x]), M[x]=i;
        }
    }
    for(int i = 0; i < (int)v.size(); i++) b[i]=v[i];
    return (int)v.size();
}
 
long long poww(long long a, long long b, long long MOD)
{
    if(b<=0)return 1ll;
    long long x = poww(a, b/2, MOD)%MOD;
    x*=x, x%=MOD;
    if(b%2)x*=a, x%=MOD;
    return x;
}
 
int countReplacement(int n, int a[])
{
    const long long MOD = 1e9+9;
    if(!valid(n, a)) return 0;
    if(*max_element(a, a+n)<=n)return 1;
    vector<int> v; v.clear();
    for(int i = 0; i < n; i++) if(a[i]>n) v.push_back(a[i]);
    sort(v.begin(), v.end());
    int m = (int)v.size();
    long long ans = 1ll;
    if(m==n)ans=n;
    for(int i = 0; i < m; i++){
        if(i==0) ans *= poww(m, v[0]-n-1, MOD);
        else ans *= poww(m-i, v[i]-v[i-1]-1, MOD);
        ans%=MOD;
    }
    return ans;
}
