#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>

using namespace std;

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

string loggedUser = "0";

int main() {
    START:

    if (loggedUser == "0") {
        SELECT_LOGIN_OPTION:

        cout << "------------------------------------------------------" << endl;
        cout << "Welcome to our ATM, please select what you want to do." << endl;
        cout << "1 - Register a new account." << endl;
        cout << "2 - Log into an existing account." << endl;
        cout << "------------------------------------------------------" << endl;
        cout << endl << "Selected option: " << endl;

        int option;
        cin >> option;
        switch (option) {
            case 1: {
            REGISTER_ENTER_USERNAME:
                bool invalidInput = false;
                bool taken = false;
                string newUsername;
                cout << endl << "Enter your new username: " << endl;
                cin >> newUsername;
                if (newUsername.length() < 3 || newUsername.find_first_of("0123456789") != string::npos) {
                    invalidInput = true;
                }

                if (!invalidInput) {
                    for (string username: users) {
                        if (strcasecmp(newUsername.c_str(), username.c_str()) == 0) {
                            taken = true;
                            break;
                        }
                    }
                }

                if (taken) {
                    cout << endl << "Username already taken! Try again." << endl;
                    goto REGISTER_ENTER_USERNAME;
                } else if (invalidInput) {
                    cout << endl << "Username had less than 3 characters or contained numbers! Try again." << endl;
                    goto REGISTER_ENTER_USERNAME;
                }

            REGISTER_ENTER_PASSWORD:
                string newPassword;
                cout << endl << "Enter your new password: " << endl;
                cin >> newPassword;
                if (newPassword.length() < 8) {
                    cout << endl << "Passwords have to contain at least 8 characters." << endl;
                    goto REGISTER_ENTER_PASSWORD;
                }

                users.push_back(newUsername);
                passwords.push_back(newPassword);

                cout << endl << "Successfully registered!" << endl;
                sleep(2);
                system("cls");
                break;
            }

            case 2: {
                LOGIN_ENTER_USERNAME:
                bool invalidInput = true;
                int userNumber = 0;
                string user;
                cout << endl << "Enter your username: " << endl;
                cin >> user;
                for (string username: users) {
                    if (strcasecmp(user.c_str(), username.c_str()) == 0) {
                        invalidInput = false;
                        break;
                    }

                    userNumber++;
                }

                if (invalidInput) {
                    cout << endl << "Invalid username! Try again." << endl;
                    goto LOGIN_ENTER_USERNAME;
                }

                LOGIN_ENTER_PASSWORD:
                string password;
                cout << endl << "Enter your password: " << endl;
                cin >> password;
                if (password != passwords[userNumber]) {
                    cout << endl << "Incorrect password! Try again." << endl;
                    goto LOGIN_ENTER_PASSWORD;
                }

                loggedUser = users[userNumber];

                cout << endl << "Successfully logged in as " << loggedUser << "!" << endl;
                sleep(2);
                system("cls");
                break;
            }

            default: {
                goto SELECT_LOGIN_OPTION;
            }
        }

        goto START;
    } else {
        MAIN_MENU:
        cout << endl << "Logged in as " << loggedUser << "." << endl;
        //TODO: ATM
    }

    return 0;
}
