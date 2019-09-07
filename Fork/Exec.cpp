#include<stdio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<cstring>
#include<sstream>

using namespace std;

string GetStdoutFromCommand(string cmd)
{
	string data;
	FILE * stream;
	const int max_buffer = 250;
	char buffer[max_buffer];
	cmd.append(" 2>&1");
	
	stream = popen(cmd.c_str(), "r");
	if(stream)
	{
		while(!feof(stream))
			if(fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
				pclose(stream);
	}
	return data;
}


// ------------------FCFS-------------------------------------
class EXECCommands
{
	public:
		

		void Init();

};

void EXECCommands::Init()
{
	size_of_queue = 0;

	for(int i=0;i<no_of_files;i++)
	{
		PID[i] = -1;
		AT[i] = -1;
		BT[i] = -1;
		CT[i] = -1;
		TAT[i] = -1;
		WT[i] = -1;
	}
}

// -----------------------------------------------------------


int main()
{
	cout<<"------------------------------------ EXEC TEST DRIVER --------------------------------------\n";

	cout<<"Execl  -  1\n";
	cout<<"Execlp -  2\n";
	cout<<"Execv  -  3\n";
	cout<<"Exece  -  4\n";
	cout<<"Exit   -  0\n";

	int choice = 0;
	cout<<"Enter choice: ";
	cin>>choice;

	if(choice == 1)

	if(choice == 0)
	{
		cout<<"------------------------------------ EXEC TEST DRIVER --------------------------------------\n";
		return 0;
	}


	cout<<"------------------------------------ EXEC TEST DRIVER --------------------------------------\n";
	return 0;
}
