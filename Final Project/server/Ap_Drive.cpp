#include "Ap_Drive.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>
using namespace std;

#define SUPERUSER 0;
#define ADMIN 1;
#define NORMALUSER 2;
#define COPY 0
#define MOVE 1
#define NOTHING 2


bool current_user_is_not_member_of(string _group_name, vector<string> user_groups_names)
{
	for(int i=0; i<user_groups_names.size(); i++)
	{
		if(_group_name==user_groups_names[i])
			return 0;
	}
	return 1;
}


bool access_permission(User* _user)
{
	if(_user==NULL)
		return 0;
	else
		return ((_user->get_position()=="Superuser")||(_user->get_position()=="Admin"));
}

bool repeated_group_name(string _group_name, vector<string> &group)
{
	for(int i=0; i<group.size(); i++)
	{
		if(_group_name==group[i])
			return 1;
	}
	return 0;
}


int Ap_Drive::find_user(string _username)
{
	
	for(int i=0; i<user.size(); i++)
	{
		if(_username==user[i]->get_username())
		{
			
			return i;
		}
	}
	throw Find_user_Exception();
}
int Ap_Drive::find_group(string _group_name)
{
	for(int i=0; i<group.size(); i++)
	{
		if(_group_name==group[i])
			return i;
	}
	throw Find_Group_Exception();
}


void get_path(vector<string> &path, string _directory)
{
	int count=0;
	for(int i=0; i<_directory.size(); i++)
	{
		if((_directory[i]=='/'))
		{
			path.push_back(_directory.substr(count,i-count));
			count =i+1;
		}
		else if(i==_directory.size()-1)
		{
			i++;
			path.push_back(_directory.substr(count,i-count));
		}
	}
}

void Ap_Drive::go_to(vector<string> & path, string _directory)
{
	
	int start=0;
	if(_directory[0]=='/')
	{
		current_folder=root;
		start=1;
	}
	try
	{
		for(int i=start;i<path.size(); i++)
		{
			current_folder=current_folder->next_folder(path[i]);
		}
	}catch(Find_folder_Exception find_folder_ex)
	{
		go_to_root();
		cout<<"Directory Not Found"<<endl;
	}

}


string union_of_licenses(string license_temp1,string license_temp2)
{
	if((license_temp1=="RW")||(license_temp2=="RW"))
		return "RW";
	else if((license_temp1=="R")&&(license_temp2=="W"))
		return "RW";
	else if((license_temp1=="W")&&(license_temp2=="R"))
		return "RW";
	else 
		return license_temp1;
}


string get_user_license(User* &current_user, string owner_user_name, string user_license, string owner_group_name, string group_license)
{
	string license_temp1="";
	string license_temp2;
	if(current_user->get_username()==owner_user_name)
		license_temp1= user_license;
	if(current_user_is_not_member_of(owner_group_name, current_user->get_groups_names()))
		license_temp2= "";
	else
		license_temp2=group_license;
	return union_of_licenses(license_temp1,license_temp2);
}

void Ap_Drive::get_license(string &license, string _path)
{
	if(current_user!=NULL)
	{
		if(current_user->get_username()=="root")
		{
			license="RW";
			return;
		}
	}

	vector<string> folder_path;
	Folder* current_folder_temp=current_folder;
	string folder_file_name;
	if(_path=="")
	{
		_path=current_folder->get_current_directory();
	}
	
		get_path(folder_path, _path);
		int ind=folder_path.size()-1;
		folder_file_name=folder_path[ind];
		folder_path.pop_back();
		go_to(folder_path, _path);
	
	string owner_user_name;
	string user_license;
	string owner_group_name;
	string group_license;



	try
	{
		owner_user_name=current_folder->get_owner_user_name(folder_file_name);
		user_license=current_folder->get_owner_license(folder_file_name);
		owner_group_name=current_folder->get_owner_group_name(folder_file_name);
		group_license=current_folder->get_group_license(folder_file_name);
	}catch(Get_owner_Exception get_owner_ex) 
	{
		cout<<"Invalid directory"<<endl;
		throw Get_license_Excaption();
	}

	
	license=get_user_license(current_user, owner_user_name, user_license, owner_group_name, group_license);
	current_folder=current_folder_temp;
	

}

void Ap_Drive::make_directory(string directory_name)
{
	string license;
	try
	{
		get_license(license,"");
	}catch(Get_license_Excaption get_license_ex) {throw Make_directory_Exception();}
	if((license!="RW")&&(license!="W"))
	{
		cout<<"No accessiblity"<<endl;
		throw Make_directory_Exception();
	}

	string _username=current_user->get_username();

	current_folder->make_directory(directory_name, _username);
	
}

