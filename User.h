#pragma once
class User
{
	int id;
	bool is_admin;
public:
	User(void);
	User(int);
	~User();
	void SetId(int id);
	int GetId(void);
	bool IsAdmin(void);
	void MakeAdmin(void);
	void RevokeAdminRight(void);
};

