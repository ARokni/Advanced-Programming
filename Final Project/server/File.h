#include <iostream>
#include <string>
#include <vector>
#pragma once

using namespace std;

#ifndef _File_H
#define _File_H

struct User_license {
		string username;
		string license;
	};
	struct Group_license {
		string group_name;
		string license;
	};


class File
{
public:
	File(string _owner_name,string _file_name, string _file_contents, double _file_size);
//************** Getter ******************
	string get_file_name() {return file_name;}
	string get_file_contents() {return file_contents;}	
	double get_file_size() {return file_size;}
	string get_user_name() {return user_license.username;}
	string get_license() {return user_license.license;}
	string get_group_name() {return group_license.group_name;}
	string get_gp_license() {return group_license.license;}
	void file_change_mode(string add_remove,string license,string  group_user );
	void file_change_owner(string _username) {user_license.username=_username;}
	void file_change_group(string _group_name) {group_license.group_name=_group_name;}

	
private:
	string file_name;
	double file_size;
	string file_contents;
	//********** License ***********
    User_license user_license;
    Group_license group_license;
};

#endif