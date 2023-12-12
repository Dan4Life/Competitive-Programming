#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int max_size = 1000;
const int min_options = 2;
const int max_options = 5;
const int max_statement_length = 250;
const int max_option_length = 100;
string database_file = "database.txt";

struct Question{
    string statement;
    vector<string> options;
};
vector<Question> questions;

void add_to_file(Question &question){ // Add a question to file
    ofstream file_out(database_file, ios::app); // create the file if it hasn't already, else just append to the file's contents
    file_out << question.statement << "\n";
    file_out << question.options.size() << "\n";
    for(auto option : question.options)
        file_out << option << "\n";
    file_out.close();
}

void load_file(){ // from file to vector
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

void update_file(){ // rewrite entire file with contents of the vector
    ofstream file_out(database_file);
    for(auto question : questions){
        file_out << question.statement << "\n";
        file_out << question.options.size() << "\n";
        for(auto option : question.options)
            file_out << option << "\n";
    }
    file_out.close();
}

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
        cout << "Invalid input, try again: ";
    }
    var = var2;
}

void validate(int &var, int low, int high){ // to make sure integers are inputted in a certain value range
    int var2;
    while(true){
        get_input(var2);
        if(var2<low or var2>high)
            cout << "Input not in range[" << low << "," << high << "]. Please try again: ";
        else break;
    }
    var = var2;
}

void validate_string(string &var, int low, int high){ // to make sure strings are inputted in a certain length range
    string var2;
    while(true){
        getline(cin, var2);
        if((int)var2.size()<low or (int)var2.size()>high)
            cout << "Length is not in range[" << low << "," << high << "]. Please try again: ";
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

void show_question(int index){
    if(index<0 or index>=questions.size()) return;
    cout << "\nThe question statement is: \"" << questions[index].statement << "\"\n";
    cout << "Current options:\n";
    int cnt2 = 0;
    for(auto option : questions[index].options){
        cout << "(" << (char)('A'+cnt2) << "). " << option << "\n";
        cnt2++;
    }
}

void add_question(){
    if((int)questions.size()>=max_size){
        cout << "\nThe number of questions in the database has reached the maximum size (" << max_size << ")\n\n";
        return;
    }

    cout << "\nPlease input a question statement:\n";
    string statement; validate_string(statement,1,max_statement_length);

    cout << "\nHow many options do you want to add (" << min_options << " to " << max_options << "): ";
    int num_options; validate(num_options, min_options, max_options);

    vector<string> options; options.clear();
    for(int i = 0; i < num_options; i++){
        if(!i) cout << "Enter the correct option: ";
        else cout << "Enter option (" << (char)('A'+i) << "): ";
        string option; validate_string(option,1,max_option_length);
        options.emplace_back(option);
    }

    questions.push_back(Question{statement, options});
    add_to_file(questions.back());
    cout << "\nSuccessfully added new question!\n";
}

void delete_question(){
    if(questions.empty()){
        cout << "Database is empty!\n";
        return;
    }

    cout << "There are currently " << questions.size() << " questions in the database\n";
    cout << "Please input the index of the question you want to delete: ";
    int index; validate(index,1,questions.size()); index--;

    show_question(index);

    cout << "\nAre you really sure you want to delete this question? Y/N: ";
    char choice; get_input(choice);

    if(choice=='Y'){
        cout << "\nDeleting...\n";
        questions.erase(questions.begin()+index);
        update_file();
        cout << "Successfully deleted this question!\n";
        return;
    }
}

void add_options_to_question(){
    if(questions.empty()){
        cout << "Database is empty!\n";
        return;
    }

    cout << "There are currently " << questions.size() << " questions in the database\n";
    cout << "Please input the index of the question you want to add options to: ";
    int index; validate(index,1,questions.size()); index--;

    int new_options = max_options-questions[index].options.size();
    if(new_options<=0){
        cout << "\nMaximum number of options added!\n";
        return;
    }

    show_question(index);

    cout << "\nYou are allowed to add at most " << new_options << " new option(s) to this question\n";
    cout << "How many options do you want to add: ";
    int num_options; validate(num_options, 0, new_options);
    if(num_options==0) return;

    vector<string> options; options.clear();
    for(int i = 0; i < num_options; i++){
        cout << "Enter option (" << (char)('A'+i+questions[index].options.size()) << "): ";
        string option; validate_string(option,1,max_option_length);
        options.emplace_back(option);
    }
    for(auto option : options)
        questions[index].options.emplace_back(option);
    update_file();
    cout << "\nSuccessfully added new options!\n";
}

void delete_option_from_question(){
    if(questions.empty()){
        cout << "\nDatabase is empty!\n";
        return;
    }

    cout << "There are currently " << questions.size() << " questions in the database\n";
    cout << "Please input the index of the question you want to delete an option from: ";
    int index; validate(index,1,questions.size()); index--;

    show_question(index);

    if(questions[index].options.size()==min_options){
        cout << "\nQuestion has minimum number of options required!\n";
        return;
    }

    cout << "\nPlease input the index of the option you want to delete.\n";
    cout << "Note that the first option which is assumed to be correct cannot be deleted: ";
    int index2; validate(index2,2,questions[index].options.size()); index2--;

    cout << "Are you sure you want to delete this option? Y/N: ";
    char choice; get_input(choice);

    if(choice=='Y'){
        cout << "\nDeleting...\n";
        questions[index].options.erase(questions[index].options.begin()+index2);
        update_file();
        cout << "Successfully deleted this question!\n";
        return;
    }
}

void edit_question(){
    if(questions.empty()){
        cout << "\nDatabase is empty!\n";
        return;
    }

    cout << "There are currently " << questions.size() << " questions in the database\n";
    cout << "Please input the index of the question you want to edit: ";
    int index; validate(index,1,questions.size()); index--;

    show_question(index);

    cout << "\nAre you really sure you want to edit this question? Y/N: ";
    char choice; get_input(choice);
    if(choice!='Y') return;

    cout << "\nPlease input the new question statement:\n";
    string statement; validate_string(statement,1,max_statement_length);

    cout << "\nHow many options do you want to add (" << min_options << " to " << max_options << "): ";
    int num_options; validate(num_options, min_options, max_options);

    vector<string> options; options.clear();
    for(int i = 0; i < num_options; i++){
        if(!i) cout << "Enter the correct option: ";
        else cout << "Enter option (" << (char)('A'+i) << "): ";
        string option; validate_string(option,1,max_option_length);
        options.emplace_back(option);
    }

    questions[index] = Question{statement, options};
    update_file(); cout << "\nSuccessfully updated this question!\n";
}

void show_all_questions(){
    cout << "ALL QUESTIONS IN THE DATABASE\n\n";
    cout << "---------------------------------------------------------------------------\n\n";
    int cnt = 1;
    for(auto question : questions){
        cout << cnt << ". " << question.statement << "\n";
        int cnt2 = 0;
        for(auto option : question.options){
            cout << "(" << (char)('A'+cnt2) << "). " << option << "\n";
            cnt2++;
        }
        cout<<"\n\n"; cnt++;
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
        cout << "\n\n";
    }
}