Ap_Drive:: Ap_Drive()
{
	User* superuser=new User("root", "root","Superuser");
	user.push_back(superuser);
	current_user=NULL;
	current_folder=new Folder();
	root=current_folder;
	
	current_folder->make_directory("root","root");

	current_folder=current_folder->next_folder("root");
	group.push_back("root");
	storage=0;
	copy_move_flag=NOTHING;


}


void Ap_Drive::add_user(string _username, string _password)
{
	
	Folder* current_folder_temp=current_folder;
	if(access_permission(current_user))
	{
		User* normaluser=new User(_username,_password,"Normaluser");
		user.push_back(normaluser);
		go_to_root();
		current_folder->make_directory(_username, _username);
	}
	else 
		throw Access_Permission_Exception();
	
	
	current_folder=current_folder->next_folder(_username);
	group.push_back(_username);
	current_folder=current_folder_temp;


}

void Ap_Drive::login(string _username, string _password)
{
	
	int user_index;
	try
	{
		
		user_index=find_user(_username);
	}catch(Find_user_Exception find_user_ex) {throw Login_Exception();}
	current_user=user[user_index];
	go_to_root();
	for(int i=0; i<current_folder->get_folder().size(); i++)
	{
		if(current_folder->get_folder()[i]->get_folder_name()==_username)
			current_folder=current_folder->get_folder()[i];
	}

	//************* bellow for testing **************
	// Folder* temp_folder= new Folder();
	// temp_folder=current_folder;
	
	// current_folder->make_directory("amire", "goom");
	// current_folder->make_directory("alie", "goom");
	// go_to_root();
	// change_directory("amire");
	//current_folder->make_directory("amirreza", "tebezbeza");
	// current_folder=root;
	
	//upload("file.txt","/root");
	// current_folder=temp_folder;
	
}


void add_group_check(User* &current_user, string _group_name, vector<string> &group)
{
	if(current_user==NULL)
		throw Add_Group_Exception();
	if(repeated_group_name(_group_name, group))
		throw Add_Group_Exception();
}

void Ap_Drive::add_group(string _group_name)
{
	add_group_check(current_user, _group_name, group);
	group.push_back(_group_name);
	current_user->add_to_group(_group_name);

}



void add_to_group_check(string  _group_name, vector<string> user_groups_names)
{
	if(current_user_is_not_member_of(_group_name, user_groups_names))
	{
		cout<<"curre user is not member of this group"<<endl;
		throw Add_to_group_Exception();
	}

}


void Ap_Drive::add_to_group(string _group_name, string _username)
{
	
	int group_index;
	int user_index;

	
	try
	{
		group_index=find_group(_group_name);
	}catch(Find_Group_Exception find_group_ex) {throw Add_to_group_Exception();}
	add_to_group_check( _group_name, current_user->get_groups_names());


	try
	{
		user_index=find_user(_username);
	}catch(Find_user_Exception find_user_ex) {throw Add_to_group_Exception();}
	user[user_index]->add_to_group(_group_name);
	
	
}




