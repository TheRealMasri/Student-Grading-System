#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

//declaring the functions
void addOne();
void searchOne(const string& fileName, const string& nameToSearch);
void addSubjectAndGrade();
void searchSubjectAndGrade(const string& fileName);
void showTopStudent();
string toLowercase(const string& input);

int main()
{
    while (1) {

        cout << "\n--- Student Management System ---\n";
        cout << "1. Add/search student name\n";
        cout << "2. Add/search student subjects and grades\n";
        cout << "3. Show top-performing student\n";
        cout << "4. Exit the program\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;


        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            while (1) {
                string operation;
                cout << "\n1. Add student names\n";
                cout << "2. Search student names\n";
                cout << "3. Back to main menu\n";
                cout << "Enter your choice: ";

                int subChoice;
                cin >> subChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (subChoice == 1) {
                    addOne();
                }
                else if (subChoice == 2) {
                    string name;
                    cout << "Enter name to search: ";
                    getline(cin, name);
                    searchOne("searchOne.txt", name);
                }
                else if (subChoice == 3) {
                    break;
                }
                else {
                    cout << "Invalid choice. Please try again.\n";
                }
            }
            break;
        }
        case 2: {
            while (1) {
                string operation;
                cout << "\n1. Add student subject and grade\n";
                cout << "2. Search student subjects\n";
                cout << "3. Search student grades\n";
                cout << "4. Back to main menu\n";
                cout << "Enter your choice: ";

                int subChoice;
                cin >> subChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (subChoice == 1) {
                    addSubjectAndGrade();
                }
                else if (subChoice == 2) {
                    searchSubjectAndGrade("searchSubjectAndGrade.txt");
                }
                else if (subChoice == 3) {
                    searchSubjectAndGrade("searchSubjectAndGrade.txt");
                }
                else if (subChoice == 4) {
                    break;
                }
                else {
                    cout << "Invalid choice. Please try again.\n";
                }
            }
            break;
        }
        case 3:
            showTopStudent();
            break;
        case 4:
            cout << "Exiting the program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            return 0;
        }
    }
    return 0;
}

string toLowercase(const string& input)
{
    string lowerCaseInput = input;
    transform(lowerCaseInput.begin(), lowerCaseInput.end(), lowerCaseInput.begin(), ::tolower);
    return lowerCaseInput;
}

void addOne()
{
    vector<string> names;
    string input;

    cout << "Enter student names (type 'stop' to finish):\n";
    while (1) {
        getline(cin, input);
        if (input == "stop") break;
        if (!input.empty()) names.push_back(input);
    }

    if (names.empty()) {
        cout << "No names entered.\n";
        return;
    }

    ofstream outFile("searchOne.txt", ios::app);
    if (!outFile) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    vector<string>::iterator it;
    for (it = names.begin(); it != names.end(); ++it) {
        outFile << *it << endl;
    }
    outFile.close();

    cout << "Names saved successfully.\n";
}

void searchOne(const string& fileName, const string& nameToSearch)
{
    ifstream file(fileName.c_str());
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    string line;
    bool found = false;

    string lowerSearchName = toLowercase(nameToSearch);

    while (getline(file, line)) {
        string lowerLine = toLowercase(line);
        if (lowerLine.find(lowerSearchName) != string::npos) {
            cout << "Found: " << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Name not found.\n";
    }
}

void addSubjectAndGrade()
{
    string name, subject;
    double grade;
    char choice;

    cout << "Enter student's full name: ";
    getline(cin, name);

    do {
        cout << "Enter subject: ";
        getline(cin, subject);

        cout << "Enter student's grade (0-100): ";
        cin >> grade;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (grade < 0 || grade > 100) {
            cout << "Invalid grade. Must be between 0-100.\n";
            continue;
        }

        ofstream outFile("searchSubjectAndGrade.txt", ios::app);
        if (!outFile) {
            cout << "Error: Could not open file.\n";
            return;
        }

        outFile << name << ":" << subject << ":" << grade << endl;
        outFile.close();

        cout << "Subject and grade added successfully!\n";

        cout << "Do you want to add another subject for " << name << "? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice == 'y' || choice == 'Y');

    cout << "Returning to the main menu.\n";
}

void searchSubjectAndGrade(const string& fileName)
{
    string searchName;
    cout << "Enter student name to search: ";
    getline(cin, searchName);

    ifstream inFile(fileName.c_str());
    if (!inFile) {
        cout << "File not found.\n";
        return;
    }

    string line;
    bool found = false;

    string lowerSearchName = toLowercase(searchName);

    cout << "Subjects and grades for " << searchName << ":\n";

    while (getline(inFile, line)) {
        stringstream ss(line);
        string name, subject, gradeStr;

        getline(ss, name, ':');
        getline(ss, subject, ':');
        getline(ss, gradeStr);

        if (toLowercase(name) == lowerSearchName) {
            cout << "- " << subject << ": " << gradeStr << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No subjects or grades found for " << searchName << ".\n";
    }
}

void showTopStudent()
{
    ifstream file("searchSubjectAndGrade.txt");
    if (!file) {
        cout << "No grade data available.\n";
        return;
    }

    string line, topStudent;
    double highestGrade = -1;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, subjects, gradeStr;

        getline(ss, name, ':');
        getline(ss, subjects, ':');
        getline(ss, gradeStr);

        double grade = 0.0;
        stringstream gradeStream(gradeStr);
        if (gradeStream >> grade) {
            if (grade > highestGrade) {
                highestGrade = grade;
                topStudent = name;
            }
        }
    }

    if (highestGrade != -1) {
        cout << "Top student: " << topStudent
            << " with grade " << highestGrade << endl;
    }
    else {
        cout << "No valid grades found.\n";
    }
}
