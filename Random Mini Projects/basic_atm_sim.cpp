/*
1. Create account (edit account afterwards)
    Name, DOB, email, password
2. Login to account
3. Check their balance (int -> balance)
4. Deposit to the account (int -> amount, amount should be positive)
5. Withdraw from the account (int -> amount, amount <= balance)
6. Exit
*/

#include <iostream>
#include <iomanip>
using namespace std;

string name, dob, email, password;
double balance = 0;
bool isCreated = false, isLoggedIn = false;

void print_menu(){
    cout << "\nWelcome to a basic ATM Simulator\n";

    if(isCreated) cout << "1. Edit account details\n";
    else cout << "1. Create account (only once) \n";

    cout << "2. Login to your account\n";
    cout << "3. Check your details\n";
    cout << "4. Deposit to the account\n";
    cout << "5. Withdraw from the account\n";
    cout << "6. Exit the program\n";
}

bool validatePassword(bool showText=true){
    if(showText) cout << "Enter your Password: ";
    cin >> password;

    bool isDigit=false, isLower=false, isUpper=false, isSymbol=false;
    if(password.size()<8){
        cout << "Password should have at least 8 characters\n";
        return false;
    }

    for(int i = 0; i < password.size(); i++){
        char c = password[i];
        if(c>='0' and c<='9') isDigit=1;
        else if(c>='a' and c<='z') isLower=1;
        else if(c>='A' and c<='Z') isUpper=1;
        else isSymbol=true;
    }

    if(!isDigit or !isLower or !isUpper or !isSymbol){
        cout << "Password must have at least 1 digit, lowercase, uppercase alphabet, symbol\n";
        return false;
    }
    return true;
}

bool createAccount(){
    cout << "\nThis is to create an account\n";
    cout << "Enter your Name: ";
    cin.ignore(); getline(cin,name);
    cout << "Enter your DOB: "; getline(cin,dob);
    cout << "Enter your Email: "; cin >> email;

    if(!validatePassword()){
        cout << "Error: Password is not strong\n";
        return false;
    }

    cout << "Confirm your Password: ";
    string confirm; cin >> confirm;
    if(confirm!=password){
        cout << "Error: Passwords don't match\n";
        return false;
    }
    cout << "Account successfully created\n";
    return true;
}

bool verifyEdit(string edit){
    cout << "Do you want to edit " << edit << "? y/n ";
    char option; cin >> option;
    if(option=='y'){
        cout << "Enter your " << edit << ": ";
        return true;
    }
    return false;
}

void editAccount(){
    if(!isCreated){
        cout << "\nYou haven't made an account yet\n";
        return;
    }
    if(!isLoggedIn){
        cout << "\nLog into your account first\n";
        return;
    }
    cout << "\nThis is to edit an account\n";

    if(verifyEdit("name")) cin.ignore(), getline(cin,name);
    if(verifyEdit("dob")) cin.ignore(), getline(cin,dob);
    if(verifyEdit("email")) cin >> email;
    if(verifyEdit("password")){
        if(!validatePassword(false)){
            cout << "Error: Password is not strong\n";
            return;
        }
        cout << "Confirm your Password: ";
        string confirm; cin >> confirm;
        if(confirm!=password) cout << "Error: Passwords don't match\n";
        else cout << "Account details successfully editted\n";
    }
}

bool loginAccount(){
    if(!isCreated){
        cout << "\nYou haven't made an account yet\n";
        return false;
    }
    if(isLoggedIn){
        cout << "\nYou are already logged in\n";
        return true;
    }

    string input_email, input_password;
    cout << "\nThis is the login page\n";
    cout << "Enter your email: "; cin >> input_email;
    cout << "Enter your password: "; cin >> input_password;
    if(input_email!=email){
        cout << "There is no account associated with this email\n";
        return false;
    }
    if(input_password!=password){
        cout << "Password is incorrect\n";
        return false;
    }
    cout << "Welcome back, " << name << "\n";
    return true;
}

void printDetails(){
    if(!isCreated){
        cout << "\nYou haven't made an account yet\n";
        return;
    }
    if(!isLoggedIn){
        cout << "\nLog into your account first\n";
        return;
    }
    cout << "\nDo you want to also view your password? y/n ";

    char choice; cin >> choice;
    string temp_password = "";
    temp_password+=password[0];
    temp_password+="********";
    if(choice=='y') temp_password = password;

    cout << "These are your account details\n";
    cout << "Name: " << name << "\n";
    cout << "DOB: " << dob << "\n";
    cout << "Email: " << email << "\n";
    cout << "Password: " << temp_password  << "\n";
    cout << "Account balance: $" << balance << "\n";
}

void deposit(){
    if(!isCreated){
        cout << "\nYou haven't made an account yet\n";
        return;
    }
    if(!isLoggedIn){
        cout << "\nLog into your account first\n";
        return;
    }
    cout << "\nThis is the deposit page\n";

    double amount;
    cout << "Enter the amount to be deposited: \n";
    cin >> amount;

    if(amount<=0){
        cout << "Amount must be positive\n";
        return;
    }

    balance+=amount;
    cout << "Your new balance is $" << balance << "\n";
}

void withdraw(){
    if(!isCreated){
        cout << "\nYou haven't made an account yet\n";
        return;
    }
    if(!isLoggedIn){
        cout << "\nLog into your account first\n";
        return;
    }
    cout << "\nThis is the withdraw page\n";

    double amount;
    cout << "Enter the amount to be withdrawn: \n";
    cin >> amount;

    if(amount<=0){
        cout << "Amount must be positive\n";
        return;
    }
    if(amount>balance){
        cout << "Amount exceeds your account balance\n";
        return;
    }

    balance-=amount;
    cout << "Your new balance is $" << balance << "\n";
}

int main()
{
    cout << fixed << setprecision(2);
    while(true){
        print_menu();
        cout << "Enter your choice: ";
        int choice; cin >> choice;
        if(choice==1){
            if(isCreated) editAccount();
            else isCreated = createAccount();
        }
        else if(choice==2) isLoggedIn = loginAccount();
        else if(choice==3) printDetails();
        else if(choice==4) deposit();
        else if(choice==5) withdraw();
        else if(choice==6){
            cout << "Goodbye\n";
            return 0;
        }
        else cout << "Invalid input\n";
        cout << "\n";
    }
}
