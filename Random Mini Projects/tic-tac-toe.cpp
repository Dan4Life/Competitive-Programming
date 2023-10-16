#include <iostream>
using namespace std;

string board = "123456789";
bool isPlayer1turn = true;
int numRounds = 9;

template<class T> void get_input(T &var){
    T var2;
    while (true){
        cout << "Enter your choice: "; cin >> var2;
        if (cin.fail()) cin.clear(), cin.ignore(numeric_limits<streamsize>::max(), '\n');
        else{
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(cin.gcount()<=1) break; // valid number
        }
        cout<<"Invalid input...\n";
    }
    var = var2;
}

void print_board(){
    for(int j = 0; j < 13; j++)
        cout << "-";
    cout << "\n";

    for(int i = 0; i < 9; i++){
        if(i%3==0) cout << "| ";
        cout << board[i] << " | ";
        if(i%3==2){
            cout << "\n";
            for(int j = 0; j < 13; j++)
                cout << "-";
            cout << "\n";
        }
    }
}

bool compare(int a, int b, int c){
    return (board[a]==board[b] and board[b]==board[c]);
}

bool wonGame(){
    if(compare(0,1,2)||compare(3,4,5)||compare(6,7,8)) return true; // horizontal
    if(compare(0,3,6)||compare(1,4,7)||compare(2,5,8)) return true; // vertical
    if(compare(0,4,8)||compare(2,4,6)) return true; // diagonal
    return false;
}

int main()
{
    cout << "Welcome to our TicTacToe Game!\n\n";
    while(numRounds--){
        print_board();
        string player = isPlayer1turn ? "Player 1" : "Player 2";
        cout << player << ", ";
        int choice;
        do{
            get_input(choice);
            if(choice<1 or choice>9)
                cout << "The number you entered is not in the range [1,9]\n";
            else if(!isdigit(board[choice-1]))
                cout << "The current square has been used already\n";
            else break;
        }
        while(true);
        board[choice-1] = isPlayer1turn?'X':'O';

        if(wonGame()){
            cout << player << " has won the game\n";
            print_board(); return 0;
        }
        isPlayer1turn^=1; // toggle boolean
    }
    cout << "The game ends in a draw\n"; print_board();
}
