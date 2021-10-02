#include <iostream>
#include <string>
#include <vector>
#include "File.h"
#include "Ap_Exception.h"
#pragma once

using namespace std;

#ifndef _Folder_H
#define _Folder_H



class Folder
{
public:
//***************  Constructor  *******************
	Folder(string _current_folder_name ,string _current_directory, string _owner_name);
	Folder();
//************* File management ********************   
 	Folder* next_folder(string _folder_name);
	void make_directory(string _folder_name, string _owner_name);
	void make_file(string _username,string _real_file_name,string _file_contents, double _file_size);
	void delete_file_from_folder(string _file_name);
	void remove(string folder_file_name);
	void remove_folder();
	double get_file_size(string file_name);
//************  utility  ******************
	int find_folder(string _folder_name);
//************* PHASE II ******************
	int find_File(string _file_name);
//************* Getter ********************
	string get_folder_name() {return current_folder_name;}
	vector<Folder*> get_folder() {return folder;}
	vector<File*> get_file() {return file;}
	string get_current_directory() {return current_directory;}
	File* find_file(string _file_name);
	string get_user_name() {return user_license.username;}
	string get_license() {return user_license.license;}
	string get_group_name() {return group_license.group_name;}
	string get_gp_license() {return group_license.license;}
//************** PHASE II ********************
	string get_prev_directory(){return prev_directory;}
	string get_prev_folder_name() {return prev_folder_name;}

//*************** Accessibility **************	
	string get_owner_user_name(string folder_file_name);
	string get_owner_license(string folder_file_name);
	string get_owner_group_name(string folder_file_name);
	string get_group_license(string folder_file_name);
	void change_mode(string group_user, string add_remove, string license,string current_user_name, string folder_file_name);
	void folder_change_mode(string add_remove,string license,string  group_user );
	void change_owner(string _username, string folder_file_name, string current_user_name);
	void folder_change_owner(string _username) {user_license.username=_username;}
	void change_group(string group_name,string folder_file_name,string current_user_name);
	void folder_change_group(string _group_name) {group_license.group_name=_group_name;}



	
private:
	vector<File*> file;
    vector<Folder*>folder;
    string directory;
    string current_folder_name;
    Folder *current_folder;
    string current_directory;
    //************ PHASE II ********
    string prev_directory;
    string prev_folder_name;
    //********** License ***********
    User_license user_license;
    Group_license group_license;
    

};

#endif


