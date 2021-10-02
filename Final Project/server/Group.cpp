#include "Group.h"
#include <iostream>
#include <vector>
using namespace std;

bool not_repeated_member(User *new_member ,vector<User*> &group_member)
{
	for(int i=0; i<group_member.size(); i++)
	{
		if(group_member[i]->get_username()==new_member->get_username())
			return 0;
	}
	return 1;
}


Group::Group(string _group_name, User *current_user)
{
	group_name=_group_name;
	group_member.push_back(current_user);
}
void Group::add_member(User* new_member)
{
	if(not_repeated_member(new_member, group_member))
		group_member.push_back(new_member);
}