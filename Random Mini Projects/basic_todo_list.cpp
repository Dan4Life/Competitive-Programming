#include <iostream>
using namespace std;

const string status[] = {"pending", "complete"}; // change the names to anything
const int max_task = (int)1e6+10;
const int mx_task_length = 150;
string tasks[max_task];
bool done[max_task];
int taskNum = 0;

int menuScreen(){
    cout << "This is a Basic To-do List C++ Program\n";
    cout << "(1) Add a new task\n";
    cout << "(2) Mark a task as " << status[1] << "\n";
    cout << "(3) Mark a task as " << status[0] << "\n";
    cout << "(4) Show all tasks and their status\n";
    cout << "(5) Show all " << status[1] << " tasks\n";
    cout << "(6) Show all " << status[0] << " tasks\n";
    cout << "(7) Exit the program\n";
    int choice;
    cout << "Enter your choice: ";
    cin >> choice; return choice;
}

void addTask(bool skip){
    cout << "Enter the task description: ";
    string description;
    if(skip) cin.ignore(); // this is annoying
    getline(cin, description);
    if(description.size() > mx_task_length){ // too large
        cout << "\nTask Description length should be at most "
        << mx_task_length << " characters\n";
        return;
    }
    tasks[taskNum] = description; done[taskNum] = 0;
    cout << "Successfully added \"" << tasks[taskNum] << "\"\n";
    cout << "Task ID: #" << taskNum << "\n\n"; taskNum++;
}

int getID(){
    if(taskNum==0){
        cout << "\nThere are no stored tasks yet\n";
        return -1;
    }
    cout << "Enter the ID of the task: ";
    int id; cin >> id;
    if(id<0 or id>=taskNum){
        cout << "\nInvalid ID\n";
        return -1;
    }
    return id;
}

void flipStatus(bool newStatus){
    int id = getID(); if(id==-1) return;
    if(done[id]==newStatus){
        cout << "Task already marked as '" << status[newStatus] << "'\n";
        return;
    }
    done[id] = !done[id]; // flipping
    cout << "Successfully changed status of task \"" << tasks[id] << "\" to '";
    cout << status[newStatus] << "'\n";
}

void printChar(int num, char c, bool newLine){
    for(int i = 0; i < num; i++) cout << c;
    if(newLine) cout << "\n";
}

// type=2 means all, type=1 means only complete, type=0 means only incomplete
void displayTasks(int type){
    int tot = 0, title_length = 0, status_length = 0;
    for(int i = 0; i < taskNum; i++){
        if(done[i]==type or type==2){
            tot++;

            // description column has to be at least the size of possible description messages
            if(title_length < tasks[i].size())
                title_length = tasks[i].size();

            // status column has to be at least the size of possible status messages
            if(status_length < status[done[i]].size())
                status_length=status[done[i]].size();
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
        if(done[i]==type or type==2){
            printChar(num_dash,'-',1);
            cout << "#" << i << "\t|";
            cout << tasks[i];
            printChar(title_length-tasks[i].size(),' ',0);
            cout << "|"; cout << status[done[i]];
            printChar(status_length-status[done[i]].size(),' ',0);
            cout << "|\n";
        }
    }
    printChar(num_dash,'-',1);
}

int main()
{
    while(true){
        cout << "\n";
        int choice = menuScreen();
        cout << "\n";
        if(choice==1){
            cout << "Enter the number of tasks to add: ";
            int num; cin >> num;
            for(int i = 0; i < num; i++) addTask(i==0);
        }
        else if(choice==2){
            cout << "Enter the number of tasks to mark: ";
            int num; cin >> num;
            while(num>0) flipStatus(1), num--;
        }
        else if(choice==3){
            cout << "Enter the number of tasks to mark: ";
            int num; cin >> num;
            while(num>0) flipStatus(0), num--;
        }
        else if(choice==4) displayTasks(2);
        else if(choice==5) displayTasks(1);
        else if(choice==6) displayTasks(0);
        else if(choice==7){
            cout << "Exiting the program...\n";
            return 0;
        }
        else cout << "Invalid input\n";
    }
}
