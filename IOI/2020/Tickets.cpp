#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;
#define sz(a) (int)a.size()
using vi = vector<int>;
using ll = long long;
using ar2 = array<ll,2>;
 
ll find_maximum(int k, vector<vi> A) {
    int n = sz(A), m = sz(A[0]); ll tot = 0;
    vector<vi> a(n,vi(m,-1)); vi Rw(n,0);
    priority_queue<ar2> pq = priority_queue<ar2>();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < k; j++)
            tot+=A[i][m-k+j], pq.push({-A[i][j]-A[i][m-k+j],i});
    int num = n*k/2;
    while(num--){
        auto [cost,i] = pq.top();
        Rw[i]++, tot+=cost; pq.pop();
    }
    int L = 0, R = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < Rw[i]; j++) 
            a[i][j]=L++, L-=k*(L==k);
        R=L;
        for(int j = m-k+Rw[i]; j < m; j++) 
            a[i][j]=R++, R-=k*(R==k);
    }
    allocate_tickets(a); return tot;
}
