#include <iostream>
#include <fstream>
using namespace std;

const string status[] = {"pending", "complete"}; // change the names to anything
const int max_task = (int)1e6+10;
const int mx_task_length = 150;
struct Task{
    string title;
    bool done;
} tasks[max_task];
int taskNum = 0;
string database_file = "database.txt";

void addTaskToFile(int id){
    ofstream file_out(database_file, ios::app);
    file_out << tasks[id].title << "\n";
    cout << tasks[id].done << "\n";
    file_out.close();
}

void loadFile(){
    ofstream file_out(database_file, ios::app);
    file_out.close();

    ifstream file_in(database_file);
    taskNum = 0;
    while(true){
        getline(file_in, tasks[taskNum].title);
        if(file_in.eof()) break;
        file_in >> tasks[taskNum].done;
        file_in.ignore(); taskNum++;
    }
    file_in.close();
}

void updateFile(int id=-1){ // the id can be removed from the file
    ofstream file_out(database_file);
    for(int i = 0; i < taskNum; i++){
        if(i==id) continue; // delete current id from file
        file_out << tasks[i].title << "\n" << tasks[i].done << "\n";
    }
    file_out.close(); loadFile();
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

int menuScreen(){
    cout << "This is a Basic To-do List C++ Program\n";
    cout << "(1) Add a new task\n";
    cout << "(2) Mark a task as " << status[1] << "\n";
    cout << "(3) Mark a task as " << status[0] << "\n";
    cout << "(4) Show all tasks and their status\n";
    cout << "(5) Show all " << status[1] << " tasks\n";
    cout << "(6) Show all " << status[0] << " tasks\n";
    cout << "(7) Delete a task\n";
    cout << "(8) Delete all tasks\n";
    cout << "(9) Exit the program\n";
    int choice; cout << "Enter your choice: ";
    get_input(choice); return choice;
}

void addTask(bool skip){
    cout << "Enter the task description: ";
    string description; getline(cin, description);
    if(description.size() > mx_task_length){ // too large
        cout << "\nTask Description length should be at most "
        << mx_task_length << " characters\n";
        return;
    }
    tasks[taskNum].title = description; tasks[taskNum].done = 0;
    cout << "Successfully added \"" << tasks[taskNum].title << "\"\n";
    cout << "Task ID: #" << taskNum << "\n\n";
    addTaskToFile(taskNum); taskNum++;
}

int getID(){
    if(taskNum==0){
        cout << "\nThere are no stored tasks yet\n";
        return -1;
    }
    cout << "Enter the ID of the task: ";
    int id; get_input(id);
    if(id<0 or id>=taskNum){
        cout << "\nInvalid ID\n";
        return -1;
    }
    return id;
}

void flipStatus(bool newStatus){
    int id = getID(); if(id==-1) return;
    if(tasks[id].done==newStatus){
        cout << "Task already marked as '" << status[newStatus] << "'\n";
        return;
    }
    tasks[id].done = !tasks[id].done; // flipping
    cout << "Successfully changed status of task \"" << tasks[id].title << "\" to '";
    cout << status[newStatus] << "'\n"; updateFile();
}

void printChar(int num, char c, bool newLine){
    for(int i = 0; i < num; i++) cout << c;
    if(newLine) cout << "\n";
}

// type=2 means all, type=1 means only complete, type=0 means only incomplete
void displayTasks(int type){
    int tot = 0, title_length = 0, status_length = 0;
    for(int i = 0; i < taskNum; i++){
        if(tasks[i].done==type or type==2){
            tot++;

            // description column has to be at least the size of possible description messages
            if(title_length < tasks[i].title.size())
                title_length = tasks[i].title.size();

            // status column has to be at least the size of possible status messages
            if(status_length < status[tasks[i].done].size())
                status_length=status[tasks[i].done].size();
        }
    }

    if(tot==0){
        cout << "There are no tasks to display\n";
        return;
    }

    /*
        * Responsive table, just some for loops to calculate
          how many spaces to leave for each column
        * The first Column which is ID is ok with 8 spaces
        * For the other 2 columns, you just put the column name
          inside the variables below this and the rest is fixed
    */

    string title = "TASK DESCRIPTION", Status = "STATUS";

    // make sure they must be at least the column heading sizes
    if(status_length < Status.size()) status_length = Status.size();
    if(title_length < title.size()) title_length = title.size();
    title_length+=3; status_length+=3; // some extra space

    int num_dash = 8+title_length+status_length+3;
    printChar(num_dash,'-',1);

    cout << "|ID\t|" << title;
    printChar(title_length-title.size(),' ',0);
    cout << "|"; cout << Status;
    printChar(status_length-Status.size(),' ',0);
    cout << "|\n";

    for(int i = 0; i < taskNum; i++){
        if(tasks[i].done==type or type==2){
            printChar(num_dash,'-',1);
            cout << "#" << i << "\t|";
            cout << tasks[i].title;
            printChar(title_length-tasks[i].title.size(),' ',0);
            cout << "|"; cout << status[tasks[i].done];
            printChar(status_length-status[tasks[i].done].size(),' ',0);
            cout << "|\n";
        }
    }
    printChar(num_dash,'-',1);
}

void deleteTask(){
    int id = getID(); if(id==-1) return;
    cout << "Do you really want to delete \"" << tasks[id].title << "\"?\n";
    cout << "Respond with y if so: "; char response; get_input(response);
    if(response!='y' and response!='Y') return;
    cout << "Deleting task...\n"; updateFile(id);
    cout << "Successfully deleted the task\n";
}

void deleteAllTasks(){
    cout << "Do you really want to delete all tasks???\n";
    cout << "Respond with y if so: "; char response; get_input(response);
    if(response!='y' and response!='Y') return;

    string confirm = "delete|all", input;
    cout << "To confirm, please type the following: " << confirm << "\n";
    get_input(input); if(input!=confirm) return;

    cout << "Deleting all tasks...\n";
    ofstream file_out(database_file);
    file_out.close(); loadFile();
    cout << "Successfully deleted all tasks\n";
}

int main()
{
    // store our data to a file
    // load a data from a file, to the variables of our program
    // append a task info to the end of a file
    loadFile();
    while(true){
        cout << "\n";
        int choice = menuScreen();
        cout << "\n";
        if(choice!=1 and choice!=9 and taskNum==0){
            cout << "There are no tasks yet\n"; continue;
        }
        if(choice==1){
            cout << "Enter the number of tasks to add: ";
            int num; get_input(num);
            for(int i = 0; i < num; i++) addTask(i==0);
        }
        else if(choice==2){
            cout << "Enter the number of tasks to mark: ";
            int num; get_input(num);
            while(num>0) flipStatus(1), num--;
        }
        else if(choice==3){
            cout << "Enter the number of tasks to mark: ";
            int num; get_input(num);
            while(num>0) flipStatus(0), num--;
        }
        else if(choice==4) displayTasks(2);
        else if(choice==5) displayTasks(1);
        else if(choice==6) displayTasks(0);
        else if(choice==7) deleteTask();
        else if(choice==8) deleteAllTasks();
        else if(choice==9){
            cout << "Exiting the program...\n";
            return 0;
        }
        else cout << "Invalid input\n";
    }
}
