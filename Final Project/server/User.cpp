#include "User.h"
#include <iostream>
#include <vector>
using namespace std;

#define SUPERUSER 0;
#define ADMIN 1;
#define NORMALUSER 2;

int compare(string _new_position, string user_position)
{
	if((_new_position=="Normaluser")&&(user_position!="Normaluser"))
		return -1;
	else if((user_position=="Superuser")&&(_new_position!="Superuser"))
		return -1;
	else
		return +1;
}

User::User(string _username, string _password, string _user_position)
{
	username=_username;
	password=_password;
	user_position=_user_position;
	groups_names.push_back(_username);
}
void User::promote(string _new_position)
{
	if(compare(_new_position, user_position)>0)
		user_position=_new_position;
	else
		cout<<"Promotion to lower position is not allowed "<<endl;
}
void User::demote(string _new_position)
{
	if(compare(_new_position, user_position)<0)
		user_position=_new_position;
	else
		cout<<"Demotion to Upper position is not allowed "<<endl;

}
bool group_is_not_repeated(string _group_name, vector<string> &groups_names)
{
	for(int i=0; i<groups_names.size(); i++)
	{
		if(groups_names[i]==_group_name)
			return 0;
	}
	return 1;
}

void User:: add_to_group(string _group_name)
{
	if(group_is_not_repeated(_group_name, groups_names))
		groups_names.push_back(_group_name);
	else
		cout<<"User already joined to group"<<endl;
}