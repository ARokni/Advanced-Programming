#include "Folder.h"
#include <iostream>
#include <vector>
#include<string>
using namespace std;


string trim_prev_name(string _current_directory)
{
	int length=_current_directory.size();
	string prev_name="";
	int last_slash_pos=0;
	for(int i=length;i>0;i--)
	{
		last_slash_pos=i;
		if(_current_directory[i]=='/')
			break; 
	}
	prev_name=_current_directory.substr(last_slash_pos,length-last_slash_pos);
	return prev_name;
}



Folder:: Folder(string _current_folder_name ,string _current_directory, string _owner_name) 
{
	
	prev_directory = _current_directory;
	prev_folder_name = trim_prev_name(_current_directory);

	current_folder_name=_current_folder_name; 
	current_directory= _current_directory+"/"+_current_folder_name;

	user_license.username=_owner_name;
	user_license.license="RW";
	group_license.group_name=_owner_name;
	group_license.license="RW";
}
Folder::Folder() 
{
	current_directory=""; 
	current_folder_name="";
	prev_directory="";
	prev_folder_name="";
}

int Folder::find_folder(string _folder_name)
{
	for(int i=0; i<folder.size(); i++)
	{
		if(_folder_name==folder[i]->current_folder_name)
			return i;
	}
	throw Find_folder_Exception();
}

void Folder::make_directory(string _folder_name, string _owner_name)
{
	
	Folder *new_folder= new Folder(_folder_name, current_directory, _owner_name);
	folder.push_back(new_folder);
}
Folder* Folder::next_folder(string _folder_name)
{
	int folder_index;
	try
	{
		folder_index=find_folder(_folder_name);
	}catch(Find_folder_Exception()) {throw Folder_Exception();}
	return folder[folder_index];
}

void Folder::make_file(string _username,string _real_file_name,string _file_contents, double _file_size)
{
	File *new_file= new File(_username,_real_file_name, _file_contents, _file_size);
	file.push_back(new_file);

}


int search_file(string _file_name, vector<File*> &file)
{
	for(int i=0; i<file.size(); i++)
	{
		if(_file_name==file[i]->get_file_name())
			return i;
	}
	throw Search_file_Exception();
}
File* Folder::find_file(string _file_name)
{
	int file_index;
	try
	{
		file_index=search_file(_file_name, file);
	}catch(Search_file_Exception search_file_ex) {throw Find_file_Exception();}
	
	return file[file_index];
}
int Folder:: find_File(string _file_name)
{	
	int file_index;
	try
	{
		file_index=search_file(_file_name, file);
	}catch(Search_file_Exception search_file_ex) {throw Find_file_Exception();}
	
	return file_index;

}

void Folder::delete_file_from_folder(string _file_name)
{
	int file_index;
	try
	{
		file_index=search_file(_file_name, file);
	}catch(Search_file_Exception search_file_ex) {throw Delete_file_from_folder_Exception();}
	
	file.erase(file.begin()+file_index);
}

void Folder::remove_folder()
{
	for(int i=0; i<folder.size(); i++)
	{
		folder[i]->remove_folder();	
	}

	for(int i=0; i<file.size(); i++)
	{
		delete file[i];				
	}
	for(int i=0; i<folder.size(); i++)
	{
		
		delete folder[i];
	}
}

void Folder::remove(string folder_file_name)
{
	int element_index;
	
	try
		{
			
			element_index=find_folder(folder_file_name);
			folder[element_index]->remove_folder();
			delete folder[element_index];
			folder.erase(folder.begin()+element_index);
		}
	catch(Find_folder_Exception find_folder_ex) 
		{
			try
			{
				element_index=search_file(folder_file_name, file);
				delete file[element_index];
				file.erase(file.begin()+element_index);
			}
			catch(Search_file_Exception search_file_ex)
			{
				throw Romve_Exception();
			}
		}
}


double Folder::get_file_size(string file_name)
{
	int element_index=search_file(file_name, file);
	return file[element_index]->get_file_size();
}

string Folder::get_owner_user_name(string folder_file_name)
{
	int element_index;
	
	try
		{
			
			element_index=find_folder(folder_file_name);
			return folder[element_index]->get_user_name();
		}
	catch(Find_folder_Exception find_folder_ex) 
		{
			try
			{
				element_index=search_file(folder_file_name, file);
				return file[element_index]->get_user_name();
			}
			catch(Search_file_Exception search_file_ex)
			{
				throw Get_owner_Exception();
			}
		}
}

string Folder::get_owner_license(string folder_file_name)
{
	int element_index;
	
	try
		{
			
			element_index=find_folder(folder_file_name);
			return folder[element_index]->get_license();
		}
	catch(Find_folder_Exception find_folder_ex) 
		{
			try
			{
				element_index=search_file(folder_file_name, file);
				return file[element_index]->get_license();
			}
			catch(Search_file_Exception search_file_ex)
			{
				throw Get_owner_Exception();
			}
		}
}


