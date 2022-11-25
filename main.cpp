#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>

using namespace std;

int loggedUser = -1;

vector<string> users = {
        "Adam",
        "Pepa",
        "Vojta"
};

vector<string> passwords = {
        "adamMadam123Pog",
        "pepikZdepa963",
        "vojtik666XD"
};

vector<int> balances = {
        250,
        1550,
        870
};

int main() {
    START:
    if (loggedUser == -1) {
        SELECT_LOGIN_OPTION:
        cout << "------------------------------------------------------" << endl;
        cout << "Welcome to our ATM, please select what you want to do." << endl << endl;
        cout << "1 - Register a new account." << endl;
        cout << "2 - Log into an existing account." << endl;
        cout << "3 - Exit." << endl;
        cout << "------------------------------------------------------" << endl << endl;
        cout << "Select an option: " << endl;
        string option;
        cin >> option;
        cout << endl;
        if (option == "1") {
            system("cls");

            cout << "------------------------------------------------------" << endl;
            cout << "Register a new account" << endl;
            cout << "------------------------------------------------------" << endl << endl;

            REGISTER_ENTER_USERNAME:
            string newUsername;
            cout << "Enter your new username: " << endl;
            cin >> newUsername;
            cout << endl;
            if (newUsername.length() < 3) {
                cout << "Usernames have to contain at least 3 characters." << endl;
                goto REGISTER_ENTER_USERNAME;
            } else if (newUsername.length() > 16) {
                cout << "Usernames cant have more than 16 characters." << endl;
                goto REGISTER_ENTER_USERNAME;
            } else if (newUsername.find_first_of("0123456789") != string::npos) {
                cout << "Usernames can't contain numbers." << endl;
                goto REGISTER_ENTER_USERNAME;
            } else if (newUsername.find_first_of(' ') != string::npos) {
                cout << "Usernames can't contain spaces." << endl;
                goto REGISTER_ENTER_USERNAME;
            }

            for (const string &username: users) {
                if (strcasecmp(newUsername.c_str(), username.c_str()) == 0) {
                    cout << "Username already taken! Try again." << endl;
                    goto REGISTER_ENTER_USERNAME;
                }
            }

            REGISTER_ENTER_PASSWORD:
            string newPassword;
            cout << "Enter your new password: " << endl;
            cin >> newPassword;
            cout << endl;
            if (newPassword.length() < 8) {
                cout << "Passwords have to contain at least 8 characters." << endl;
                goto REGISTER_ENTER_PASSWORD;
            } else if (newPassword.find_first_of(' ') != string::npos) {
                cout << "Passwords can't contain spaces." << endl;
                goto REGISTER_ENTER_PASSWORD;
            }

            users.push_back(newUsername);
            passwords.push_back(newPassword);
            balances.push_back(0);

            cout << "Successfully registered with username " << newUsername << "!" << endl;
            sleep(2);
            system("cls");

            goto SELECT_LOGIN_OPTION;
        } else if (option == "2") {
            system("cls");

            cout << "------------------------------------------------------" << endl;
            cout << "Log into an existing account" << endl;
            cout << "------------------------------------------------------" << endl << endl;

            LOGIN_ENTER_USERNAME:
            int userNumber = 0;
            string user;
            cout << "Enter your username: " << endl;
            cin >> user;
            cout << endl;
            bool invalid = true;
            for (const string &username: users) {
                if (strcasecmp(user.c_str(), username.c_str()) == 0) {
                    invalid = false;
                    break;
                }

                userNumber++;
            }

            if (invalid) {
                cout << "Invalid username! Try again." << endl;
                goto LOGIN_ENTER_USERNAME;
            }

            LOGIN_ENTER_PASSWORD:
            string password;
            cout << "Enter your password: " << endl;
            cin >> password;
            cout << endl;
            if (password != passwords[userNumber]) {
                cout << "Incorrect password! Try again." << endl;
                goto LOGIN_ENTER_PASSWORD;
            }

            loggedUser = userNumber;
            cout << "Successfully logged in as " << users[loggedUser] << "!" << endl;
            sleep(2);
            system("cls");
        } else if (option == "3") {
            system("cls");
            cout << "Exiting...";
            sleep(1);
            return 0;
        } else {
            cout << "Invalid option!" << endl;
            sleep(2);
            system("cls");
            goto SELECT_LOGIN_OPTION;
        }

        goto START;
    } else {
        MAIN_MENU:
        cout << "------------------------------------------------------" << endl;
        cout << "Logged in as " << users[loggedUser] << "." << endl;
        cout << "Your balance is " << balances[loggedUser] << "CZK." << endl << endl;
        cout << "1 - Withdraw money." << endl;
        cout << "2 - Send money." << endl;
        cout << "3 - Log out." << endl;
        cout << "------------------------------------------------------" << endl << endl;
        cout << "Select an option: " << endl;
        string option;
        cin >> option;
        system("cls");
        if (option == "1") {
            cout << "------------------------------------------------------" << endl;
            cout << "Money withdrawal" << endl;
            cout << "------------------------------------------------------" << endl << endl;
            cout << "How much money do you want to withdraw?" << endl;
            int money;
            cin >> money;
            cout << endl;
            if (money < 0) {
                cout << "You can't withdraw negative money." << endl;
                sleep(2);
                system("cls");
                goto MAIN_MENU;
            } else if (balances[loggedUser] - money < 0) {
                cout << "You don't have enough money to withdraw " << money << "CZK." << endl;
                sleep(2);
                system("cls");
                goto MAIN_MENU;
            } else {
                balances[loggedUser] -= money;
                cout << "You have withdrawn " << money << "CZK." << endl;
                cout << "Your balance is now " << balances[loggedUser] << "CZK." << endl;
                sleep(2);
                system("cls");
                goto MAIN_MENU;
            }
        } else if (option == "2") {
            system("cls");
            cout << "------------------------------------------------------" << endl;
            cout << "Send money" << endl;
            cout << "------------------------------------------------------" << endl << endl;
            cout << "Who do you want to send money to?" << endl;
            string name;
            cin >> name;
            cout << endl;
            int userNumber = 0;
            bool invalid = true;
            for (const string &username: users) {
                if (strcasecmp(name.c_str(), username.c_str()) == 0) {
                    invalid = false;
                    break;
                }

                userNumber++;
            }

            if (strcasecmp(name.c_str(), users[loggedUser].c_str()) == 0) {
                cout << "You can't send money to yourself." << endl;
                sleep(2);
                system("cls");
                goto MAIN_MENU;
            } else if (invalid) {
                cout << "This user does not exist." << endl;
                sleep(2);
                system("cls");
                goto MAIN_MENU;
            }

            cout << "How much money do you want to send to " << users[userNumber] << "?" << endl;
            int money;
            cin >> money;
            if (money < 0) {
                cout << "You can't send negative money." << endl;
                sleep(2);
                system("cls");
                goto MAIN_MENU;
            } else if (balances[loggedUser] - money < 0) {
                cout << endl << "You don't have enough money to send " << money << "CZK to " << users[userNumber] << "." << endl;
                sleep(2);
                system("cls");
                goto MAIN_MENU;
            } else {
                balances[loggedUser] -= money;
                balances[userNumber] += money;
                cout << endl << "You have sent " << money << "CZK to " << users[userNumber] << "." << endl;
                cout << "Your balance is now " << balances[loggedUser] << "CZK." << endl;
                sleep(2);
                system("cls");
                goto MAIN_MENU;
            }
        } else if (option == "3") {
            cout << "Logging out..." << endl;
            loggedUser = -1;
            sleep(2);
            system("cls");
            goto START;
        } else {
            cout << "Invalid option!" << endl;
            sleep(2);
            system("cls");
            goto MAIN_MENU;
        }
    }
}
