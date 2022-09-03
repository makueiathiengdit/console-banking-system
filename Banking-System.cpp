/*
* Project Name: Console Banking System
* Author Name: Awet Thon
* Date       : 28-08-2022
*/

#include <iostream>
#include "Bank.h"

enum COMMANDS
{
    CREATE,
    SHOW,
    SHOW_ALL,
    DEPOSIT,
    WITHDRAW,
    DELETE,
    DELETE_ALL,
    BLOCK,
    UNBLOCK,
    TRANSFER,
    QUIT
};

int InputAccountNumber(void);
std::string InputUserName(void);
double InputAmount(void);

int main()
{
    std::cout << "\n========= C O N S O L E   B A N K I N G   S Y S T E M ===========\n";
    Bank bank;
    int command = SHOW_ALL;
    while (true) {
        std::cout << "\n\n\t*** WELCOME TO " << bank.GetName() << " ***\n";
        std::cout << "\n========== COMMANDS MENU ==========\n";
        std::cout << "0\tCREATE\n";
        std::cout << "1\tSHOW\n";
        std::cout << "2\tSHOW_ALL\n";
        std::cout << "3\tDEPOSIT\n";
        std::cout << "4\tWITHDRAW\n";
        std::cout << "5\tDELETE\n";
        std::cout << "6\tDELETE_ALL\n";
        std::cout << "7\tBLOCK\n";
        std::cout << "8\tUNBLOCK\n";
        std::cout << "9\tTRANSFER\n";
        std::cout << "10\tQUIT\n";
        std::cout << "\nENTER COMMAND: ";
        std::cin >> command;
        if (command == QUIT)
            break;
        switch (command)
        {
        case CREATE:
        {
            /*
                bank.Populate(10);
            */
            std::string owner = InputUserName();
            bank.CreateAccount(owner);
            break;
        }
        case SHOW:
        {
            std::cout << "\nSHOW ACCOUNT\n";
            int acc_no = InputAccountNumber();
            bank.Show(acc_no);
            break;
        }
        case SHOW_ALL:
            bank.ShowAll();
            break;

        case DEPOSIT:
        {
            std::cout << "\nDEPOSIT\n";         
            int acc_no = InputAccountNumber();
            double amount = InputAmount();      
            bank.Deposit(acc_no, amount);
            break;
        }
        case WITHDRAW:
        {
            std::cout << "\nWITHDRAW\n";
            int acc_no = InputAccountNumber();
            double amount = InputAmount();
            bank.Withdraw(acc_no, amount);
            break;
        }
        case DELETE:
        {
            std::cout << "\nDELETE\n";
            int acc_no = InputAccountNumber();
            bank.DeleteAccount(acc_no);
            break; 
        }
        case DELETE_ALL:
            bank.DeleteAll();
            break;
        
        case BLOCK:
        {
            std::cout << "\nBLOCK\n";
            int acc_no = InputAccountNumber();
            bank.BlockAccount(acc_no);
            break;
        }
        case UNBLOCK:
        {
            std::cout << "\nUNBLOCK\n";
            int acc_no = InputAccountNumber();
            bank.UnblockAccount(acc_no);
            break;
        }
        case TRANSFER:
        {
            int from = 0, to = 0;
            double amount = 0.0;
            std::cout << "Enter sender account no: ";
            from = InputAccountNumber();
            std::cout << "Enter recipient account no: ";
            to = InputAccountNumber();
            amount = InputAmount();
            bank.Transfer(from, to, amount);
            break;
        }
        default:
            break;
        }
    }
    
    return 0;
}

int InputAccountNumber(void)
{
    int acc_no = 0;
    while (acc_no <=0)
    {
        std::cout << "Enter account number: ";
        std::cin >> acc_no;
    }
    return acc_no;
}

std::string InputUserName(void)
{
    std::string name = "";
    while (name == "")
    {
        std::cout << "Enter owner name: ";
        std::getline(std::cin, name);
    }
    return name;
}

double InputAmount(void)
{
    double amount = 0.0;
    while (amount<=0)
    {
        std::cout << "Enter amount : ";
        std::cin >> amount;
    }
    return amount;
}
