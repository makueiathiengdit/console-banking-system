#include <iostream>
#include <string>
#include "Account.h"


Account::Account(void)
{
    account_number = 0;
    balance = 0.0;
    is_blocked = false;
}

Account::Account(int number)
{
    account_number = number;
    balance = 0.0;
    is_blocked = false;
}

Account::Account(int acc, double bal)
{
    account_number = acc;
    balance = bal;
    is_blocked = false;
}

Account::~Account()
{
}

void Account::SetAccountNumber(int number)
{
    account_number = number;
}

int Account::GetAccountNumber(void)
{
    return account_number;
}

void Account::SetBalance(double bal)
{
    balance = bal;
}

double Account::GetBalance(void)
{
    return balance;
}

void Account::Deposit(double amount)
{
    
    if (amount > 0) {
        balance += amount;
        std::cout << "\n" << amount << " deposited to account no " << account_number << "\n";
        this->PrintDetails();
    }
    else
    {
        throw "Error: amount cannot be negative";
    }
 
}

void Account::Withdraw(double amount)
{
    if (amount > 0 && amount < balance) {
        balance -= amount;
        std::cout << "\n" << amount << " withdrawn from account no " << account_number << "\n";
        this->PrintDetails();
    }
    else
    {
        throw ("Error: amount cannot be negative");
    } 
}

void Account::PrintDetails(void)
{
    std::cout << "\n";
    std::cout << "ACC\tBALANCE\n";
    std::cout << account_number << "\t" << balance << "\n";
}

bool Account::IsBlocked(void)
{
    return is_blocked;
}

void Account::Block(void)
{
    is_blocked = true;
}

void Account::Unblock(void)
{
    is_blocked = false;
}
