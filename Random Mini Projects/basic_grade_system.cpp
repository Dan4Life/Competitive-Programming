#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

const int max_size = 100000;
const int max_name_size = 150;
const double EPS = 1e-2;

struct Student{
    string full_name;
    float math_score;
    float english_score;
    float science_score;
} students[max_size];

int numStudents = 0;
string database_file = "database.txt";

void add_to_file(int id){ // Add a student to file
    ofstream file_out(database_file, ios::app);
    file_out << students[id].full_name << "\n";
    file_out << students[id].math_score << "\n";
    file_out << students[id].english_score << "\n";
    file_out << students[id].science_score << "\n";
    file_out.close();
}

void load_file(){ // from file to arrays
    ofstream file_out(database_file, ios::app);
    file_out.close(); numStudents = 0;
    ifstream file_in(database_file);
    while(true){
        getline(file_in, students[numStudents].full_name);
        if(file_in.eof()) break; // no input again
        file_in >> students[numStudents].math_score;
        file_in >> students[numStudents].english_score;
        file_in >> students[numStudents].science_score;

        // that extra '\n' is annoying for the next getline
        if(!file_in.eof()) file_in.ignore();
        numStudents++;
    }
    file_in.close();
}

void update_file(int id=-1){ // possible to delete a certain ID
    ofstream file_out(database_file);
    for(int i = 0; i < numStudents; i++){
        if(i==id) continue;
        file_out << students[i].full_name << "\n";
        file_out << students[i].math_score << "\n";
        file_out << students[i].english_score << "\n";
        file_out << students[i].science_score << "\n";
    }
    file_out.close(); load_file();
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
    cout << "Welcome to our Grade System\n";
    cout << "(0) Exit\n";
    cout << "(1) Add a student to the System\n";
    cout << "(2) Modify a student's info\n";
    cout << "(3) Show a student's report card\n";
    cout << "(4) Show all students' report cards\n";
    cout << "(5) Delete a student's info in the system\n";
    cout << "(6) Delete all students' info in the system\n";
    cout << "(7) Find the highest scoring student(s)\n";
    cout << "(8) Find the lowest scoring student(s)\n";
    cout << "(9) Calculate average grade of all students for each subject\n";
    cout << "(10) Show all students' report cards in decreasing order of grades\n";
    cout << "\n";
}

void validate(float &var){
    float var2;
    while(true){
        get_input(var2);
        if(var2<0 or var2>100)
            cout << "Score not in range[0,100]. Please try again: ";
        else break;
    }
    var = var2;
}

void add_student(){
    cout << "\nThis is to add a student\n";
    cout << "Enter the student's full name: ";

    string s = students[numStudents].full_name;
    while(true){
        getline(cin, s);
        if(s.size() > max_name_size)
            cout << "Name is longer than " << max_name_size << " . Please try again: ";
        else break;
    }
    students[numStudents].full_name = s;

    cout << "Enter the student's math score: ";
    validate(students[numStudents].math_score);
    cout << "Enter the student's english score: ";
    validate(students[numStudents].english_score);
    cout << "Enter the student's science score: ";
    validate(students[numStudents].science_score);

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
        string s = students[id].full_name;
        while(true){
            getline(cin, s);
            if(s.size() > max_name_size)
                cout << "Name is longer than " << max_name_size << " . Please try again: ";
            else break;
        }
        students[id].full_name = s;
        is_modified = true;
    }
    else if(option!='n') return is_modified;

    option=verifyEdit("math score");
    if(option=='y'){
        validate(students[id].math_score); is_modified = true;
    }
    else if(option!='n') return is_modified;

    option=verifyEdit("english score");
    if(option=='y'){
        validate(students[id].english_score); is_modified = true;
    }
    else if(option!='n') return is_modified;

    option=verifyEdit("science score");
    if(option=='y'){
        validate(students[id].science_score); is_modified = true;
    }
    else if(option!='n') return is_modified;

    return is_modified;
}