string Folder::get_owner_group_name(string folder_file_name)
{
	int element_index;
	
	try
		{
			
			element_index=find_folder(folder_file_name);
			return folder[element_index]->get_group_name();
		}
	catch(Find_folder_Exception find_folder_ex) 
		{
			try
			{
				element_index=search_file(folder_file_name, file);
				return file[element_index]->get_group_name();
			}
			catch(Search_file_Exception search_file_ex)
			{
				throw Get_owner_Exception();
			}
		}
}


string Folder::get_group_license(string folder_file_name)
{
	int element_index;
	
	try
		{
			
			element_index=find_folder(folder_file_name);
			return folder[element_index]->get_gp_license();
		}
	catch(Find_folder_Exception find_folder_ex) 
		{
			try
			{
				element_index=search_file(folder_file_name, file);
				return file[element_index]->get_gp_license();
			}
			catch(Search_file_Exception search_file_ex)
			{
				throw Get_owner_Exception();
			}
		}
}

void Folder::change_mode(string group_user, string add_remove, string license,string current_user_name, string folder_file_name)
{
	int element_index;
	try
		{
			
			element_index=find_folder(folder_file_name);
			if(current_user_name!=folder[element_index]->get_user_name())
			{
				cout<<"No accesibilty"<<endl;
				return ;
			}
			folder[element_index]->folder_change_mode(add_remove,license, group_user );

		}
	catch(Find_folder_Exception find_folder_ex) 
		{
			try
			{
				element_index=search_file(folder_file_name, file);
				if(current_user_name!=file[element_index]->get_file_name())
				{
					cout<<"No accesibilty"<<endl;
					return ;
				}
				file[element_index]->file_change_mode(add_remove,license, group_user );
			}
			catch(Search_file_Exception search_file_ex)
			{
				cout<<"File Folder Not found"<<endl;
			}
		}

}


void Folder::folder_change_mode(string add_remove,string license,string  group_user )
{
	
	if(group_user=="user")
	{
		if(add_remove=="+")
		{
			if(license=="rw")
				user_license.license="RW";
			if(license=="read")
			{
				if(user_license.license=="W")
					user_license.license="RW";
			}
			if(license=="write")
			{
				if(user_license.license=="R")
					user_license.license="RW";
			}


		}
		if(add_remove=="-")
		{
			if(license=="rw")
				user_license.license="";
			if(license=="read")
			{
				if(user_license.license=="RW")
					user_license.license="W";
				if(user_license.license=="R")
					user_license.license="";
			}
			if(license=="write")
			{
				if(user_license.license=="RW")
					user_license.license="R";
				if(user_license.license=="W")
					user_license.license="";
			}
		}
	}
	if(group_user=="group")
	{
		if(add_remove=="+")
		{
			if(license=="rw")
				group_license.license="RW";
			if(license=="read")
			{
				if(group_license.license=="W")
					group_license.license="RW";
			}
			if(license=="write")
			{
				if(group_license.license=="R")
					group_license.license="RW";
			}


		}
		if(add_remove=="-")
		{
			if(license=="rw")
				group_license.license="";
			if(license=="read")
			{
				if(group_license.license=="RW")
					group_license.license="W";
				if(group_license.license=="R")
					group_license.license="";
			}
			if(license=="write")
			{
				if(group_license.license=="RW")
					group_license.license="R";
				if(group_license.license=="W")
					group_license.license="";
			}
		}
	}

}


void Folder::change_owner(string _username, string folder_file_name,string current_user_name)
{
	int element_index;
	try
		{
			
			element_index=find_folder(folder_file_name);
			if(current_user_name!=folder[element_index]->get_user_name())
			{
				cout<<"No accesibilty"<<endl;
				return ;
			}
			folder[element_index]->folder_change_owner(_username);

		}
	catch(Find_folder_Exception find_folder_ex) 
		{
			try
			{
				element_index=search_file(folder_file_name, file);
				if(current_user_name!=file[element_index]->get_file_name())
				{
					cout<<"No accesibilty"<<endl;
					return ;
				}
				file[element_index]->file_change_owner(_username );
			}
			catch(Search_file_Exception search_file_ex)
			{
				cout<<"File Folder Not found"<<endl;
			}
		}
}


void Folder::change_group(string group_name,string folder_file_name,string current_user_name)
{
	int element_index;
	try
		{
			
			element_index=find_folder(folder_file_name);
			if(current_user_name!=folder[element_index]->get_user_name())
			{
				cout<<"No accesibilty"<<endl;
				return ;
			}
			folder[element_index]->folder_change_group(group_name);

		}
	catch(Find_folder_Exception find_folder_ex) 
		{
			try
			{
				element_index=search_file(folder_file_name, file);
				if(current_user_name!=file[element_index]->get_file_name())
				{
					cout<<"No accesibilty"<<endl;
					return ;
				}
				file[element_index]->file_change_group(group_name );
			}
			catch(Search_file_Exception search_file_ex)
			{
				cout<<"File Folder Not found"<<endl;
			}
		}

}


//******************* PHASE II *************************
