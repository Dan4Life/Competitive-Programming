#include "friend.h"
#include <bits/stdc++.h>
using namespace std;
int findSample(int n, int c[], int h[], int p[]){
    int ans = 0; // Mind-blown!
    for(int i = n; i>0; i--){
        if(p[i]==2) c[h[i]]=max(c[h[i]],c[i]);
        else if(p[i]==1) c[h[i]]+=c[i];
        else ans+=c[i], c[h[i]]=max(0, c[h[i]]-c[i]);
    }
    return c[0]+ans;
}
