#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Book Class
class Book {
public:
    int bookID;
    string title;
    string author;
    bool isIssued;

    Book(int id, string t, string a) {
        bookID = id;
        title = t;
        author = a;
        isIssued = false;
    }
};

// Member Class
class Member {
public:
    int memberID;
    string name;

    Member(int id, string n) {
        memberID = id;
        name = n;
    }
};

// Library Class
class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:

    // Add Book
    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));

        cout << "Book Added Successfully!\n";
    }

    // Add Member
    void addMember() {
        int id;
        string name;

        cout << "Enter Member ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Member Name: ";
        getline(cin, name);

        members.push_back(Member(id, name));

        cout << "Member Added Successfully!\n";
    }

    // Display Books
    void displayBooks() {
        cout << "\n--- Book List ---\n";

        for (auto &book : books) {
            cout << "ID: " << book.bookID
                 << " | Title: " << book.title
                 << " | Author: " << book.author
                 << " | Status: "
                 << (book.isIssued ? "Issued" : "Available")
                 << endl;
        }
    }

    // Issue Book
    void issueBook() {
        int id;

        cout << "Enter Book ID to Issue: ";
        cin >> id;

        for (auto &book : books) {
            if (book.bookID == id) {
                if (!book.isIssued) {
                    book.isIssued = true;
                    cout << "Book Issued Successfully!\n";
                } else {
                    cout << "Book is already issued.\n";
                }
                return;
            }
        }

        cout << "Book not found.\n";
    }

    // Return Book
    void returnBook() {
        int id;

        cout << "Enter Book ID to Return: ";
        cin >> id;

        for (auto &book : books) {
            if (book.bookID == id) {
                if (book.isIssued) {
                    book.isIssued = false;
                    cout << "Book Returned Successfully!\n";
                } else {
                    cout << "Book was not issued.\n";
                }
                return;
            }
        }

        cout << "Book not found.\n";
    }

    // Search by Title
    void searchByTitle() {
        string title;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        for (auto &book : books) {
            if (book.title == title) {
                cout << "\nBook Found:\n";
                cout << "ID: " << book.bookID
                     << " | Author: " << book.author
                     << " | Status: "
                     << (book.isIssued ? "Issued" : "Available")
                     << endl;
                return;
            }
        }

        cout << "Book not found.\n";
    }

    // Search by Author
    void searchByAuthor() {
        string author;
        cin.ignore();

        cout << "Enter Author Name: ";
        getline(cin, author);

        bool found = false;

        for (auto &book : books) {
            if (book.author == author) {
                cout << "\nBook Found:\n";
                cout << "ID: " << book.bookID
                     << " | Title: " << book.title
                     << " | Status: "
                     << (book.isIssued ? "Issued" : "Available")
                     << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No books found by this author.\n";
        }
    }
};

// Main Function
int main() {
    Library lib;
    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Display Books\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Search Book by Title\n";
        cout << "7. Search Book by Author\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                lib.addBook();
                break;

            case 2:
                lib.addMember();
                break;

            case 3:
                lib.displayBooks();
                break;

            case 4:
                lib.issueBook();
                break;

            case 5:
                lib.returnBook();
                break;

            case 6:
                lib.searchByTitle();
                break;

            case 7:
                lib.searchByAuthor();
                break;

            case 8:
                cout << "Exiting Program...\n";
                break;

            default:
                cout << "Invalid Choice.\n";
        }

    } while (choice != 8);

    return 0;
}