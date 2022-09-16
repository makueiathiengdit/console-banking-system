#include <iostream>
#include <iomanip>
#include <ctime>       

#include <fstream>
#include "Bank.h"
const std::string DEFAULT_NAME = "ABYEI BANK";
#pragma warning( disable : 4996 34 )
Bank::Bank()
{
    name = DEFAULT_NAME;
    ReadFromDB();
}

Bank::~Bank()
{
    std::cout << "==== YEARLY REVIEW =====\n";
    std::cout << "This year we had the following: \n";
    std::cout << "Number of accounts: " << TotalAccounts() << "\n";
    std::cout << "Amount in the bank: " << std::to_string(BankValue()) << "\n";
    WriteToDB();
    std::cout << "Bank closed\n";
}

Account Bank::FindById(int acc_no)
{
    return _accounts[acc_no];
}

void Bank::CreateAccount(std::string owner)
{
    int acc_no = GenerateAccountNumber();
    while (AccountExists(acc_no))
    {
        acc_no = GenerateAccountNumber();
    }

    Account acc(acc_no, owner);

    _accounts[acc_no] = acc;
    std::cout << "\nAccount created: " << acc_no << "\n";
    std::string msg = "Created account ";
    msg += std::to_string(acc_no);
    Log(msg);
   
}

void Bank::CreateTestAccount()
{
    int acc_no = GenerateAccountNumber();
    std::string owner = "Test";
    while (AccountExists(acc_no))
    {
        acc_no = GenerateAccountNumber();
    }

    Account acc(acc_no, owner);

    _accounts[acc_no] = acc;
    std::cout << "\nAccount created: " << acc_no << "\n";
    std::string msg = "Created account ";
    msg += std::to_string(acc_no);
    Log(msg);
    Deposit(acc_no, rand());
}

void Bank::DeleteAccount(int acc_no)
{
    if (AccountExists(acc_no)) {
        std::cout << "Deleting account no: " << acc_no;
        _accounts.erase(acc_no);
        std::cout << "....done\n";
        std::string msg = "Deleted account " + std::to_string(acc_no);
        Log(msg);
    }
    else
    {
        std::cout << "Account " << acc_no << " does not exist\n";
    }
}

void Bank::DeleteAll(void)
{
    char ans = 'N';
    std::cout << "\nAre you sure you want to delete all accounts? (Y/N): ";
    std::cin >> ans;
    if (ans == 'Y' || ans == 'y')
    {
        std::cout << "Deleting all accounts......";
        _accounts.clear();
        WriteToDB();
        std::cout << "done\n";
        Log("Deleted all accounts");
    }
    else
    {
        std::cout << "Delete operation cancelled\n";
    }
}

void Bank::Show(int acc_no)
{
   
    if (AccountExists(acc_no))
    {
        std::cout << "\nACCOUNT\t\tNAME\t\tBALANCE\n";
        std::cout << "---------------------------------------\n";
        std::cout << _accounts[acc_no].GetAccountNumber()<< "\t\t"
                  << _accounts[acc_no].GetName()<< "\t\t" 
                  << std::to_string(_accounts[acc_no].GetBalance()) << std::endl;
    }
    else
    {
        std::cout << "Account " << acc_no << " does not exist\n";
    }
}

void Bank::ShowAll(void)
{
    if (_accounts.empty())
        std::cout << "No accounts\n";
    else
    {
        std::cout << "SNO" << std::setw(10) << "ACCOUNT" << std::setw(15) << "NAME" << std::setw(10) << "BALANCE" << std::endl;
        std::cout << "--------------------------------------\n";
        int i = 1;
        for (auto& acc : _accounts)
        {
            if (!acc.second.IsBlocked())
            {
                std::cout
                    << std::setw(2)
                    << i << std::setw(10)
                    << acc.second.GetAccountNumber();
                std::cout << std::setw(15);
                std::cout << std::right
                    << acc.second.GetName()
                    << std::right;
                    std::cout<<std::setw(15)
                    << std::to_string(acc.second.GetBalance()) << "\n";
                i++;
            }
        }
    }
    
}

void Bank::BlockAccount(int acc_no)
{
    if (AccountExists(acc_no))
    {
        std::cout << "Blocking account no " << acc_no;
        _accounts[acc_no].Block();
        std::cout << "....done\n";
        std::string msg = "Blocked account " + acc_no;
        Log(msg);
    }
    else
        std::cout << "Account " << acc_no << " does not exist\n";
}

void Bank::UnblockAccount(int acc_no)
{
    if (AccountExists(acc_no))
    {
        std::cout << "Unblocking account no " << acc_no;
        _accounts[acc_no].Unblock();
        std::cout << "....done\n";
        Log("Unblocked account " + std::to_string(acc_no));
    }
    else
        std::cout << "Account " << acc_no << " does not exist\n";
}

