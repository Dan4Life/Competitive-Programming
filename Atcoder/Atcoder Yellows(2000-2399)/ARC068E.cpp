/*
Solved with help (partially with editorial, but mostly without help)
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)3e5+10;
int n, m;
int l[maxn], r[maxn], fenwick[maxn], fenwick2[maxn];

void update(int x, int v, int fenwick[]){
    for(; x<maxn; x+=(x&-x)) fenwick[x]+=v;
}

int sum(int x, int fenwick[]){
    int ans = 0;
    for(; x>0; x-=(x&-x)) ans+=fenwick[x];
    return ans;
}

int32_t main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> l[i] >> r[i];
    vector<int> ord(n,0); iota(ord.begin(),ord.end(),0);
    sort(ord.begin(), ord.end(), [](int a, int b){
        if(r[a]-l[a]!=r[b]-l[b]) return r[a]-l[a]<r[b]-l[b];
        return r[a]<r[b];
    });
    int ptr = 0;
    for(int i = 1; i <= m; i++){
        while(ptr<n and r[ord[ptr]]-l[ord[ptr]]+1<i) 
            update(l[ord[ptr]],1,fenwick), update(r[ord[ptr]]+1,-1,fenwick), ptr++;
        for(int j = i; j <= m; j+=i){
            update(i,sum(j,fenwick),fenwick2);
            update(i+1,-sum(j,fenwick),fenwick2);
        }
    }
    for(int i = 0; i < n; i++) update(1,1,fenwick2), update(r[i]-l[i]+2,-1,fenwick2);
    for(int i = 1; i <= m; i++) cout << sum(i,fenwick2) << "\n";
}