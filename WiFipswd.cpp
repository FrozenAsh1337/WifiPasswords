#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
int main()
{
	int line_count=0;
	char* ID;
	std::string name,pwd,line,cmd;
	std::vector<std::string> names={},pwds={};
	std::ifstream dataRead;
	system("netsh wlan show profiles | findstr -r -s -i -m -c:\"\\<    All User Profile\\>\">Wifi_Passwords.txt");
	dataRead.open("Wifi_Passwords.txt");
	while(dataRead>>line)
	{
		if(line_count==4)
		{
			names.push_back(line);
		}
		line_count++;
		line_count%=5;
	}
	dataRead.close();
	std::ofstream dataWrite;
	dataWrite.open("Wifi_Passwords.txt");
	dataWrite.close();
	for(int i=0;i<names.size();i++)
	{
		cmd="netsh wlan show profile "+names.at(i)+" key=clear | findstr -r -s -i -m -c:\"\\<Key Content\\>\">>Wifi_Passwords.txt";
		system(cmd.c_str());
	}
	line_count=0;
	dataRead.open("Wifi_Passwords.txt");
	while(dataRead>>line)
	{
		if(line_count==3)
		{
			pwds.push_back(line);
		}
		line_count++;
		line_count%=4;
	}
	dataRead.close();
	dataWrite.open("Wifi_Passwords.txt");
	for(int j=0;j<names.size();j++)
	{
		std::cout<<"\""<<names.at(j)<<"\":\""<<pwds.at(j)<<"\""<<std::endl;
		dataWrite<<"\""<<names.at(j)<<"\":\""<<pwds.at(j)<<"\""<<std::endl;
	}
	getchar();
	return 0;
}