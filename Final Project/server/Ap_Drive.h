#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Group.h"
#include "Folder.h"
#include "Ap_Exception.h"
#include <iostream>
#include<string>
#include<vector>
#include "../utils/request.hpp"

using namespace std;

#ifndef _Ap_Drive_H
#define _Ap_Drive_H

class Ap_Drive
{
public:
	Ap_Drive();
	int find_user(string _username);
	int find_group(string _group_name);
// **************** Getter ***************************
User* get_current_user() {return current_user;}	
Folder* get_current_folder() {return current_folder;}
vector<User*> get_users() {return user;}
// ************** Setter *****************************
//************** phase II ****************************
void set_selected_file(string _file_content) {selected_file=_file_content;}


// **************** User management *******************
	void add_user(string _username, string _password);
	void login(string _username, string _password);
	void logout() {current_user=NULL;}
	void add_group(string _group_name);
	void add_to_group(string _group_name, string _username);
// **************** File management *******************
	void go_to(vector<string> &path,string _directory);
	void go_to_root() {current_folder=root;}
	void upload(string real_file_name,string  path);
	void download(string _path, string _output_name);
	void make_directory(string _directory_name);
	void copy(string _source_path, string _destination_path);
	void move(string source_path,string destination_path);
	void remove(string _path);
	void print_directory() {cout<<current_folder->get_current_directory()<<endl;}
	void change_directory(string _path);
	double file_size(string _path);
	void get_license(string &license, string _path);
	void change_mode(vector<string>command);
	void change_owner(string _username,string path);
	void change_group(string group_name,string path);
// ************** Management commands **********
	void promote(string user_name, string new_position);
	void demote(string user_name, string new_position);
	void userlist();
	void show_storage() {cout<<storage<<endl;}
	void remove_server();
// **************** Phase II *************	
	void do_action(Request *request);
	string show_file() {return selected_file;}
// *************** Setter II **************	
	void set_copy_move_flag(int _flag) {copy_move_flag=_flag;}
	void set_copy_move_source(string _copy_move_source) {copy_move_source=_copy_move_source;}
	void set_details(vector<string>_details) {details = _details;}
// *************** Getter II **************
	int get_copy_move_flag() {return copy_move_flag;}
	string get_copy_move_source() {return copy_move_source;}
	vector<string> get_details() {return details;}

	
private:
// ************ User fileds ****************	
	vector <User*> user;
	User *current_user;
// *********** Group fields ****************
	vector<string> group;
// ************ Folder fields *************
	Folder *current_folder;
	Folder *root;
	double storage;
// ************ Phase II fields *************
	string selected_file;
	string copy_move_source;
	int copy_move_flag;
	vector<string>details;


};

#endif