bool Bank::Deposit(int acc_no, double amount)
{
    if (AccountExists(acc_no)) 
    {
        if (!_accounts[acc_no].IsBlocked())
        {
            if (_accounts[acc_no].Deposit(amount))
            {
                std::string msg = "Deposited ";
                msg += std::to_string(amount);
                msg += " to account " + std::to_string(acc_no);
                Log(msg);
                return true;
            }
        }
        else
        {
            std::cout << "CANNOT DEPOSIT\n account " << acc_no << "is blocked\n";
        }
    }
    else
    {
        std::cout << "Account " << acc_no << " does not exist\n";

    }
    return false;

}

bool Bank::Withdraw(int acc_no, double amount)
{
    if (AccountExists(acc_no))
    {
        if (!_accounts[acc_no].IsBlocked())
        {
            if (_accounts[acc_no].Withdraw(amount))
            {
                std::string msg = "Withdrew ";
                msg += std::to_string(amount);
                msg += " from " + std::to_string(acc_no);
                Log(msg);
                return true;
            }
        }
        else
        {
            std::cout << "CANNOT WITHDRAW\n account " << acc_no << " is blocked\n";  
        }
    }
    else
    {
        std::cout << "Account " << acc_no << " does not exist\n";
    }
    return false;
}

void Bank::Transfer(int from, int to, double amount)
{
    if(from != to)
        if (AccountExists(from) && AccountExists(to))
        {
            if (amount > 0)
            {
                if (Withdraw(from, amount) && Deposit(to, amount))
                {
                    std::cout << "\n";
                    std::cout << amount << " transfered from " << from << " to " << to << "\n";
                    std::string msg = "Transfered ";
                    msg += std::to_string(amount);
                    msg += "  from " + std::to_string( from);
                    msg += "  to " + std::to_string(to);
                    Log(msg);
                }
            }
            else
            {
                std::cout << "Cannot transfer amount less than 0\n";
            }
        }
        else
        {
            std::cout << "Either account " << from << " or " << to << " does not exist\n";
        }
}

void Bank::UpdateAccountName(int acc_no, std::string name)
{
    if (AccountExists(acc_no))
    {
        if (name != _accounts[acc_no].GetName())
        {
            std::string old_name = _accounts[acc_no].GetName();
            _accounts[acc_no].SetName(name);
            std::string msg = "Updated account: ";
            msg += std::to_string(acc_no);
            msg += " changed name from " + old_name + " to " + name;
            std::cout << msg;
            Log(msg);
        }

    }
    else 
    {
        std::cout << "Account no: " << acc_no << " does not exist\n";
    }
}

void Bank::Populate(int how_many)
{
    while (how_many)
    {
        CreateTestAccount();
        how_many--;
    } 
}

bool Bank::AccountExists(int acc_no)
{
    auto it = _accounts.find(acc_no);
    if (it == _accounts.end())
        return false;
    return true;
}

int Bank::GenerateAccountNumber()
{
    return rand() % 100000 + 100000;
}

std::string Bank::GetName(void)
{
    return name;
}

void Bank::SetName(std::string name)
{
    this->name = name;
}

void Bank::Log(std::string msg)
{
    std::ofstream log_file(this->log_file, std::ios::app);
    if (log_file.is_open()) 
    {
        time_t current_time;
        time(&current_time);       
        std::string c_msg = "";
        c_msg += std::asctime(localtime(&current_time));
        c_msg[c_msg.length() - 1] = ' ';
        log_file << c_msg;
        log_file << msg << "\n";
        log_file.close();
    }
    else
    {
        std::cout << "Error opening file: " << this->log_file << "\n";
    }
}

int Bank::TotalAccounts(void)
{
    return int(_accounts.size());
}

double Bank::BankValue(void)
{
    double total_amount = 0.0;
    for (auto& acc : _accounts)
        total_amount += acc.second.GetBalance();
    return total_amount;
}

void Bank::ReadFromDB(void)
{
    std::ifstream db(this->db_name, std::ios::in);
    if (db.is_open())
    {
        std::cout << "Reading from db...";
        std::string line;
        
        while (std::getline(db, line))
        {
            std::string acc_no, bal;
            std::size_t pos = line.find(' ');
            acc_no = line.substr(0,pos);
            bal = line.substr(pos +  4);
     
            Account acc(int(std::stoi(acc_no)), double (std::stod(bal)));
            acc.SetName("Test");
            _accounts[std::stoi(acc_no)] = acc;
        }
        db.close();
        std::cout << "Done\n";
    }
    else
    {
        std::cout << "Error opening file: " << this->db_name;
    }
}

void Bank::WriteToDB(void)
{
    std::ofstream db(db_name);
    if (db.is_open()) {
        std::cout << "Writing to db...";
        for (auto& acc : _accounts)
        {
            db << acc.second.GetAccountNumber() << "    " << acc.second.GetBalance() << "\n";
        }
        std::cout << "Done\n";
        db.close();
    }
}
