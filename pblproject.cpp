#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <map>
#include <conio.h>

using namespace std;
#define MIN_BALANCE 500

class Account
{

    long accountNumber;
    string firstName;
    string lastName;
    float balance;
    static long NextAccountNumber;

public:
    Account() {}
    Account(string fname, string lname, float balance);
    long getAccNo() { return accountNumber; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    float getBalance() { return balance; }

    void Deposit(float amount);
    void Withdraw(float amount);
    static void setLastAccountNumber(long accountNumber);
    static long getLastAccountNumber();
    friend ofstream &operator<<(ofstream &ofs, Account &acc);
    friend ifstream &operator>>(ifstream &ifs, Account &acc);
    friend ostream &operator<<(ostream &os, Account &acc);
};
long Account::NextAccountNumber = 0;
class Bank
{
private:
    map<long, Account> accounts;

public:
    Bank();
    Account OpenAccount(string fname, string lname, float balance);
    Account BalanceEnquiry(long accountNumber);
    Account Deposit(long accountNumber, float amount);
    Account Withdraw(long accountNumber, float amount);
    void CloseAccount(long accountNumber);
    void ShowAllAccounts();
    ~Bank();
};

void fordelay(long int j)
{
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

int main()
{

    char starter[] = "Project Name : Banking System \n Group Members :\n 1.Ishwer Deore \n 2.Shreyas Kharde \n 3.Prathmesh Khot\n 4.Paras Khilosiya ";
    for (int i = 0; i < strlen(starter); i++)
    {
        printf("%c", starter[i]);
        fordelay(10000000);
    }
    getche();
    system("cls");
    Bank b;
    Account acc;

    int choice;
    string fname, lname;
    long accountNumber;
    float balance;
    float amount;
    do
    {
        cout << "_______________________________________________________________\n";
        cout << "\t\t**  Banking System  **" << endl;
        cout << "-----------------------------------------------------------------\n    ";
        cout << "\n\t\tSelect one option below ";
        cout << "\n\t\t1 Open an Account";
        cout << "\n\t\t2 Balance Enquiry";
        cout << "\n\t\t3 Deposit";
        cout << "\n\t\t4 Withdrawal";
        cout << "\n\t\t5 Close an Account";
        cout << "\n\t\t6 Show All Accounts";
        cout << "\n\t\t7 Quit\n";
        cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -";
        cout << "\n\tEnter your choice: ";
        cin >> choice;
        cout << "----------------------------------------------------------\n\n";
        switch (choice)
        {
        case 1:
            cout << "\tEnter First Name: ";
            cin >> fname;
            cout << "\tEnter Last Name: ";
            cin >> lname;
            cout << "\tEnter initial Balance: ";
            cin >> balance;
            try
            {
                if (balance < MIN_BALANCE)
                    throw balance;
                acc = b.OpenAccount(fname, lname, balance);
                cout << endl
                     << "\tCongratulation Account is Created" << endl;
                cout << acc;
            }
            catch (float amount)
            {
                cout << "\t you can't Create Account  \n\t As Minimum Balance In The Account Should Be Greater Than 500 " << endl;
            }

            getche();
            system("cls");
            break;
        case 2:
            cout << "\tEnter Account Number:";
            cin >> accountNumber;
            acc = b.BalanceEnquiry(accountNumber);
            cout << endl
                 << "\tYour Account Details" << endl;
            cout << acc;
            getche();
            system("cls");
            break;
        case 3:
            cout << "\tEnter Account Number:";
            cin >> accountNumber;
            cout << "\tEnter Balance:";
            cin >> amount;
            acc = b.Deposit(accountNumber, amount);
            cout << endl
                 << "\tAmount is Deposited Succesfully !" << endl;
            cout << acc;
            getche();
            system("cls");
            break;
        case 4:
            cout << "\tEnter Account Number:";
            cin >> accountNumber;
            cout << "\tEnter Balance:";
            cin >> amount;
            acc = b.Withdraw(accountNumber, amount);

            cout << acc;
            getche();
            system("cls");
            break;
        case 5:
            cout << "\tEnter Account Number:";
            cin >> accountNumber;
            b.CloseAccount(accountNumber);
            cout << endl
                 << "\tAccount is Closed Successfully ! " << endl;
            cout << acc;
            getche();
            system("cls");
            break;
        case 6:
            b.ShowAllAccounts();
            getche();
            system("cls");
            break;
        case 7:
            break;
        default:
            cout << "\n\tEnter corret choice";
            exit(0);
        }
    } while (choice != 7);

    return 0;
}
Account::Account(string fname, string lname, float balance)
{
    NextAccountNumber++;
    accountNumber = NextAccountNumber;
    firstName = fname;
    lastName = lname;
    this->balance = balance;
}
void Account::Deposit(float amount)
{
    balance += amount;
}
void Account::Withdraw(float amount)
{
    try
    {
        if (balance - amount < MIN_BALANCE)
            throw amount;
        balance -= amount;
        cout << endl
             << "\tAmount Withdrawn Succesfully !" << endl;
    }
    catch (float amount)
    {
        cout << "\t You Can't Withdraw Ammount \n\t As Minimum Balance In The Account Should Be Greater Than 500 " << endl;
    }
}
void Account::setLastAccountNumber(long accountNumber)
{
    NextAccountNumber = accountNumber;
}
long Account::getLastAccountNumber()
{
    return NextAccountNumber;
}
ofstream &operator<<(ofstream &ofs, Account &acc)
{
    ofs << acc.accountNumber << endl;
    ofs << acc.firstName << endl;
    ofs << acc.lastName << endl;
    ofs << acc.balance << endl;
    return ofs;
}
ifstream &operator>>(ifstream &ifs, Account &acc)
{
    ifs >> acc.accountNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.balance;
    return ifs;
}
ostream &operator<<(ostream &os, Account &acc)
{
    os << "\tFirst Name: " << acc.getFirstName() << endl;
    os << "\tLast Name: " << acc.getLastName() << endl;
    os << "\tAccount Number: " << acc.getAccNo() << endl;
    os << "\tBalance: " << acc.getBalance() << endl;
    return os;
}
Bank::Bank()
{

    Account account;
    ifstream infile;
    infile.open("Bank.data");
    if (!infile)
    {
        cout << "Error in Opening! File Not Found!!" << endl;
        return;
    }
    while (!infile.eof())
    {
        infile >> account;
        accounts.insert(pair<long, Account>(account.getAccNo(), account));
    }
    Account::setLastAccountNumber(account.getAccNo());

    infile.close();
}
Account Bank::OpenAccount(string fname, string lname, float balance)
{
    ofstream file;
    Account account(fname, lname, balance);
    accounts.insert(pair<long, Account>(account.getAccNo(), account));

    file.open("Bank.data", ios::trunc);

    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        file << itr->second;
    }
    file.close();
    return account;
}
Account Bank::BalanceEnquiry(long accountNumber)

{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    return itr->second;
}
Account Bank::Deposit(long accountNumber, float amount)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Deposit(amount);
    return itr->second;
}
Account Bank::Withdraw(long accountNumber, float amount)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Withdraw(amount);
    return itr->second;
}

void Bank::CloseAccount(long accountNumber)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    cout << "Account Deleted" << itr->second;
    accounts.erase(accountNumber);
}

void Bank::ShowAllAccounts()
{
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        cout << "Account " << itr->first << endl
             << itr->second << endl;
    }
}

Bank::~Bank()
{
    ofstream outfile;
    outfile.open("Bank.data", ios::trunc);
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
}