float getTotScore(int id, Student students[]){
    return students[id].math_score+students[id].english_score+students[id].science_score;
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
    int id = getId();
    if(id==-1) return;

    cout << "Student's Full Name: " << students[id].full_name << "\n";
    cout << "Student's Math Score: " << students[id].math_score << " (" << grade_letter(students[id].math_score) << ")\n";
    cout << "Student's English Score: " << students[id].english_score << " (" << grade_letter(students[id].english_score) << ")\n";
    cout << "Student's Science Score: " << students[id].science_score << " (" << grade_letter(students[id].science_score) << ")\n";
    float total_score = getTotScore(id, students);
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
        mx = max(mx, (int)(students[i].full_name.size()));

    int tot = 57+(mx+1)/8*8;
    print_line(tot);
    cout << "|ID\t|Student Name";
    for(int i = 0; i < (mx+1)/8; i++) cout << "\t";
    cout << "|Math\t|Eng.\t|Sci.\t|Grade\t\t|\n";

    for(int i = 0; i < numStudents; i++){
        print_line(tot);
        cout << "|" << i << "\t|";
        string name = students[i].full_name;
        while(name.size()<mx)name+=' ';
        cout << name << "\t|";
        cout << students[i].math_score << "\t|";
        cout << students[i].english_score << "\t|";
        cout << students[i].science_score << "\t|";
        float average = getTotScore(i, students)/3;
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
    cout << "Student name is " << students[id].full_name << "\n\n";
    cout << "Are you really sure you want to delete this student id?\n";
    cout << "Respond with y/n (yes/no): ";
    char option; get_input(option);
    if(option!='y') return;
    update_file(id);
    cout << "Successfully deleted student\n";
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
    if(option!='y') return;
    string confirm = "delete|all", input;
    cout << "To confirm, please type the following: " << confirm << "\n";
    get_input(input); if(input!=confirm) return;
    ofstream file_out(database_file);
    file_out.close(); load_file(); // clear file, then load new(empty) file to arrays
    cout << "Successfully deleted all students\n";
}

void find_highest_students(){
    if(numStudents==0){
        cout << "\nThere are no students in this system\n";
        return;
    }

    float highest_score = 0;
    for(int i = 0; i < numStudents; i++)
        highest_score = max(highest_score, getTotScore(i,students)/3);

    cout << "\nThe highest score among all students is " << highest_score << "%\n";
    cout << "The following students obtained this score:\n\n";
    for(int i = 0; i < numStudents; i++)
        if(abs(getTotScore(i,students)/3 - highest_score) < EPS)
            cout << "#" << i << " " << students[i].full_name << "\n";
}

void find_lowest_students(){
    if(numStudents==0){
        cout << "\nThere are no students in this system\n";
        return;
    }

    float lowest_score = getTotScore(0,students);
    for(int i = 0; i < numStudents; i++)
        lowest_score = min(lowest_score, getTotScore(i,students)/3);

    cout << "\nThe lowest score among all students is " << lowest_score << "%\n";
    cout << "The following students obtained this score:\n\n";
    for(int i = 0; i < numStudents; i++)
        if(abs(getTotScore(i,students)/3 - lowest_score) < EPS)
           cout << "#" << i << " " << students[i].full_name << "\n";
}

void get_average_per_subject(){
    if(numStudents==0){
        cout << "\nThere are no students in this system\n";
        return;
    }
    float math=0, eng=0, sci=0, avg=0;
    for(int i = 0; i < numStudents; i++){
        math+=students[i].math_score;
        eng+=students[i].english_score;
        sci+=students[i].science_score;
        avg+=getTotScore(i,students)/3;
    }
    math/=numStudents, eng/=numStudents, sci/=numStudents, avg/=numStudents;
    cout << "\nThis is to show all averages\n\n";
    cout << "The average math score: " << math << "\n";
    cout << "The average english score: " << eng << "\n";
    cout << "The average science score: " << sci << "\n";
    cout << "The average percentage: " << avg << "("<< grade_letter(avg) <<")\n\n";
}

bool cmp_student(Student a, Student b){
    float totA = a.math_score+a.english_score+a.science_score;
    float totB = b.math_score+b.english_score+b.science_score;
    if(totA > totB) return true;
    return false;
}

void show_all_report_cards_decreasing(){
    if(numStudents==0){
        cout << "\nThere are no students in this system\n";
        return;
    }

    cout << "\nThis is to show all students' report cards in decreasing order\n\n";
    Student students_copy[numStudents];
    for(int i = 0; i < numStudents; i++)
        students_copy[i] = students[i];

    sort(students_copy, students_copy+numStudents, cmp_student);
    int mx = 12;
    for(int i = 0; i < numStudents; i++)
        mx = max(mx, (int)(students_copy[i].full_name.size()));

    int tot = 57+(mx+1)/8*8;
    print_line(tot);
    cout << "|ID\t|Student Name";
    for(int i = 0; i < (mx+1)/8; i++) cout << "\t";
    cout << "|Math\t|Eng.\t|Sci.\t|Grade\t\t|\n";

    for(int i = 0; i < numStudents; i++){
        print_line(tot);
        cout << "|" << i << "\t|";
        string name = students_copy[i].full_name;
        while(name.size()<mx)name+=' ';
        cout << name << "\t|";
        cout << students_copy[i].math_score << "\t|";
        cout << students_copy[i].english_score << "\t|";
        cout << students_copy[i].science_score << "\t|";
        float average = getTotScore(i,students_copy)/3;
        cout << average;
        cout << "(" << grade_letter(average) << ")";
        if(average<10.0) cout << "\t";
        cout << "\t|\n";
    }
    print_line(tot);
}

int main()
{
    cout << fixed << setprecision(2);
    load_file();
    while(true){
        print_menu();
        int option;
        cout << "Enter your choice: ";
        get_input(option);

        if(option==0){
            cout << "Thanks for visiting. See you next time!\n";
            return 0;
        }
        else if(option==1) add_student();
        else if(option==2){
            if(modify_student()){
                update_file();
                cout << "Student info has successfully been modified\n";
            }
        }
        else if(option==3) show_report_card();
        else if(option==4) show_all_report_cards();
        else if(option==5) delete_student();
        else if(option==6) delete_all_students();
        else if(option==7) find_highest_students();
        else if(option==8) find_lowest_students();
        else if(option==9) get_average_per_subject();
        else if(option==10) show_all_report_cards_decreasing();
        else cout << "Your choice is not valid. Try again!\n";
    }
}
