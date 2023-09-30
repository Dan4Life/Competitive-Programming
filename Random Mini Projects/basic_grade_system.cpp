/**
Basic Student Grade Management System:
Math, English, Science
0. Exit the program
1. Add a student to the System
     - Ask for name
     - Ask for the grades

2. Modify a student's info
3. Show a student's report card
4. Show all students' report card
5. Delete a student in the system
6. Delete all students in the system

Inside report card:
    average grade, total grade / 300
    the score for each subject: A,B,C,D,E,F
    the overall score: A--F

No classes/structs involved.
Allows for saving to database
**/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int max_size = 100000;
const int max_name_size = 150;
string full_name[max_size];
float math_score[max_size];
float english_score[max_size];
float science_score[max_size];
int numStudents = 0;
char* database_file = "database.txt";

void add_to_file(int id){
    ofstream file_output(database_file, ios::app);
    file_output << full_name[id] << "\n";
    file_output << math_score[id] << "\n";
    file_output << english_score[id] << "\n";
    file_output << science_score[id] << "\n";
    file_output.close();
}

void load_file(){
    ofstream file_output(database_file, ios::app);
    file_output.close(); numStudents = 0;
    ifstream file_input(database_file);
    while(true){
        getline(file_input, full_name[numStudents]);
        if(file_input.eof()) break;
        file_input >> math_score[numStudents];
        file_input >> english_score[numStudents];
        file_input >> science_score[numStudents];
        if(!file_input.eof()) file_input.ignore();
        numStudents++;
    }
    file_input.close();
}

void save_file(int id=-1){ // can save a file without a specific id
    char* tempfile_name = "tempfile.txt";

    ofstream tempfile(tempfile_name);
    for(int i = 0; i < numStudents; i++){
        if(i==id) continue;
        tempfile << full_name[i] << "\n";
        tempfile << math_score[i] << "\n";
        tempfile << english_score[i] << "\n";
        tempfile << science_score[i] << "\n";
    }
    tempfile.close(); remove(tempfile_name);

    ofstream file_output(database_file);
    for(int i = 0; i < numStudents; i++){
        if(i==id) continue;
        file_output << full_name[i] << "\n";
        file_output << math_score[i] << "\n";
        file_output << english_score[i] << "\n";
        file_output << science_score[i] << "\n";
    }
    file_output.close();
}

