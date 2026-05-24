#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class BankAccount
{
private:
    int accountNumber;
    char name[50];
    float balance;

public:

    void createAccount()
    {
        cout << "\nEnter Account Number : ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Account Holder Name : ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance : ";
        cin >> balance;
    }

    void displayAccount()
    {
        cout << "\n----------------------------------";
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nAccount Holder : " << name;
        cout << "\nBalance        : " << balance;
        cout << "\n----------------------------------\n";
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    float getBalance()
    {
        return balance;
    }

    void deposit(float amount)
    {
        balance = balance + amount;
    }

    bool withdraw(float amount)
    {
        if (amount > balance)
        {
            return false;
        }

        balance = balance - amount;
        return true;
    }
};



// CREATE ACCOUNT
void createNewAccount()
{
    BankAccount account;

    ofstream file("bank.dat", ios::binary | ios::app);

    if (!file)
    {
        cout << "\nFile Error!\n";
        return;
    }

    account.createAccount();

    file.write((char*)&account, sizeof(account));

    file.close();

    cout << "\nAccount Created Successfully!\n";
}



// DISPLAY ALL ACCOUNTS
void displayAllAccounts()
{
    BankAccount account;

    ifstream file("bank.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    while (file.read((char*)&account, sizeof(account)))
    {
        account.displayAccount();
    }

    file.close();
}



// SEARCH ACCOUNT
void searchAccount()
{
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number to Search : ";
    cin >> accNo;

    BankAccount account;

    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.getAccountNumber() == accNo)
        {
            account.displayAccount();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}



// DEPOSIT MONEY
void depositMoney()
{
    int accNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number : ";
    cin >> accNo;

    cout << "Enter Amount to Deposit : ";
    cin >> amount;

    BankAccount account;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.getAccountNumber() == accNo)
        {
            account.deposit(amount);

            int position = -1 * sizeof(account);

            file.seekp(position, ios::cur);

            file.write((char*)&account, sizeof(account));

            cout << "\nAmount Deposited Successfully!\n";

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}



// WITHDRAW MONEY
void withdrawMoney()
{
    int accNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number : ";
    cin >> accNo;

    cout << "Enter Amount to Withdraw : ";
    cin >> amount;

    BankAccount account;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.getAccountNumber() == accNo)
        {
            bool success = account.withdraw(amount);

            if (success)
            {
                int position = -1 * sizeof(account);

                file.seekp(position, ios::cur);

                file.write((char*)&account, sizeof(account));

                cout << "\nPlease Collect Your Cash\n";
            }
            else
            {
                cout << "\nInsufficient Balance!\n";
            }

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}



// CHECK BALANCE
void checkBalance()
{
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number : ";
    cin >> accNo;

    BankAccount account;

    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.getAccountNumber() == accNo)
        {
            cout << "\nCurrent Balance : " << account.getBalance() << endl;

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}



// DELETE ACCOUNT
void deleteAccount()
{
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number to Delete : ";
    cin >> accNo;

    BankAccount account;

    ifstream file("bank.dat", ios::binary);
    ofstream tempFile("temp.dat", ios::binary);

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.getAccountNumber() == accNo)
        {
            found = true;
        }
        else
        {
            tempFile.write((char*)&account, sizeof(account));
        }
    }

    file.close();
    tempFile.close();

    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if (found)
    {
        cout << "\nAccount Deleted Successfully!\n";
    }
    else
    {
        cout << "\nAccount Not Found!\n";
    }
}



// MAIN FUNCTION
int main()
{
    int choice;

    do
    {
        cout << "\n========================================";
        cout << "\n      BANK MANAGEMENT SYSTEM";
        cout << "\n========================================";

        cout << "\n1. Create New Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Search Account";
        cout << "\n4. Deposit Money";
        cout << "\n5. Withdraw Money";
        cout << "\n6. Check Balance";
        cout << "\n7. Delete Account";
        cout << "\n8. Exit";

        cout << "\n\nEnter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewAccount();
            break;

        case 2:
            displayAllAccounts();
            break;

        case 3:
            searchAccount();
            break;

        case 4:
            depositMoney();
            break;

        case 5:
            withdrawMoney();
            break;

        case 6:
            checkBalance();
            break;

        case 7:
            deleteAccount();
            break;

        case 8:
            cout << "\nThank You For Using The System!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}