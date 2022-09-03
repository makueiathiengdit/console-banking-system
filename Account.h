#pragma once
class Account
{
private:
	int account_number;
	double balance;
	bool is_blocked;
public:
	Account(void);

	Account(int);
	Account(int, double);
	~Account();
	void SetAccountNumber(int number);
	int GetAccountNumber(void);
	void SetBalance(double bal);
	double GetBalance(void);
	void Deposit(double amount);
	void Withdraw(double amount);
	void PrintDetails(void);
	bool IsBlocked(void);
	void Block(void);
	void Unblock(void);
};

