#include <bits/stdc++.h>
using namespace std;
array<int64_t,2> v[200010];
 
vector<int> find_subset(int L,int R,vector<int>w) {
    int n=w.size(),i=0,j; vector<int> A;
    while(i<n)v[i]={w[i],i},i++;
    sort(v,v+n); int64_t s = 0;
    for(i=j=0;i<n;s-=v[i++][0]){
        while(j<=n&&s<L)s+=v[j++][0];
        if(L<=s&&s<=R&&j<=n){ while(i<j)A.push_back((int)v[i++][1]); break; }
    }
    return A;
}