template<class T> void get_input(T &var){
    while(true){
        cin >> var;
        if(cin.fail()){
            cin.clear(); // reset fail state flag
		  cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else{
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(cin.gcount() <= 1) break; // valid number
        }
        cout << "Invalid input. Please try again: ";
    }
}

void validate(float &var){
    while(true){
        get_input(var);
        if(var<0 or var>100)
            cout << "Score not in range[0,100]. Please try again: ";
        else break;
    }
}

int getId(){
    int id;
    cout << "Enter the ID of the student: ";
    get_input(id);
    if(id < 0 or id >= numStudents){
        cout << "This id is invalid\n";
        return -1;
    }
    cout << "\n";
    return id;
}

void print_menu(){
    cout << "\n";
    cout << "Welcome to our Grade Management System\n";
    cout << "0. Exit\n";
    cout << "1. Add a student to the system\n";
    cout << "2. Modify a student's info\n";
    cout << "3. Show a student's report card\n";
    cout << "4. Show all students' report card\n";
    cout << "5. Delete a student in the system\n";
    cout << "6. Delete all students in the system\n";
    cout << "\n";
}

int get_choice(){
    int choice;
    cout << "Enter your choice: ";
    get_input(choice);
    return choice;
}

void add_student(){
    cout << "\nThis is to add a student\n";
    cout << "Enter the student's full name: ";

    while(true){
        getline(cin, full_name[numStudents]);
        if(full_name[numStudents].size() > max_name_size)
            cout << "Name is longer than " << max_name_size << " . Please try again: ";
        else break;
    }

    cout << "Enter the student's math score: ";
    validate(math_score[numStudents]);
    cout << "Enter the student's english score: ";
    validate(english_score[numStudents]);
    cout << "Enter the student's science score: ";
    validate(science_score[numStudents]);

    cout << "The ID of this student is #" << numStudents << "\n";
    add_to_file(numStudents); numStudents++;
}

char verifyEdit(string edit){
    cout << "\nDo you want to edit the student's " << edit << "?\n";
    cout << "Respond with y/n/other (yes/no/exit): ";
    char option; get_input(option);
    if(option=='y') cout << "Enter the new " << edit << " of the student: ";
    return option;
}

bool modify_student(){
    if(numStudents==0){
        cout << "\nThere are no students in this system\n";
        return false;
    }

    cout << "\nThis is to modify a student\n";
    bool is_modified = false;
    int id = getId();
    if(id==-1) return is_modified;

    char option = verifyEdit("full name");
    if(option=='y'){
        while(true){
            getline(cin, full_name[id]);
            if(full_name[id].size() > max_name_size)
                cout << "Name is longer than " << max_name_size << " . Please try again: ";
            else break;
        }
        is_modified = true;
    }
    else if(option!='n') return is_modified;

    option=verifyEdit("math score");
    if(option=='y'){
        validate(math_score[id]); is_modified = true;
    }
    else if(option!='n') return is_modified;

    option=verifyEdit("english score");
    if(option=='y'){
        validate(english_score[id]); is_modified = true;
    }
    else if(option!='n') return is_modified;

    option=verifyEdit("science score");
    if(option=='y'){
        validate(science_score[id]); is_modified = true;
    }
    else if(option!='n') return is_modified;

    return is_modified;
}

float getTotScore(int id){
    return math_score[id]+english_score[id]+science_score[id];
}

string grade_letter(float score){
    if(score>=90) return "A*";
    if(score>=80) return "A";
    if(score>=70) return "B";
    if(score>=60) return "C";
    if(score>=50) return "D";
    if(score>=40) return "E";
    return "F";
}

void show_report_card(){
    if(numStudents==0){
        cout << "\nThere are no students in this system\n";
        return;
    }

    cout << "\nThis is to show a student's report card\n\n";
    int id = getId(); if(id==-1) return;

    cout << "Student's Full Name: " << full_name[id] << "\n";
    cout << "Student's Math Score: " << math_score[id] << " (" << grade_letter(math_score[id]) << ")\n";
    cout << "Student's English Score: " << english_score[id] << " (" << grade_letter(english_score[id]) << ")\n";
    cout << "Student's Science Score: " << science_score[id] << " (" << grade_letter(science_score[id]) << ")\n";
    float total_score = getTotScore(id);
    cout << "Student's Total Score: " << total_score << "\n";
    cout << "Student's Percentage: " << total_score/3 << "%" << " (" << grade_letter(total_score/3) << ")\n";
}

void print_line(int num){
    for(int i = 0; i < num; i++)
        cout << "-";
    cout << "\n";
}

void show_all_report_cards(){
    if(numStudents==0){
        cout << "\nThere are no students in this system\n";
        return;
    }

    cout << "\nThis is to show all students' report cards\n\n";

    int mx = 12;
    for(int i = 0; i < numStudents; i++)
        mx = max(mx, (int)(full_name[i].size()));

    int tot = 57+(mx+1)/8*8;
    print_line(tot);
    cout << "|ID\t|Student Name";
    for(int i = 0; i < (mx+1)/8; i++) cout << "\t";
    cout << "|Math\t|Eng.\t|Sci.\t|Grade\t\t|\n";

    for(int i = 0; i < numStudents; i++){
        print_line(tot);
        cout << "|" << i << "\t|";
        string name = full_name[i];
        while(name.size()<mx)name+=' ';
        cout << name << "\t|";
        cout << math_score[i] << "\t|";
        cout << english_score[i] << "\t|";
        cout << science_score[i] << "\t|";
        float average = getTotScore(i)/3;
        cout << average;
        cout << "(" << grade_letter(average) << ")";
        if(average<10.0) cout << "\t";
        cout << "\t|\n";
    }
    print_line(tot);
}

void delete_student(){
    if(numStudents==0){
        cout << "\nThere are no students in this system\n";
        return;
    }

    cout << "\nThis is to delete a student's data\n\n";
    int id = getId(); if(id==-1) return;
    cout << "Student name is " << full_name[id] << "\n\n";
    cout << "Are you really sure you want to delete this student id?\n";
    cout << "Respond with y/n (yes/no): ";
    char option; get_input(option);
    if(option != 'y') return;
    save_file(id); load_file();
    cout << "Successfully deleted the ID\n";
}

void delete_all_students(){
    if(numStudents==0){
        cout << "\nThere are no students in this system\n";
        return;
    }

    cout << "\nThis is to delete all students' data\n\n";
    cout << "Are you really sure you want to delete all students' data?\n";
    cout << "Respond with y/n (yes/no): ";
    char option; get_input(option);
    if(option != 'y') return;
    string confirm = "delete|all", input;
    cout << "To confirm, please type the following: " << confirm << "\n";
    getline(cin, input);
    if(input!=confirm) return;
    remove(database_file); load_file();
    cout << "Successfully cleared the database\n";
}

int main(){
    cout << fixed << setprecision(1);
    load_file();

    while(true){
        print_menu();
        int option = get_choice();
        if(option==0){
            cout << "Thanks for visiting. See you next time!\n";
            return 0;
        }
        else if(option==1) add_student();
        else if(option==2){
            if(modify_student()){
                save_file();
                cout << "Student info has successfully been modified\n";
            }
        }
        else if(option==3) show_report_card();
        else if(option==4) show_all_report_cards();
        else if(option==5) delete_student();
        else if(option==6) delete_all_students();
        else cout << "Your choice is not valid. Try again!\n";
    }
}
