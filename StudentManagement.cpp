#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;
    float cgpa;
};

void addStudent() {

    Student s;

    ofstream file;

    file.open("students.txt", ios::app);

    if (!file) {
        cout << "\nError Opening File!\n";
        return;
    }

    cout << "\nEnter Student ID: ";
    cin >> s.id;

    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    cout << "Enter Student Age: ";
    cin >> s.age;

    cin.ignore();

    cout << "Enter Student Course: ";
    getline(cin, s.course);

    cout << "Enter Student CGPA: ";
    cin >> s.cgpa;

    file << s.id << endl;
    file << s.name << endl;
    file << s.age << endl;
    file << s.course << endl;
    file << s.cgpa << endl;

    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents() {

    Student s;

    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\n========== STUDENT RECORDS ==========\n";

    while (file >> s.id) {

        file.ignore();

        getline(file, s.name);

        file >> s.age;

        file.ignore();

        getline(file, s.course);

        file >> s.cgpa;

        file.ignore();

        cout << "\nStudent ID     : " << s.id;
        cout << "\nStudent Name   : " << s.name;
        cout << "\nStudent Age    : " << s.age;
        cout << "\nStudent Course : " << s.course;
        cout << "\nStudent CGPA   : " << s.cgpa;
        cout << "\n-------------------------------------\n";
    }

    file.close();
}

void searchStudent() {

    Student s;

    int searchId;

    bool found = false;

    cout << "\nEnter Student ID to Search: ";
    cin >> searchId;

    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo Records Found!\n";
        return;
    }

    while (file >> s.id) {

        file.ignore();

        getline(file, s.name);

        file >> s.age;

        file.ignore();

        getline(file, s.course);

        file >> s.cgpa;

        file.ignore();

        if (s.id == searchId) {

            cout << "\nStudent Found Successfully!\n";

            cout << "\nStudent ID     : " << s.id;
            cout << "\nStudent Name   : " << s.name;
            cout << "\nStudent Age    : " << s.age;
            cout << "\nStudent Course : " << s.course;
            cout << "\nStudent CGPA   : " << s.cgpa << endl;

            found = true;

            break;
        }
    }

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }

    file.close();
}

void updateStudent() {

    Student s;

    int updateId;

    bool found = false;

    cout << "\nEnter Student ID to Update: ";
    cin >> updateId;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file) {
        cout << "\nNo Records Found!\n";
        return;
    }

    while (file >> s.id) {

        file.ignore();

        getline(file, s.name);

        file >> s.age;

        file.ignore();

        getline(file, s.course);

        file >> s.cgpa;

        file.ignore();

        if (s.id == updateId) {

            found = true;

            cout << "\nEnter New Student Name: ";
            getline(cin >> ws, s.name);

            cout << "Enter New Student Age: ";
            cin >> s.age;

            cout << "Enter New Student Course: ";
            getline(cin >> ws, s.course);

            cout << "Enter New Student CGPA: ";
            cin >> s.cgpa;
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
        cout << "\nStudent Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

void deleteStudent() {

    Student s;

    int deleteId;

    bool found = false;

    cout << "\nEnter Student ID to Delete: ";
    cin >> deleteId;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file) {
        cout << "\nNo Records Found!\n";
        return;
    }

    while (file >> s.id) {

        file.ignore();

        getline(file, s.name);

        file >> s.age;

        file.ignore();

        getline(file, s.course);

        file >> s.cgpa;

        file.ignore();

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
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main() {

    int choice;

    do {

        cout << "\n=====================================\n";
        cout << "     STUDENT MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";

        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "0. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
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
            cout << "\nProgram Closed Successfully.\n";
            break;

        default:
            cout << "\nInvalid Choice! Please Try Again.\n";
        }

    } while (choice != 0);

    return 0;
}