void read_file(string &str, double &file_size_bytes, string real_file_name)
{
	std::ifstream t(real_file_name.c_str());
	std::string str_temp((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
	 std::ifstream in(real_file_name.c_str(), std::ifstream::ate | std::ifstream::binary);
	 str=str_temp;	
     file_size_bytes=in.tellg();
}







void Ap_Drive::upload(string real_file_name, string path)
{
	
	if(current_user==NULL)
		throw Upload_Exception();
	vector<string> address;
	string str;
	string license;
	try
	{
		get_license(license,path);
	}catch(Get_license_Excaption get_license_ex) {throw Upload_Exception();}
	if((license!="RW")&&(license!="W"))
	{
		cout<<"No accessiblity"<<endl;
		throw Upload_Exception();
	}

	double file_size_bytes;
	read_file(str, file_size_bytes, real_file_name);
	get_path(address, path);
	go_to(address, path);
	string _username=current_user->get_username();
	current_folder->make_file(_username,real_file_name, str, file_size_bytes/1024.0);
	storage+=(file_size_bytes/1024.0);

}

void Ap_Drive::download(string _path, string _output_name)
{
	
	if(current_user==NULL)
		throw Download_Exception();
	string license;
	try
	{
		get_license(license,_path);
	}catch(Get_license_Excaption get_license_ex) {throw Download_Exception();}
	if((license!="RW")&&(license!="R"))
	{
		cout<<"No accessiblity"<<endl;
		throw Download_Exception();
	}

	vector<string> folder_path;
	string file_name;
	get_path(folder_path, _path);
	int ind=folder_path.size()-1;
	file_name=folder_path[ind];
	folder_path.pop_back();
	go_to(folder_path, _path);

	File* my_file= current_folder->find_file(file_name);
	
	string file_contents=my_file->get_file_contents();
	ofstream outfile;
    outfile.open(_output_name.c_str());
    outfile << file_contents.c_str() << endl;
}


void Ap_Drive::copy(string source_path, string destination_path)
{

	
	if(current_user==NULL)
		throw Copy_Exception();
	string license;
	try
	{
		get_license(license,source_path);
	}catch(Get_license_Excaption get_license_ex) {throw Copy_Exception();}
	if((license!="RW")&&(license!="R"))
	{
		cout<<"No accessiblity"<<endl;
		throw Copy_Exception();
	}
	try
	{
		get_license(license,destination_path);
	}catch(Get_license_Excaption get_license_ex) {throw Copy_Exception();}
	if((license!="RW")&&(license!="W"))
	{
		cout<<"No accessiblity"<<endl;
		throw Copy_Exception();
	}







	vector<string> folder_path;
	get_path(folder_path, source_path);
	int ind=folder_path.size()-1;
	string file_name=folder_path[ind];
	folder_path.pop_back();
	
	go_to(folder_path, source_path);
	File* my_file= current_folder->find_file(file_name);
	upload(file_name, destination_path);

}

void Ap_Drive::move(string source_path,string destination_path)
{

	if(current_user==NULL)
		throw Move_Exception();
	string license;
	try
	{
		get_license(license,source_path);
	}catch(Get_license_Excaption get_license_ex) {throw Move_Exception();}
	if((license!="RW")&&(license!="W"))
	{
		cout<<"No accessiblity"<<endl;
		throw Move_Exception();
	}

	try
	{
		get_license(license,destination_path);
	}catch(Get_license_Excaption get_license_ex) {throw Move_Exception();}
	if((license!="RW")&&(license!="W"))
	{
		cout<<"No accessiblity"<<endl;
		throw Move_Exception();
	}




	vector<string> folder_path;
	get_path(folder_path, source_path);
	int ind=folder_path.size()-1;
	string file_name=folder_path[ind];
	folder_path.pop_back();

	Folder* current_folder_temp1=current_folder;
	try
	{
		copy(source_path, destination_path);
		Folder* current_folder_temp2= current_folder;
		current_folder=current_folder_temp1;
		
		go_to(folder_path, source_path);
		current_folder->delete_file_from_folder(file_name);
		current_folder=current_folder_temp2;
 
	}catch(Find_file_Exception find_file_ex) {throw Move_Exception();}
}
void Ap_Drive::remove(string _path)
{
	if(current_user==NULL)
		throw Remove_Exception();

	string license;
	try
	{
		
		get_license(license,_path);
	}catch(Get_license_Excaption get_license_ex) {throw Remove_Exception();}
	if((license!="RW")&&(license!="W"))
	{
		cout<<"No accessiblity"<<endl;
		throw Remove_Exception();
	}



	vector<string> folder_path;
	
	get_path(folder_path, _path);
	int ind=folder_path.size()-1;
	string folder_file_name=folder_path[ind];
	folder_path.pop_back();
	go_to(folder_path, _path);
	current_folder->remove(folder_file_name);



}


void Ap_Drive::change_directory(string _path)
{
	if(current_user==NULL)
		throw Change_driectory_Exception();
	vector<string> address;
	string str;
	string license;
	try
	{
		get_license(license,_path);
	}catch(Get_license_Excaption get_license_ex) {throw Change_driectory_Exception();}
	if((license!="RW")&&(license!="R"))
	{
		cout<<"No accessiblity"<<endl;
		throw Change_driectory_Exception();
	}



	vector<string> folder_path;
	get_path(folder_path, _path);
	go_to(folder_path, _path);


}

double Ap_Drive::file_size(string _path)
{
	vector<string> folder_path;
	
	get_path(folder_path, _path);
	int ind=folder_path.size()-1;
	string file_name=folder_path[ind];
	folder_path.pop_back();
	go_to(folder_path, _path);
	return current_folder->get_file_size(file_name);

}


void Ap_Drive::promote(string user_name, string new_position)
{
	if(current_user->get_position()!="Superuser")
	{
		cout<<"Current user is not a superuser one"<<endl;
		throw Promote_Exception();
	}
	int user_ind=find_user(user_name);
	user[user_ind]->promote(new_position);
}

void Ap_Drive::demote(string user_name, string new_position)
{
	if(current_user->get_position()!="Superuser")
	{
		cout<<"Current user is not a superuser one"<<endl;
		throw demote_Exception();
	}
	int user_ind=find_user(user_name);
	user[user_ind]->demote(new_position);
}

void Ap_Drive::userlist()
{
	if(current_user->get_position()=="Normaluser")
	{
		cout<<"Normaluser can not see userlist"<<endl;
		throw Userlist_Exception();
	}
	for(int i=0; i<user.size(); i++)
		cout<<user[i]->get_username()<<endl;
}


void Ap_Drive::change_mode(vector<string>command)
{
	string path=command[4];

	vector<string> folder_path;
	Folder* current_folder_temp=current_folder;
	string folder_file_name;
	if(path=="")
	{
		path=current_folder->get_current_directory();
	}
	
		get_path(folder_path, path);
		int ind=folder_path.size()-1;
		folder_file_name=folder_path[ind];
		folder_path.pop_back();
		string group_user=command[1];
		string add_remove=command[2];
		string license=command[3];
		string current_user_name=current_user->get_username();
		
		go_to(folder_path, path);
		current_folder->change_mode(group_user, add_remove, license,current_user_name,folder_file_name);

}


void Ap_Drive::change_owner(string _username,string path)
{
	vector<string> folder_path;
	Folder* current_folder_temp=current_folder;
	string folder_file_name;
	if(path=="")
	{
		path=current_folder->get_current_directory();
	}
	
		get_path(folder_path, path);
		int ind=folder_path.size()-1;
		folder_file_name=folder_path[ind];
		folder_path.pop_back();
		string current_user_name=current_user->get_username();
		go_to(folder_path, path);
		current_folder->change_owner(_username,folder_file_name,current_user_name);
}

void Ap_Drive::change_group(string group_name,string path)
{

	vector<string> folder_path;
	Folder* current_folder_temp=current_folder;
	string folder_file_name;
	if(path=="")
	{
		path=current_folder->get_current_directory();
	}
	
		get_path(folder_path, path);
		int ind=folder_path.size()-1;
		folder_file_name=folder_path[ind];
		folder_path.pop_back();
		string current_user_name=current_user->get_username();
		go_to(folder_path, path);
		current_folder->change_group(group_name,folder_file_name,current_user_name);
}


void Ap_Drive::remove_server()
{
	string folder_file_name;
	go_to_root();
	int up_count=current_folder->get_folder().size();

	for(int i=0; i<up_count;i++)
	{
		
		folder_file_name=current_folder->get_folder()[0]->get_folder_name();
		go_to_root();
		current_folder->remove(folder_file_name);

		go_to_root();
	}
	delete root;

}
//******************** Phase 2 **********************
void login_user_pas(Request* &request, string &username, string &password)
{
	
username=request->getBodyParam("username");
password=request->getBodyParam("password");




}

void do_login(Request* &request, Ap_Drive* ap_drive)
{
	string password, username;
	login_user_pas(request, username, password);
	try
	{
		ap_drive->login(username, password);
	}catch(Login_Exception login_ex) {
		cout<<"Login Error"<<endl;
		throw Ap_Drive_Exception();
	}
}



void go_back(Ap_Drive* &ap_drive)
{	
	
	string _path=ap_drive->get_current_folder()->get_prev_directory();
	if(_path=="")
		ap_drive->go_to_root();
	else
		ap_drive->change_directory(_path);
}
void do_remove(Ap_Drive* &ap_drive,Request* &request)
{
	string path=request->getQueryParam("name2");
	ap_drive->remove(path);
}
void do_copy_move(Ap_Drive* &ap_drive,Request* &request, string query)
{
	string path = ap_drive->get_current_folder()->get_current_directory();
	path+="/";
	path+=request->getQueryParam("name2");
	if(query=="copy")
		ap_drive->set_copy_move_flag(COPY);
	else
	    ap_drive->set_copy_move_flag(MOVE);

	ap_drive->set_copy_move_source(path);
}



void do_paste(Ap_Drive* &ap_drive,Request* &request)
{
	int _copy_move_flag = ap_drive->get_copy_move_flag();
	string source_path = ap_drive->get_copy_move_source();
	string destination_path = ap_drive->get_current_folder()->get_current_directory();
	
	switch (_copy_move_flag)
	{
		case COPY :
			ap_drive->copy(source_path , destination_path);
			break;
		case MOVE :
			ap_drive->move(source_path , destination_path);
			break;
		default : 
			break;
	}
}







void do_showlist(Request* &request, Ap_Drive* ap_drive)
{
	string query=request->getQueryParam("name");
	if(query=="back")
		go_back(ap_drive);
	else if(query=="remove")
		do_remove(ap_drive, request);
	else if((query=="copy")||(query=="move"))
		do_copy_move(ap_drive, request, query);
	else if(query=="paste")
		do_paste(ap_drive, request);
	else
		ap_drive->change_directory(query);
}
void do_showfile(Request* &request, Ap_Drive* ap_drive)
{
	string filename=request->getQueryParam("name");
	string file_content=ap_drive->get_current_folder()->find_file(filename)->get_file_contents();
	ap_drive->set_selected_file(file_content);
	
}

void show_details_folder(Ap_Drive* &ap_drive, int folder_ind)
{
	string  details_temp;
	vector<string> details;

	details_temp = "Folder";
	details.push_back(details_temp);


	details_temp = ap_drive->get_current_folder()->get_folder()[folder_ind]->get_folder_name();
	details.push_back(details_temp);

	details_temp = ap_drive->get_current_folder()->get_folder()[folder_ind]->get_user_name();
	details.push_back(details_temp);


	details_temp = ap_drive->get_current_folder()->get_folder()[folder_ind]->get_license();
	details.push_back(details_temp);

	details_temp = ap_drive->get_current_folder()->get_folder()[folder_ind]->get_group_name();
	details.push_back(details_temp);

	details_temp = ap_drive->get_current_folder()->get_folder()[folder_ind]->get_gp_license();
	details.push_back(details_temp);

	ap_drive->set_details(details);

}

void show_details_file(Ap_Drive* &ap_drive, int file_ind)
{
	string  details_temp;
	vector<string> details;

	details_temp = "File";
	details.push_back(details_temp);


	details_temp = ap_drive->get_current_folder()->get_file()[file_ind]->get_file_name();
	details.push_back(details_temp);

	details_temp = ap_drive->get_current_folder()->get_file()[file_ind]->get_user_name();
	details.push_back(details_temp);


	details_temp = ap_drive->get_current_folder()->get_file()[file_ind]->get_license();
	details.push_back(details_temp);

	details_temp = ap_drive->get_current_folder()->get_file()[file_ind]->get_group_name();
	details.push_back(details_temp);

	details_temp = ap_drive->get_current_folder()->get_file()[file_ind]->get_gp_license();
	details.push_back(details_temp);

	double size_temp = ap_drive->get_current_folder()->get_file()[file_ind]->get_file_size();
	details_temp = to_string(size_temp);
	details.push_back(details_temp);
	ap_drive->set_details(details);

}
void do_details(Request* &request, Ap_Drive* ap_drive)
{
	
	string file_folder_name = request->getQueryParam("name2");
	try
	{
		int folder_ind = ap_drive->get_current_folder()->find_folder(file_folder_name);
		show_details_folder(ap_drive, folder_ind);
	}catch(Find_folder_Exception find_folder_ex)
	{
		int file_ind = ap_drive->get_current_folder()->find_File(file_folder_name);
		show_details_file(ap_drive, file_ind);
	}

}
void do_promote(Ap_Drive* &ap_drive , string username)
{
	int user_ind=ap_drive->find_user(username);
	string current_position = ap_drive->get_users()[user_ind]->get_position();
	if(current_position=="Normaluser")
		ap_drive->get_users()[user_ind]->promote("Admin");
	else
		ap_drive->get_users()[user_ind]->promote("Superuser");
}
void do_demote(Ap_Drive* &ap_drive , string username)
{
	int user_ind=ap_drive->find_user(username);
	string current_position = ap_drive->get_users()[user_ind]->get_position();
	if(current_position=="Superuser")
   		 ap_drive->get_users()[user_ind]->demote("Admin");
	else
		 ap_drive->get_users()[user_ind]->demote("Normaluser");

}
void do_userlist(Request* &request, Ap_Drive* ap_drive)
{
	string query1 = request->getQueryParam("name");
	string username = request->getQueryParam("name2");
	if(query1=="promote")
		do_promote(ap_drive , username);
	else if(query1=="demote") 
		do_demote(ap_drive , username);
}

void Ap_Drive::do_action(Request* request)
{
	if((request->getMethod()==POST)&&(request->getPath()=="/login"))
		do_login(request, this);
	if(request->getPath()=="/showlist")
		do_showlist(request, this);
	if(request->getPath()=="/showfile")
		do_showfile(request, this);
	if(request->getPath()=="/logout")
		this->logout();
	if(request->getPath()=="/details")
		do_details(request, this);
	if(request->getPath()=="/userlist")
		do_userlist(request, this);
	
}

