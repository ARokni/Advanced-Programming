#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#pragma once

using namespace std;

#ifndef _Group_H
#define _Group_H

class Group
{
public:
	Group(string _group_name, User *current_user);
// ************ Getter *******************
	string get_group_name() {return group_name;}
	vector<User*> get_member() {return group_member;}
// *********** Group Management **********
	void add_member(User* new_member);
	
private:
	string group_name;
	vector<User*> group_member;
};

#endif