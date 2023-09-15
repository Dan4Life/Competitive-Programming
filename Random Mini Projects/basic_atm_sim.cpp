/*
1. Create account (edit account afterwards)
    Name, DOB, email, password
2. Log in to account
3. Check their balance (int -> balance)
4. Deposit to the account (int -> amount, amount should be positive)
5. Withdraw from the account (int -> amount, amount <= balance)
6. Log out of your account
7. Exit
*/

#include <iostream>
#include <iomanip>
using namespace std;

// can be extended to multiple users
double balance = 0;
string name, dob, email, password;
bool isCreated = false, isLoggedIn = false;

// Returns an error code, and prints error message
int errorLog(){
    if(!isCreated){
        cout << "\nYou haven't made an account yet\n";
        return 1;
    }
    if(!isLoggedIn){
        cout << "\nLog into your account first\n";
        return 2;
    }
    return 0; // No errors
}

void print_menu(){
    cout << "\nWelcome to a basic ATM Simulator\n";

    if(isCreated) cout << "1. Edit account details\n";
    else cout << "1. Create account (only once) \n";

    cout << "2. Log in to your account\n";
    cout << "3. Check your details\n";
    cout << "4. Deposit to the account\n";
    cout << "5. Withdraw from the account\n";
    cout << "6. Log out of your account\n";
    cout << "7. Exit the program\n";
}

bool validatePassword(bool showText=true){
    if(showText) cout << "Enter your Password: ";
    string new_password; cin >> new_password;

    bool isDigit=false, isLower=false, isUpper=false, isSymbol=false;
    if(new_password.size()<8){
        cout << "Error: Password should have at least 8 characters\n";
        return false;
    }

    for(int i = 0; i < new_password.size(); i++){
        char c = new_password[i];
        if(c>='0' and c<='9') isDigit=1;
        else if(c>='a' and c<='z') isLower=1;
        else if(c>='A' and c<='Z') isUpper=1;
        else isSymbol=true;
    }

    if(!isDigit or !isLower or !isUpper or !isSymbol){
        cout << "Error: Password must have at least 1 digit, lowercase, uppercase alphabet, symbol\n";
        return false;
    }

    cout << "Confirm your Password: ";
    string confirm; cin >> confirm;
    if(confirm!=new_password){
        cout << "Error: Passwords don't match\n";
        return false;
    }
    password=new_password;
    return true;
}

void createAccount(){
    cout << "\nThis is to create an account\n";
    cout << "Enter your Name: "; cin.ignore(); getline(cin,name);
    cout << "Enter your DOB: "; getline(cin,dob);
    cout << "Enter your Email: "; cin >> email;

    if(!validatePassword()) return;
    cout << "Account successfully created\n";
    isCreated = true;
}

bool verifyEdit(string edit){
    cout << "Do you want to edit " << edit << "? y/n ";
    char option; cin >> option;
    if(option=='y'){
        cout << "Enter your new " << edit << ": ";
        return true;
    }
    return false;
}

void editAccount(){
    if(errorLog()) return;
    cout << "\nThis is to edit an account\n";

    if(verifyEdit("name")) cin.ignore(), getline(cin,name);
    if(verifyEdit("dob")) cin.ignore(), getline(cin,dob);
    if(verifyEdit("email")) cin >> email;
    if(verifyEdit("password")){
        if(!validatePassword(0)) return;
        cout << "Account details successfully edited\n";
    }
}

void loginAccount(){
    if(isLoggedIn){
        cout << "\nYou are already logged in\n";
        return;
    }
    if(!isCreated){
        cout << "\nYou haven't made an account yet\n";
        return;
    }

    string input_email, input_password;
    cout << "\nThis is the login page\n";
    cout << "Enter your email: "; cin >> input_email;
    cout << "Enter your password: "; cin >> input_password;
    if(input_email!=email){
        cout << "\nThere is no account associated with this email\n";
        return;
    }
    if(input_password!=password){
        cout << "\nPassword is incorrect\n";
        return;
    }
    cout << "\nWelcome back, " << name << "\n";
    isLoggedIn=true;
}

void printDetails(){
    if(errorLog()) return;
    cout << "\nDo you want to also view your password? y/n ";
    char choice; cin >> choice;

    string temp_password = "";
    temp_password+=password[0]; //showing only first character initially
    temp_password+="*******";
    if(choice=='y') temp_password = password;

    cout << "These are your account details\n";
    cout << "Name: " << name << "\n";
    cout << "DOB: " << dob << "\n";
    cout << "Email: " << email << "\n";
    cout << "Password: " << temp_password  << "\n";
    cout << "Account balance: $" << balance << "\n";
}

void deposit(){
    if(errorLog()) return;
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
    if(errorLog()) return; // if errorLog does not return 0
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

void logoutAccount(){
    if(errorLog()) return;

    cout << "\nDo you really want to log out? y/n ";
    char choice; cin >> choice;
    if(choice=='y'){
        cout << "Logging out...\n";
        isLoggedIn=false;
    }
}

int main()
{
    cout << fixed << setprecision(2); // fixes decimal places to 2
    while(true){
        print_menu();
        cout << "Enter your choice: ";
        int choice; cin >> choice;
        if(choice==1){
            // After creating account, user can only edit account from now on.
            // This should actually only apply if also logged in
            // (in case of extending to multiple users...) but it's ok for 1 user like this
            if(isCreated) editAccount();
            else createAccount();
        }
        else if(choice==2) loginAccount();
        else if(choice==3) printDetails();
        else if(choice==4) deposit();
        else if(choice==5) withdraw();
        else if(choice==6) logoutAccount();
        else if(choice==7){ cout << "Goodbye\n"; return 0; }
        else cout << "\nInvalid input\n";
        cout << "\n";
    }
}
