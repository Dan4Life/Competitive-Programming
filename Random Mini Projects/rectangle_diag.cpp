#include <iostream>
using namespace std;

int main()
{
    while(true){
        cout << "Printing a rectangle with diagonals (Advanced version of rectangle assignment)\n";
        cout << "Eg: Try the following inputs: 20 x 20, 31 x 31, 18 x 35, 19 x 37, 6 x 61, 11 x 71....\n\n";
        int height, width;
        cout << "Enter the height: "; cin >> height;
        cout << "Enter the width: "; cin >> width;
        if(width>=82 or height >= 82) cout << "Too big\n";
        else if(width<=0 or height <= 0) cout << "Impossible rectangle\n";
        else if(width<=1){  for(int i = 1; i <= height; i++) cout << "*\n"; }
        else if(height<=1){ for(int i = 1; i <= width; i++) cout << "*"; cout << "\n"; }
        else if((width-1)%(height-1)==0){
            int gradient = (width-1)/(height-1);
            int pos = 1+gradient, pos2 = width-gradient;
            for(int i = 1; i <= height; i++){
                if(i==1 or i==height){
                    for(int j = 1; j <= width; j++) cout << "* ";
                }
                else{
                    bool chk = 0, chk2 = 0;
                    for(int j = 1; j <= width; j++){
                        if((j==pos and !chk) or (j==pos2 and !chk2)){
                            cout << "*";
                            if(j==pos and !chk) pos+=gradient, chk = 1;
                            if(j==pos2 and !chk2) pos2-=gradient, chk2 = 1;
                        }
                        else if(j==1 or j==width) cout << "*";
                        else cout << " ";
                        cout << " ";
                    }
                }
                cout << "\n";
            }
        }
        else if((height-1)%(width-1)==0){
            int gradient = (height-1)/(width-1);
            for(int i = 1; i <= height; i++){
                for(int j = 1; j <= width; j++){
                    if(i==1 or i==height or j==1 or j==width) cout << "*";
                    else if((j-1)*gradient+1==i or (width-(j-1)-1)*gradient+1==i) cout << "*";
                    else cout << " ";
                    cout << " ";
                }
                cout << "\n";
            }
        }
        else{
            cout << "Diagonal cannot be printed out :) Here's a box instead...\n";
            for(int i = 1; i <= height; i++){
                cout << "* ";
                for(int j = 1; j <= width-2; j++){
                    cout << " *"[i==1 or i==height];
                    cout << " ";
                }
                cout << "*\n";
            }
        }
        cout << "\n";
    }
}
