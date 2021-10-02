#include <iostream>
#include <string>
#include <vector>
#pragma once

using namespace std;

#ifndef _User_H
#define _User_H

class User
{
	
public:
		User(string _username, string _password, string _user_position);
//***************** Getters ****************
		string get_username(){return username;}
		string get_password(){return password;}
		string get_position() {return user_position;}
		vector<string> get_groups_names(){return groups_names;}
// **************  Management Orders **************
		void promote(string _new_position);
		void demote(string _new_position);
// ************* Groups And Files *********
		void add_to_group(string _group_name);

private:
	string username, password;
	string user_position;
	vector<string> groups_names;
	
	
};

#endif