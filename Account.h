#pragma once
#include <string>
class Account
{
private:
	int account_number;
	std::string name;
	double balance;
	bool is_blocked = false;
public:
	Account(void);
	Account(int, double);
	Account(int,std::string);
	Account(int acc_no, std::string owner, double bal);
	~Account();
	void SetAccountNumber(int number);
	int GetAccountNumber(void);
	void SetBalance(double bal);
	double GetBalance(void);
	void SetName(std::string name);
	std::string GetName(void);
	bool Deposit(double amount);
	bool Withdraw(double amount);
	void PrintDetails(void);
	bool IsBlocked(void);
	void Block(void);
	void Unblock(void);
};

