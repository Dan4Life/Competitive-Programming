#include <bits/stdc++.h>
using namespace std;
int n, x, y, st;

bool query(int x, int y){
    if(x<1 or y<1 or x>n or y>n) return false;
    cout << "examine " << x << " " << y << endl;
    string s; cin >> s; return s[0]=='t';
}

int32_t main(){
    cin >> n >> x >> y;
    for(int i = 0; i < 3; i++){
        st = 1<<30;
        while(st){
            if(query(x-st,y))x-=st;
            st>>=1;
        }
        st = 1<<30;
        while(st){
            if(query(x,y-st))y-=st;
            st>>=1;
        }
    }
    st = 1<<30;
    while(st){
        if(query(x-st,y-st))x-=st,y-=st;
        st>>=1;
    }
    int X = x, Y = y;
    st = 1<<30;
    while(st){
        if(query(x+st,y+st))x+=st,y+=st;
        st>>=1;
    }
    int dis = x-X+1, ok, m;
    if(dis%5==0){
        m = dis/5; ok = 1;
        for(int i = 1; i <= 4; i++)
            ok&=query(X+i*m,Y+i*m);
    }
    if(!ok and dis%3==0){
        m = dis/3; ok = 1;
        for(int i = 1; i <= 2; i++)
            ok&=query(X+i*m,Y+i*m);
    }
    if(!ok) m = dis;    
    while(query(X-m,Y)) X-=m;
    while(query(X,Y-m)) Y-=m;
    cout << "solution " << X+2*m+m/2 << " " << Y+2*m+m/2 << endl;
}
