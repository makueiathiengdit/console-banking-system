#pragma once
#include <string>
#include <unordered_map>
#include "Account.h"
class Bank
{
	std::unordered_map<int, Account>_accounts;
	std::string name;
	std::string log_file = "logs.txt";
	std::string db_name = "db.txt";
public:
	Bank();
	~Bank();
	Account FindById(int);
	void CreateAccount(std::string owner);
	void CreateTestAccount();

	void DeleteAccount(int acc_no);
	void DeleteAll(void);
	void Show(int acc_no);
	void ShowAll(void);
	void BlockAccount(int acc_no);
	void UnblockAccount(int acc_no);
	bool Deposit(int acc_no, double amount);
	bool Withdraw(int acc_no, double amount);
	void Transfer(int from, int to, double amount);
	void UpdateAccountName(int acc_no, std::string name);
	void Populate(int how_many);
	bool AccountExists(int acc_no);
	int GenerateAccountNumber();
	std::string GetName(void);
	void SetName(std::string name);
	void Log(std::string msg);
	int TotalAccounts(void);
	double BankValue(void);
	void ReadFromDB(void);
	void WriteToDB(void);
};

