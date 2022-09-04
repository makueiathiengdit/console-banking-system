#include "User.h"

User::User(void)
{
    id = 0;
    is_admin = false;
}

User::User(int id)
{
    this->id = id;
    is_admin = false;
}

User::~User()
{
}

void User::SetId(int id)
{
    this->id = id;
}

int User::GetId(void)
{
    return id;
}

bool User::IsAdmin(void)
{
    return is_admin;
}

void User::MakeAdmin(void)
{
    is_admin = true;
}

void User::RevokeAdminRight(void)
{
    is_admin = false;
}
