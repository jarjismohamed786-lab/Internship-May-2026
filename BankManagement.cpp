#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    float balance;

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Account Holder Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount() {
        cout << "\n---------------------------";
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nAccount Holder : " << name;
        cout << "\nBalance         : " << balance;
        cout << "\n---------------------------\n";
    }

    int getAccountNumber() {
        return accountNumber;
    }

    void depositMoney(float amount) {
        balance = balance + amount;
    }

    void withdrawMoney(float amount) {
        if (amount > balance) {
            cout << "\nInsufficient Balance!\n";
        } else {
            balance = balance - amount;
            cout << "\nWithdrawal Successful!\n";
        }
    }

    float getBalance() {
        return balance;
    }
};

void addAccount() {
    BankAccount account;

    ofstream file("bank.dat", ios::binary | ios::app);

    if (!file) {
        cout << "\nFile Error!\n";
        return;
    }

    account.createAccount();

    file.write((char*)&account, sizeof(account));

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAllAccounts() {
    BankAccount account;

    ifstream file("bank.dat", ios::binary);

    if (!file) {
        cout << "\nFile Not Found!\n";
        return;
    }

    while (file.read((char*)&account, sizeof(account))) {
        account.displayAccount();
    }

    file.close();
}

void searchAccount() {
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number to Search: ";
    cin >> accNo;

    BankAccount account;

    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&account, sizeof(account))) {
        if (account.getAccountNumber() == accNo) {
            account.displayAccount();
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nAccount Not Found!\n";
    }
}

void depositAmount() {
    int accNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    BankAccount account;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&account, sizeof(account))) {
        if (account.getAccountNumber() == accNo) {

            account.depositMoney(amount);

            int position = -1 * sizeof(account);

            file.seekp(position, ios::cur);

            file.write((char*)&account, sizeof(account));

            cout << "\nAmount Deposited Successfully!\n";

            found = true;

            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nAccount Not Found!\n";
    }
}

void withdrawAmount() {
    int accNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    BankAccount account;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&account, sizeof(account))) {

        if (account.getAccountNumber() == accNo) {

            if (amount > account.getBalance()) {
                cout << "\nInsufficient Balance!\n";
            } else {

                account.withdrawMoney(amount);

                int position = -1 * sizeof(account);

                file.seekp(position, ios::cur);

                file.write((char*)&account, sizeof(account));

                cout << "\nPlease Collect Your Cash\n";
            }

            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nAccount Not Found!\n";
    }
}

int main() {

    int choice;

    do {

        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";

        cout << "\n1. Create Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Search Account";
        cout << "\n4. Deposit Amount";
        cout << "\n5. Withdraw Amount";
        cout << "\n6. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addAccount();
            break;

        case 2:
            displayAllAccounts();
            break;

        case 3:
            searchAccount();
            break;

        case 4:
            depositAmount();
            break;

        case 5:
            withdrawAmount();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}