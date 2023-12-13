#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono> // higher precision clock
#include <iomanip>
using namespace std;

const int min_options = 2;
const int max_options = 5;
const int max_size = 100000;
const int max_test_duration = 600;
const int max_option_length = 100;
const int max_statement_length = 250;
const int max_test_questions_size = 100;
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
    ofstream file_out(database_file, ios::app); // make sure the file is created if there isn't one.
    file_out.close(); questions.clear();        // make sure the variables are cleared.
    ifstream file_in(database_file);
    while(true){
        Question question;
        getline(file_in, question.statement);
        if(file_in.eof()) break;                    // no input again
        int num_options; file_in >> num_options;
        file_in.ignore();                           // to prevent issues with the next getline
        question.options.clear();
        while(num_options--){
            string option; getline(file_in, option);
            question.options.push_back(option);
        }
        questions.push_back(question);
    }
    file_in.close();
}

void update_file(){ // rewrite entire file with contents of the vector
    ofstream file_out(database_file); // create empty file / clear existing file
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
        cout << "\nInput is not in the right format, please try again: ";
    }
    var = var2;
}

template<class T, class U> void validate(T &var, U low, U high){
    // to make sure integers/floats/chars are inputted in a certain value range
    // and strings are inputted in a certain length range
    // I did this with two functions in a previous version of this code...
    T var2;
    while(true){
        if constexpr(is_same_v<T, int> or is_same_v<T, float> or is_same_v<T, char>) { // if type int/float/char
            get_input(var2);
            if(var2<low or var2>high)
                cout << "\nInput is not in range[" << (T)low << "," << (T)high << "]. Please try again: "; // notice the type casting...
            else break;
        }
        else if constexpr (is_same_v<T, string>) { // if type string
            getline(cin, var2);
            if((int)var2.size()<low or (int)var2.size()>high)
                cout << "\nInput length is not in range[" << low << "," << high << "]. Please try again: ";
            else break;
        }
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
    if(index<0 or index>=(int)questions.size()) return;
    cout << "\nThe question statement is: \"" << questions[index].statement << "\"\n";
    cout << "Current options (note that option A is the correct answer):\n";
    int cnt2 = 0;
    for(auto option : questions[index].options){
        cout << "(" << (char)('A'+cnt2) << "). " << option << "\n";
        cnt2++;
    }
}

void print_char(char c, int length){
    for(int i = 0; i < length; i++) cout << c;
    cout << "\n";
}

void add_question(){
    if((int)questions.size()>=max_size){
        cout << "The number of questions in the database has reached the maximum size (" << max_size << ")\n\n";
        return;
    }
    cout << "ADD A NEW QUESTION\n\n";

    cout << "Please input a question statement:\n";
    string statement; validate(statement,1,max_statement_length);

    cout << "\nHow many options do you want to add (" << min_options << " to " << max_options << "): ";
    int num_options; validate(num_options, min_options, max_options);

    vector<string> options; options.clear();
    for(int i = 0; i < num_options; i++){
        if(!i) cout << "Enter the correct option: ";
        else cout << "Enter option (" << (char)('A'+i) << "): ";
        string option; validate(option,1,max_option_length);
        options.emplace_back(option);
    }

    questions.push_back(Question{statement, options});
    add_to_file(questions.back());
    cout << "\n\nSuccessfully added new question!\n\n";
}

void delete_question(){
    if(questions.empty()){ cout << "Database is empty!\n"; return; }
    cout << "DELETE A QUESTION\n\n";

    cout << "There are currently " << questions.size() << " questions in the database\n";
    cout << "Please input the index of the question you want to delete: ";
    int index; validate(index,1,(int)questions.size()); index--;

    show_question(index);

    cout << "\nAre you really sure you want to delete this question? Y(y)/(any for no): ";
    char choice; get_input(choice);
    if(choice!='Y' and choice!='y') return;

    questions.erase(questions.begin()+index);
    update_file();
    cout << "\n\nSuccessfully deleted this question!\n\n";
}

void add_options_to_question(){
    if(questions.empty()){ cout << "Database is empty!\n"; return; }
    cout << "ADD OPTIONS TO A QUESTION\n\n";

    cout << "There are currently " << questions.size() << " questions in the database\n";
    cout << "Please input the index of the question you want to add options to: ";
    int index; validate(index,1,(int)questions.size()); index--;

    int new_options = max_options-questions[index].options.size();
    if(new_options<=0){
        cout << "\nThis question already has the maximum number of options!\n";
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
        string option; validate(option,1,max_option_length);
        options.emplace_back(option);
    }

    for(auto option : options)
        questions[index].options.emplace_back(option);
    update_file();
    cout << "\n\nSuccessfully added new options to this question!\n\n";
}

void delete_option_from_question(){
    if(questions.empty()){ cout << "Database is empty!\n"; return; }
    cout << "DELETE AN OPTION FROM A QUESTION\n\n";

    cout << "There are currently " << questions.size() << " questions in the database\n";
    cout << "Please input the index of the question you want to delete an option from: ";
    int index; validate(index,1,(int)questions.size()); index--;

    show_question(index);

    if(questions[index].options.size()<=min_options){
        cout << "\nQuestion has minimum number of options required!\n";
        return;
    }

    cout << "\nPlease input the index of the option you want to delete.\n";
    cout << "Note that if you delete the first option, the next option will be assumed to be correct: ";
    int index2; validate(index2,1,(int)questions[index].options.size()); index2--;

    cout << "Are you sure you want to delete this option? Y(y)/(any for no): ";
    char choice; get_input(choice);
    if(choice!='Y' and choice!='y') return;

    questions[index].options.erase(questions[index].options.begin()+index2);
    update_file();
    cout << "\n\nSuccessfully deleted this question!\n\n";
}

void edit_question(){
    if(questions.empty()){ cout << "Database is empty!\n"; return; }
    cout << "EDIT A QUESTION\n\n";

    cout << "There are currently " << questions.size() << " questions in the database\n";
    cout << "Please input the index of the question you want to edit: ";
    int index; validate(index,1,(int)questions.size()); index--;

    show_question(index);

    cout << "\nAre you really sure you want to edit this question? Y(y)/(any for no): ";
    char choice; get_input(choice);
    if(choice!='Y' and choice!='y') return;

    cout << "\nPlease input the new question statement:\n";
    string statement; validate(statement,1,max_statement_length);

    cout << "\nHow many options do you want to add (" << min_options << " to " << max_options << "): ";
    int num_options; validate(num_options, min_options, max_options);

    vector<string> options; options.clear();
    for(int i = 0; i < num_options; i++){
        if(!i) cout << "Enter the correct option: ";
        else cout << "Enter option (" << (char)('A'+i) << "): ";
        string option; validate(option,1,max_option_length);
        options.emplace_back(option);
    }

    questions[index] = Question{statement, options};
    update_file();
    cout << "\n\nSuccessfully editted this question!\n\n";
}

void show_all_questions(){
    if(questions.empty()){ cout << "Database is empty!\n"; return; }
    cout << "SHOW ALL QUESTIONS IN THE DATABASE\n\n\n";

    int cnt = 1;
    for(auto question : questions){
        cout << cnt++ << ". " << question.statement << "\n";
        int cnt2 = 0;
        for(auto option : question.options){
            cout << "(" << (char)('A'+cnt2) << "). " << option << "\n";
            cnt2++;
        }
        cout<<"\n\n";
    }
}

void start_test(){
    if(questions.empty()){ cout << "Database is empty!\n"; return; }
    cout << "TAKE THE TEST\n\n";

    cout << "There are currently " << questions.size() << " questions in the database\n";
    cout << "Before we begin, I have a few questions to ask:\n\n";

    cout << "1. Do you want the questions in random order? Y(y)/(any for no): ";
    char choice; get_input(choice);
    bool random_order = (choice=='Y' or choice=='y');

    cout << "2. How long do you want to take the test(in minutes from 1 to " << max_test_duration << "): ";
    float test_duration; validate(test_duration,1,max_test_duration);

    cout << "3. How many questions do you want to take for the test (at most ";
    cout << min(max_test_questions_size,(int)questions.size()) << " questions): ";
    int num_questions; validate(num_questions, 0, min(max_test_questions_size,(int)questions.size()));
    if(num_questions==0) return;

    cout << "4. Do you want to know immediately if you got a question correctly? Y(y)/(any for no): ";
    get_input(choice);
    bool immediate_outcome = (choice=='Y' or choice=='y');

    cout << "\n\nTest Starts Now!\n\n\n";

    vector<int> indices(num_questions,0);
    iota(indices.begin(),indices.end(),0);
    if(random_order) random_shuffle(indices.begin(),indices.end()); // randomize the question order if necessary

    int cnt = 1, total_correct = 0;
    auto startTime = chrono::steady_clock::now();
    auto endTime = startTime + (chrono::seconds)((int)(60*test_duration));

    for(auto i : indices){
        if (chrono::steady_clock::now() > endTime) {
            cout << "Your time is up!\n"; break;
        }

        cout << cnt++ << ". " << questions[i].statement << "\n";

        vector<int> option_indices((int)questions[i].options.size(),0);
        iota(option_indices.begin(),option_indices.end(),0);
        random_shuffle(option_indices.begin(),option_indices.end()); // randomize the options order

        int cnt2 = 0, correct_answer = -1;
        for(auto j : option_indices){
            if(j==0) correct_answer = cnt2;
            cout << "(" << (char)('A'+cnt2) << "). " << questions[i].options[j] << "\n";
            cnt2++;
        }

        cout << "\nPick your choice: ";
        char choice; validate(choice,(int)'A','A'+(int)questions[i].options.size()-1);

        bool got_question_right = (choice-'A'==correct_answer);
        total_correct += got_question_right;

        if(immediate_outcome){
            cout << "\n";
            if(got_question_right) cout << "You got the right answer!";
            else cout << "You failed the question, the right answer is " << (char)('A'+correct_answer);
            cout << "\n\n";
        }
        cout << "\n";
    }
    endTime = min(endTime, chrono::steady_clock::now());
    cout << "\n\nThe test has ended!\n\n";
    cout << "You used " << chrono::duration_cast<chrono::seconds>(endTime - startTime).count() << " seconds for the test\n";
    cout << "You got " << total_correct << "/" << num_questions << " questions right!\n";
    cout << "Your percentage for the test is " << fixed << setprecision(2) << (1.0*total_correct/num_questions * 100) << "%\n";
}

int main(){
    srand(time(NULL));  // to make sure we have a new random seed every run
    load_file();        // copy all the database info to the variables
    while(true){
        print_menu();
        cout << "\nEnter your option: ";
        int choice; validate(choice,0,7); cout << "\n\n";
        print_char('-',100); cout << "\n";
        if(choice==0){
            cout << "Exiting the program...\n";
            cout << "Any ideas on improving this?\n";
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
        print_char('-',100); cout << "\n\n";
    }
}
