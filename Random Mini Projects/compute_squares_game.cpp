// This game I made helped me mentally compute X^2 for all X<=1000 quickly
// It's useful for improving your focus when thinking of problems in general
// as you'd definitely need to focus to do this quickly and accurately
// First memorize 1^2 to 32^2  (You probably know 1-16 by heart)
// To compute X^2 for X in [33,100] just use X^2 = (X+Y)(X-Y) + Y^2
// I use 50 for X < 70, eg: 62^2 = (62-12)(62+12) + 144 = 50*74+144 = 3700+144 = 3844
// and 100 for X >= 70, eg: 84^2 = (84+16)(84-16) + 256 = 100*68+256 = 7056
// To extend to 3 digit numbers, we can do the same thing but on a harder difficulty : )
// Eg  748^2 = 700*796 + 48^2 = 557200 + 2304 = 559504

#include <bits/stdc++.h>
using namespace std;

template<class T> void get_input(T &var){ // to prevent unwanted input during runtime
    T var2;
    while(1){
        cin >> var2;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else{
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(cin.gcount() <= 1) break;
        }
        cout << "\nInput is not in the right format, please try again: ";
    }
    var = var2;
}

template<class T, class U> void validate(T &var, U low, U high){
    // to make sure integers/floats/chars are inputted in a certain value range
    // and strings are inputted in a certain length range
    T var2;
    while(true){
        if constexpr(is_same_v<T, int> or is_same_v<T, float> or is_same_v<T, char>) { // if type int/float/char
            get_input(var2);
            if(var2<low or var2>high)
                cout << "\nInput is not in range [" << (T)low << "," << (T)high << "]. Please try again: "; // notice the type casting...
            else break;
        }
        else if constexpr (is_same_v<T, string>) { // if type string
            getline(cin, var2);
            if((int)var2.size()<low or (int)var2.size()>high)
                cout << "\nInput length is not in range [" << low << "," << high << "]. Please try again: ";
            else break;
        }
    }
    var = var2;
}

int randint(int a, int b){
	return rand()%(b-a+1)+a;
}

int main(){
	srand(time(0)); int lb, ub, repeat, option, lim=-1;
	
	cout << "Welcome to \"Compute The Perfect Squares\" game\n\n";
	cout << "There are some preset game settings, pick any option or choose custom settings\n";
	cout << "1) 1 to 32, once\n";
	cout << "2) 33 to 100, once\n";
	cout << "3) 101 to 1000, (100 random questions) \n";
	cout << "4) 1 to 100, once\n";
	cout << "5) 1 to 1000, once\n";
	cout << "0) Custom settings\n";
	cout << "\n";
	cout << "Enter option: "; validate(option, 0, 5);
	if(option==1) lb=1,ub=32,repeat=1;
	else if(option==2) lb=33,ub=100,repeat=1;
	else if(option==3) lb=101,ub=1000,repeat=1,lim=100;
	else if(option==4) lb=1,ub=100,repeat=1;
	else if(option==5) lb=1,ub=1000,repeat=1;
	else{
		cout << "Enter the minimum number you want to guess: "; validate(lb, 0, 9000);
		cout << "Enter the maximum number you want to guess: "; validate(ub, lb, lb+1000);
		cout << "Enter how many times you want each number in the range ["
		<< lb << ","<<ub<<"]: "; validate(repeat, 1, 5);
		
		if(repeat*(ub-lb)>1000) {
			cout << "\nInvalid\n";
			cout << "The number of questions must be less than 1000, even with repeats\n";
			return 0;
		}
	}
	
	cout << "\nTo end the game at any point, input -1\n";
	cout << "Let's start!\n";
	
	vector<int> v;
	for(int i = lb; i <= ub; i++) 
		for(int j = 0; j < repeat; j++) 
			v.push_back(i);
	random_shuffle(begin(v),end(v));
	if(lim!=-1) v.resize(lim);
	int score=0, tot=0;
	double avg_time = 0, avg_good=0, max_time=0;
	
	for(auto x : v){
		cout << "\n" << x << " x " << x << " = ";
		auto start = chrono::high_resolution_clock::now();
		int ans; validate(ans, -1, ub*ub); if(ans==-1) break;
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds> (stop - start); 
		auto tim = duration.count()/1000.0;
		avg_time+=tim; tot++; max_time=max(max_time, tim);
		if(ans==x*x){
			cout << "Correct! ";
			avg_good+=tim; score++;
		}
		else cout << "Wrong! Answer is " << x*x << ". ";
		cout << "Took " << fixed << setprecision(1) << tim << "s\n";
	}
	
	if(tot){
		cout << "\n\nYou got " << score << "/" << tot << " right, which is ";
		cout << fixed << setprecision(2) << (double)(100.0*score/tot*1.0) << "%\n";  
	}
	if(score) cout << "You took an average of " << avg_good/score*1.0 << " seconds to answer correctly\n";
	if(tot and tot!=score) cout << "Average response time: " << avg_time/tot*1.0 << " seconds\n";
	if(tot) cout << "Max response time for a single question: " << max_time << " seconds\n";
	cout << "\n";
}
