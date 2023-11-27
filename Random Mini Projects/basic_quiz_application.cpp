#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int max_size = 1000;
const int max_options = 5;
string database_file = "database.txt";

struct Question{
    string statement;
    vector<string> options;
};
vector<Question> questions;

void add_to_file(Question &question){ // Add a question to file
    ofstream file_out(database_file, ios::app);
    file_out << question.statement << "\n";
    file_out << question.options.size() << "\n";
    for(auto option : question.options)
        file_out << option << "\n";
    file_out.close();
}

void load_file(){ // from file to vectors
    ofstream file_out(database_file, ios::app);
    file_out.close(); questions.clear();
    ifstream file_in(database_file);
    while(true){
        Question question;
        getline(file_in, question.statement);
        if(file_in.eof()) break; // no input again
        int num_options; file_in >> num_options;
        file_in.ignore();
        question.options.clear();
        while(num_options--){
            string option;
            getline(file_in, option);
            question.options.push_back(option);
        }
        questions.push_back(question);
    }
    file_in.close();
}

void update_file(){
    ofstream file_out(database_file);
    for(auto question : questions){
        file_out << question.statement << "\n";
        file_out << question.options.size() << "\n";
        for(auto option : question.options)
            file_out << option << "\n";
    }
    file_out.close();
}

template<class T> void get_input(T &var){
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
        cout << "Invalid input, try again: ";
    }
    var = var2;
}

void validate(int &var, int low, int high){
    int var2;
    while(true){
        get_input(var2);
        if(var2<low or var2>high)
            cout << "Input not in range[" << low << "," << high << "]. Please try again: ";
        else break;
    }
    var = var2;
}

void print_menu(){
    cout << "Welcome to this Quiz Application!\n";
    cout << "(0). Exit\n";
    cout << "(1). Add a question\n";
    cout << "(2). Delete a question\n";
    cout << "(3). Add options to a question\n";
    cout << "(4). Delete an option from a question\n";
    cout << "(5). Edit a question\n";
    cout << "(6). Show all questions\n";
    cout << "(7). Take the test\n";
}

void add_question(){
    cout << "\nPlease input a question statement:\n";
    string statement; getline(cin, statement);
    cout << "How many options do you want to add(2 to " << max_options << "): ";
    int num_options; validate(num_options,2,max_options);

    vector<string> options; options.clear();
    for(int i = 0; i < num_options; i++){
        if(!i) cout << "Enter the correct option: ";
        else cout << "Enter option (" << (char)('A'+i) << "): ";
        string option; getline(cin, option);
        options.emplace_back(option);
    }
    questions.push_back(Question{statement, options});
    add_to_file(questions.back());
}

void delete_question(){

}

void add_options_to_question(){

}

void delete_option_from_question(){

}

void edit_question(){

}

void show_all_questions(){
    cout << "ALL QUESTIONS IN THE DATABASE\n\n";
    cout << "---------------------------------------------------------------------------\n\n";
    int cnt = 1;
    for(auto question : questions){
        cout << cnt << ". " << question.statement << "\n";
        int cnt2 = 0;
        for(auto option : question.options){
            cout << (char)('a'+cnt2) << "). " << option << "\n"; cnt2++;
        }
        cout<<"\n"; cnt++;
    }
    cout << "---------------------------------------------------------------------------\n";
}

void start_test(){

}

int main(){
    load_file();
    while(true){
        print_menu();
        cout << "\nEnter your option: ";
        int choice; validate(choice,0,7); cout << "\n";

        if(choice==0){
            cout << "Exiting the program...\n";
            return 0;
        }
        else if(choice==1) add_question();
        else if(choice==2) delete_question();
        else if(choice==3) add_options_to_question();
        else if(choice==4) delete_option_from_question();
        else if(choice==5) edit_question();
        else if(choice==6) show_all_questions();
        else if(choice==7) start_test();
        else cout << "Your choice is not valid. Try again!";
        cout << "\n";
    }
}
