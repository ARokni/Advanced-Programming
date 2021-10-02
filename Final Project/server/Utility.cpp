#include "Utility.h"
#include <iostream>
#include<string>
#include<vector>
#include <fstream>
#include <cstdlib>
#include<stdlib.h>
#include<sstream>
using namespace std;

void read_command(vector<string> &command, string &temp)
{
	stringstream in(temp);
	while(in>>temp)
	{
		command.push_back(temp);
	}
}