#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <limits>

using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string course;
    float cgpa;
};

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void ignoreLine(ifstream &file) {
    file.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isDuplicateId(int id) {

    Student s;

    ifstream file("students.txt");

    if (!file) {
        return false;
    }

    while (file >> s.id) {

        ignoreLine(file);

        getline(file, s.name);

        file >> s.age;
        ignoreLine(file);

        getline(file, s.course);

        file >> s.cgpa;
        ignoreLine(file);

        if (s.id == id) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void addStudent() {

    Student s;

    ofstream file("students.txt", ios::app);

    if (!file) {
        cout << "\nUnable to open file!\n";
        return;
    }

    cout << "\nEnter Student ID: ";

    while (!(cin >> s.id) || s.id <= 0 || isDuplicateId(s.id)) {

        if (cin.fail()) {
            cout << "Invalid input! Enter a valid positive number: ";
            clearInput();
        }
        else {
            cout << "ID already exists! Enter another ID: ";
            clearInput();
        }
    }

    clearInput();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";

    while (!(cin >> s.age) || s.age <= 0 || s.age > 100) {
        cout << "Invalid age! Enter again: ";
        clearInput();
    }

    clearInput();

    cout << "Enter Course: ";
    getline(cin, s.course);

    cout << "Enter CGPA: ";

    while (!(cin >> s.cgpa) || s.cgpa < 0 || s.cgpa > 10) {
        cout << "Invalid CGPA! Enter between 0 and 10: ";
        clearInput();
    }

    clearInput();

    file << s.id << endl;
    file << s.name << endl;
    file << s.age << endl;
    file << s.course << endl;
    file << s.cgpa << endl;

    file.close();

    cout << "\nStudent added successfully!\n";
}

void displayAllStudents() {

    Student s;

    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo records found.\n";
        return;
    }

    cout << "\n========== Student Records ==========\n";

    while (file >> s.id) {

        ignoreLine(file);

        getline(file, s.name);

        file >> s.age;
        ignoreLine(file);

        getline(file, s.course);

        file >> s.cgpa;
        ignoreLine(file);

        cout << "\nID      : " << s.id;
        cout << "\nName    : " << s.name;
        cout << "\nAge     : " << s.age;
        cout << "\nCourse  : " << s.course;
        cout << "\nCGPA    : " << s.cgpa;
        cout << "\n-------------------------------------\n";
    }

    file.close();
}

void searchStudent() {

    Student s;

    int searchId;
    bool found = false;

    cout << "\nEnter Student ID to Search: ";

    while (!(cin >> searchId)) {
        cout << "Invalid input! Enter valid ID: ";
        clearInput();
    }

    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo records found.\n";
        return;
    }

    while (file >> s.id) {

        ignoreLine(file);

        getline(file, s.name);

        file >> s.age;
        ignoreLine(file);

        getline(file, s.course);

        file >> s.cgpa;
        ignoreLine(file);

        if (s.id == searchId) {

            found = true;

            cout << "\nStudent Found!\n";

            cout << "\nID      : " << s.id;
            cout << "\nName    : " << s.name;
            cout << "\nAge     : " << s.age;
            cout << "\nCourse  : " << s.course;
            cout << "\nCGPA    : " << s.cgpa << endl;

            break;
        }
    }

    if (!found) {
        cout << "\nStudent not found.\n";
    }

    file.close();
}

void updateStudent() {

    Student s;

    int updateId;
    bool found = false;

    cout << "\nEnter Student ID to Update: ";

    while (!(cin >> updateId)) {
        cout << "Invalid input! Enter valid ID: ";
        clearInput();
    }

    clearInput();

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file) {
        cout << "\nNo records found.\n";
        return;
    }

    while (file >> s.id) {

        ignoreLine(file);

        getline(file, s.name);

        file >> s.age;
        ignoreLine(file);

        getline(file, s.course);

        file >> s.cgpa;
        ignoreLine(file);

        if (s.id == updateId) {

            found = true;

            cout << "\nEnter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Age: ";

            while (!(cin >> s.age) || s.age <= 0 || s.age > 100) {
                cout << "Invalid age! Enter again: ";
                clearInput();
            }

            clearInput();

            cout << "Enter New Course: ";
            getline(cin, s.course);

            cout << "Enter New CGPA: ";

            while (!(cin >> s.cgpa) || s.cgpa < 0 || s.cgpa > 10) {
                cout << "Invalid CGPA! Enter again: ";
                clearInput();
            }

            clearInput();
        }

        temp << s.id << endl;
        temp << s.name << endl;
        temp << s.age << endl;
        temp << s.course << endl;
        temp << s.cgpa << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent updated successfully!\n";
    else
        cout << "\nStudent not found.\n";
}

void deleteStudent() {

    Student s;

    int deleteId;
    bool found = false;

    cout << "\nEnter Student ID to Delete: ";

    while (!(cin >> deleteId)) {
        cout << "Invalid input! Enter valid ID: ";
        clearInput();
    }

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file) {
        cout << "\nNo records found.\n";
        return;
    }

    while (file >> s.id) {

        ignoreLine(file);

        getline(file, s.name);

        file >> s.age;
        ignoreLine(file);

        getline(file, s.course);

        file >> s.cgpa;
        ignoreLine(file);

        if (s.id == deleteId) {
            found = true;
        }
        else {

            temp << s.id << endl;
            temp << s.name << endl;
            temp << s.age << endl;
            temp << s.course << endl;
            temp << s.cgpa << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent deleted successfully!\n";
    else
        cout << "\nStudent not found.\n";
}

int main() {

    int choice;

    do {

        cout << "\n====== Student Management System ======\n";

        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "0. Exit\n";

        cout << "Enter Your Choice: ";

        while (!(cin >> choice)) {
            cout << "Invalid input! Enter again: ";
            clearInput();
        }

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayAllStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 0:
                cout << "\nGoodbye!\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}