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

void print(string text, bool endlBefore) {
    cout << (endlBefore ? "\n" : "") << text << endl;
}

void print(string text) {
    print(text, false);
}

void print() {
    print("");
}

int main() {
    START:

    if (loggedUser == "0") {
        SELECT_LOGIN_OPTION:

        print("Welcome to our ATM, please select what you want to do.");
        print("1 - Register a new account.");
        print("2 - Log into an existing account.");
        print();

        int loginInput;
        cin >> loginInput;
        if (loginInput == 1) {
            REGISTER_ENTER_USERNAME:
            bool invalidInput = false;
            bool taken = false;
            string newUsername;
            print("Enter your new username: ", true);
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
                print("Username already taken! Try again.");
                goto REGISTER_ENTER_USERNAME;
            } else if (invalidInput) {
                print("Username had less than 3 characters or contained numbers! Try again.");
                goto REGISTER_ENTER_USERNAME;
            }

            REGISTER_ENTER_PASSWORD:
            string newPassword;
            print("Enter your new password: ", true);
            cin >> newPassword;
            if (newPassword.length() < 8) {
                print("Passwords have to contain at least 8 characters.");
                goto REGISTER_ENTER_PASSWORD;
            }

            users.push_back(newUsername);
            passwords.push_back(newPassword);

            print("Successfully registered!", true);
            sleep(2);
        } else if (loginInput == 2) {
            LOGIN_ENTER_USERNAME:
            bool invalidInput = true;
            int userNumber = 0;
            string user;
            print("Enter your username: ", true);
            cin >> user;
            for (string username: users) {
                if (strcasecmp(user.c_str(), username.c_str()) == 0) {
                    invalidInput = false;
                    break;
                }

                userNumber++;
            }

            if (invalidInput) {
                print("Invalid username! Try again.");
                goto LOGIN_ENTER_USERNAME;
            }

            LOGIN_ENTER_PASSWORD:
            string password;
            print("Enter your password: ", true);
            cin >> password;
            if (password != passwords[userNumber]) {
                print("Wrong password! Try again.");
                goto LOGIN_ENTER_PASSWORD;
            }

            loggedUser = users[userNumber];

            print("Successfully logged in!", true);
            sleep(2);
        } else {
            goto SELECT_LOGIN_OPTION;
        }

        goto START;
    } else {
        MAIN_MENU:
        print("Logged in as: " + loggedUser, true);
        //TODO: ATM
    }

    return 0;
}
