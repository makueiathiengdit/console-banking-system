#include <iostream>
#include "Bank.h"
const std::string DEFAULT_NAME = "ABYEI BANK";

Bank::Bank()
{
    name = DEFAULT_NAME;
}

Bank::~Bank()
{
    std::cout << "Bank closed\n";
}

Account Bank::FindById(int acc_no)
{
    return _accounts[acc_no];
}

void Bank::CreateAccount()
{
    int acc_no = GenerateAccountNumber();
    while (AccountExists(acc_no))
    {
        acc_no = GenerateAccountNumber();
    }
    Account acc(acc_no);

    /*
        acc.SetBalance(rand());
    */
    _accounts[acc_no] = acc;
    std::cout << "\nAccount created: " << acc_no << "\n";
}

void Bank::DeleteAccount(int acc_no)
{
    if (AccountExists(acc_no)) {
        std::cout << "Deleting account no: " << acc_no;
        _accounts.erase(acc_no);
        std::cout << "....done\n";
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
        std::cout << "done\n";
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
        std::cout << "\nACC\tBALANCE\n";
        std::cout << _accounts[acc_no].GetAccountNumber() << "\t" << _accounts[acc_no].GetBalance() << "\n";
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
        std::cout << "\nSNO\tACCOUNT\t\tBALANCE\n";
        std::cout << "-------------------------------\n";
        int i = 1;
        for (auto& acc : _accounts)
        {
            if (!acc.second.IsBlocked())
            {
                std::cout << i << "\t" << acc.second.GetAccountNumber() << "\t\t" << acc.second.GetBalance() << "\n";
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
    }
    else
        std::cout << "Account " << acc_no << " does not exist\n";
}

void Bank::Deposit(int acc_no, double amount)
{
    if (AccountExists(acc_no)) 
    {
        if (!_accounts[acc_no].IsBlocked())
            _accounts[acc_no].Deposit(amount);
        else
            std::cout << "CANNOT DEPOSIT\n account "<<acc_no << "is blocked\n";
    }
    else
        std::cout << "Account " << acc_no << " does not exist\n";

}

void Bank::Withdraw(int acc_no, double amount)
{
    if (AccountExists(acc_no))
    {
        if (!_accounts[acc_no].IsBlocked())
            _accounts[acc_no].Withdraw(amount);
        else
            std::cout << "CANNOT WITHDRAW\n account " <<acc_no << " is blocked\n";
    }else
        std::cout << "Account " << acc_no << " does not exist\n";

}

void Bank::Transfer(int from, int to, double amount)
{
    if (AccountExists(from) && AccountExists(to))
    {
        if (amount > 0)
        {
            Withdraw(from, amount);
            Deposit(to, amount);
            std::cout << "\n";
            std::cout << amount << " transfered from " << from << " to " << to << "\n";
        }
        else
        {
            std::cout << "Cannot transfer amount less than 0\n";
        }
    }
    else
    {
        std::cout << "Either account " << from << " or " << to << "does not exist\n";
    }
}

void Bank::Populate(int how_many)
{
    while (how_many)
    {
        CreateAccount();
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
