#ifndef ADMIN_H
#define ADMIN_H

#include<iostream>
#include<fstream>
#include<termios.h>   // For termios
#include<unistd.h>    // For STDIN_FILENO

using namespace std;

class Admin {
protected:

    static string getPasswordInput() {
        string password;
        char ch;

        termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);          // Save old terminal settings
        newt = oldt;
        newt.c_lflag &= ~(ECHO);                 // Disable echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set new settings

        while ((ch = getchar()) != '\n') {
            if (ch == 127 || ch == '\b') {       // 127 = Backspace on Linux
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            } else {
                password += ch;
                cout << '*';
            }
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
        return password;
    }

    static void addAdminUser() {
        string newUsername, newPassword, confirmPassword;

        cout << "\n\n\tEnter New Admin Username: ";
        cin >> newUsername;
        cin.ignore(); // clear newline

        cout << "\n\n\tEnter New Admin Password: ";
        newPassword = getPasswordInput();

        cout << "\n\n\tConfirm Password: ";
        confirmPassword = getPasswordInput();

        if (newPassword != confirmPassword) {
            cout << "\n\n\tError: Passwords do not match. Admin user not added.";
            cout << "\n\tPress Enter to continue...";
            cin.ignore();
            return;
        }

        ofstream adminData("Data/admindatabase.txt", ios::app);
        if (!adminData) {
            cerr << "\n\n\tError: Unable to access admindatabase file.";
            cout << "\n\tPress Enter to continue...";
            cin.ignore();
            return;
        }

        adminData << newUsername << ' ' << newPassword << '\n';
        adminData.close();

        cout << "\n\n\tNew Admin User Added Successfully!";
        cout << "\n\tPress Enter to continue...";
        cin.ignore();
    }

    static bool authorizeAdmin() {
        const string defaultAdminUsername = "admin";
        const string defaultAdminPassword = "1234";

        string enteredUsername, enteredPassword;

        cout << "\n\n\tEnter Admin Username: ";
        cin >> enteredUsername;
        cin.ignore(); // clear newline

        cout << "\n\tEnter Admin Password: ";
        enteredPassword = getPasswordInput();

        if (enteredUsername == defaultAdminUsername && enteredPassword == defaultAdminPassword) {
            cout << "\n\tDefault Admin Login Successful!";
            return true;
        }

        ifstream adminFile("Data/admindatabase.txt");
        string fileUsername, filePassword;
        while (adminFile >> fileUsername >> filePassword) {
            if (fileUsername == enteredUsername && filePassword == enteredPassword) {
                cout << "\n\tAdmin Login Successful!";
                adminFile.close();
                return true;
            }
        }

        adminFile.close();
        cout << "\n\tLogin Failed! Invalid Username or Password.";
        return false;
    }
};

#endif
