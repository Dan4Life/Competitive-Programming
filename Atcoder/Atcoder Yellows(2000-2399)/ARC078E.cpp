/*
Solved with help (partially with external help for cornercases)
Basically this: https://codeforces.com/blog/entry/53305?#comment-373508
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

bool query(int i){
    cout << "? " << i << endl;
    char x; cin >> x;
    return (x=='Y');
}

int32_t main(){
    int cur = 1;
    for(; cur<=1000000000; cur*=10) if(!query(cur)) break;
    if(query(cur)){
        for(cur=9; cur<=1000000000; cur*=10, cur+=9) 
            if(query(cur)) break; cur++;
    }
    int l = cur, r=cur*10;
    while(l<r){
        int mid = (l+r)/2;
        if(query(mid)) r=mid;
        else l=mid+1;
    }
    cout << "! " << l/10;
}