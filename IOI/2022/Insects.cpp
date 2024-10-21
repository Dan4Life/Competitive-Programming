#include "insects.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a), end(a)
using vi = vector<int>;
int D, inside[3000];
 
int min_cardinality(int n) {
    for(int i = 0; i < n; i++){
        move_inside(i);
        if(press_button()>1) move_outside(i);
        else inside[i]=1, D++;
    }
    if(D==1) return n;
    if(D==n) return 1;
    int l = 1, r = n/D, p=1, tot=D,ans=1;
    while(l<=r){
        int mid = (l+r)/2;
        for(int i = 0; i < n; i++)
            if(inside[i] >= mid and mid<=p)
                move_outside(i), inside[i]=0, tot--;
        vector<int> v(n,0); iota(all(v),0);
        random_shuffle(all(v));
        for(auto i : v){
            if(!!inside[i] or tot==D*mid) continue; move_inside(i);
            if(press_button()>mid) move_outside(i);
            else inside[i]=mid, tot++;
        }
        if(tot==D*mid) ans=mid,l = mid+1;
        else{
            for(int i = 0; i < n; i++) 
                if(!inside[i]) inside[i]=-1;
            r=mid-1;
        }
        p=mid;
    }
    return ans;
}
