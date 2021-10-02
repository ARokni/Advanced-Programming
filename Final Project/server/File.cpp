#include "File.h"
#include <iostream>
#include <vector>
using namespace std;
File::File(string _owner_name,string _file_name, string _file_contents, double _file_size)
{
	file_name=_file_name;
	file_size=_file_size;
	file_contents=_file_contents;

	user_license.username=_owner_name;
	user_license.license="RW";
	group_license.group_name=_owner_name;
	group_license.license="RW";
}

void File::file_change_mode(string add_remove,string license,string  group_user )
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