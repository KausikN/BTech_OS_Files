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

int StrToInt(char s[], int start, int end)
{
	int val = 0;
	for(int i = start; i <= end; i++)
	{
		if((int)s[i] >= 48 && (int)s[i] <= 57)
			val = (10*val) + (int)s[i] - 48;
	}
	return val;
}

// ------------------Priority_P_Aging-------------------------------------
class Priority_P_Aging
{
	public:
		int no_of_files;
		
		int PID[20], AT[20], BT[20];
		int CT[20], TAT[20], WT[20];
		
		int aging_factor;
		int priority_factor;
		
		int Priority[20];

		int order_of_exe[20];

		int size_of_queue;	

		int max_size;

		void Init();
		void AddProcess(int pid, int at, int bt, int priority);
		void RemoveProcess(int pid);
		void Evaluate();
		void SSort();
};

void Priority_P_Aging::Init()
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

void Priority_P_Aging::AddProcess(int pid, int at, int bt, int priority)
{
	if(size_of_queue < no_of_files)
	{
		PID[size_of_queue] = pid;
		AT[size_of_queue]= at;
		BT[size_of_queue] = bt;

		CT[size_of_queue] = 0;
		TAT[size_of_queue] = 0;
		WT[size_of_queue] = 0;
		
		Priority[size_of_queue] = priority;

		size_of_queue++;
	}
}

void Priority_P_Aging::RemoveProcess(int pid)
{
	for(int i=0;i<size_of_queue;i++)
	{
		if(PID[i] == pid)
		{
			PID[i] = -1;
			for(int j=i+1;j<size_of_queue;j++)
			{
				PID[j-1] = PID[j];
				AT[j-1] = AT[j];
				BT[j-1] = BT[j];
			}
			size_of_queue--;
			break;
		}
	}
}

void Priority_P_Aging::Evaluate()
{
	if(size_of_queue > 0)
	{
		SSort();
	
		int BT_temp[size_of_queue];
		for(int i=0;i<size_of_queue;i++) BT_temp[i] = BT[i];

		int no_completed = 0;
		int cur_time = AT[0];
		BT_temp[0] = BT_temp[0] - 1;
		cur_time++;
		CT[0] = cur_time;

		int prev_index = 0;
		
		cout<<"\nCURRENT PID: "<<PID[prev_index]<<", AT: "<<AT[prev_index]<<", BT: "<<BT_temp[prev_index]<<", Priority: "<<Priority[prev_index]<<", CT: "<<CT[prev_index]<<endl;
		
		while(no_completed < size_of_queue)
		{
			
			for(int j=0;j<size_of_queue;j++)
			{
				if(AT[j] <= cur_time && j != prev_index && BT_temp[j] > 0)
				{
					int wt = cur_time - AT[j];
					if(wt > aging_factor)
					{
						Priority[j] = Priority[j] + priority_factor;
					}
				}
			}
			
			
			
			int max_priority_index = -1;
			int least_at_index = -1;

			for(int j=0;j<size_of_queue;j++)
			{
				if(BT_temp[j] > 0 && AT[j] <= cur_time)
				{
					if(max_priority_index == -1 || Priority[max_priority_index] < Priority[j]) max_priority_index = j;
				}
				if(BT_temp[j] > 0) 
				{
					if((least_at_index == -1 || AT[least_at_index] > AT[j]) && AT[j] <= cur_time) least_at_index = j;
				} 
			}
			if(max_priority_index == -1)
			{
				cur_time++;

				if(least_at_index >= 0)
				{
					BT_temp[least_at_index] = BT_temp[least_at_index] - 1;
					CT[least_at_index] = cur_time;
					 
					if(BT_temp[least_at_index] == 0)
					{
						TAT[least_at_index] = CT[least_at_index] - AT[least_at_index];
						WT[least_at_index] = TAT[least_at_index] - BT[least_at_index];

						no_completed++;
					}
					prev_index = least_at_index;
				}
				else 
				{
					cout<<"No processes have arrived yet."<<endl;
					continue;
				}
			}
			else
			{
				cur_time++;
			
				BT_temp[max_priority_index] = BT_temp[max_priority_index] - 1;
				CT[max_priority_index] = cur_time;
				
				if(BT_temp[max_priority_index] == 0)
				{
					TAT[max_priority_index] = CT[max_priority_index] - AT[max_priority_index];
					WT[max_priority_index] = TAT[max_priority_index] - BT[max_priority_index];

					no_completed++;
				}
				prev_index = max_priority_index;
			}
			cout<<"\nCURRENT PID: "<<PID[prev_index]<<", AT: "<<AT[prev_index]<<", BT: "<<BT_temp[prev_index]<<", Priority: "<<Priority[prev_index]<<", CT: "<<CT[prev_index]<<endl;
		}
	}

	//Display
	for(int i=0;i<size_of_queue;i++)
	{
		cout<<endl<<"PID: "<<PID[i]<<" - AT: "<<AT[i]<<" - BT: "<<BT[i]<<" - Priority: "<<Priority[i]<<" - CT: "<<CT[i]<<" - TAT: "<<TAT[i]<<" - WT: "<<WT[i]<<endl;
	}
}

void Priority_P_Aging::SSort()
{
	for(int i=0;i<size_of_queue;i++)
	{
		int max_i = 0;
		for(int j=0;j<size_of_queue-i;j++)
		{
			if(AT[j] > AT[max_i])
			{
				max_i = j;
			}
		}

		int temp = PID[max_i];
		PID[max_i] = PID[size_of_queue - i - 1];
		PID[size_of_queue - i - 1] = temp;

		temp = AT[max_i];
		AT[max_i] = AT[size_of_queue - i - 1];
		AT[size_of_queue - i - 1] = temp;

		temp = BT[max_i];
		BT[max_i] = BT[size_of_queue - i - 1];
		BT[size_of_queue - i - 1] = temp;
	}
}


// -----------------------------------------------------------


int main()
{
	// Init
	Priority_P_Aging p;

	p.no_of_files = 7;
	cout<<"Enter no of files: ";
	cin>>p.no_of_files;
	
	p.aging_factor = 0;
	cout<<"Enter aging factor: ";
	cin>>p.aging_factor;
	
	p.priority_factor = 0;
	cout<<"Enter priority factor: ";
	cin>>p.priority_factor;
	
	int custom_input = 0;
	cout<<"Do you want custom input: ";
	cin>>custom_input;

	p.Init();

	// Get BTs

	for(int i = 1; i <= p.no_of_files; i++)
	{
		int pid = i;
		double at;
		int bt;
		
		int priority;
		
		if(custom_input == 0)
		{
		
			cout<<"Enter priority for "<<pid<<": ";
			cin>>priority;
		
			char ci[] = "0.txt";
			ci[0] = (char)(i+48);
		
			// Get ATs
			char cmd_stat[] = "stat ";

			strcat(cmd_stat, ci);
			cout<<cmd_stat<<endl;

			string command_stat = GetStdoutFromCommand(cmd_stat);
			cout<<command_stat<<endl;

			char crtime[18];

			for(int j=0;j<500-5;j++)
			{
				char check[6];
				check[0] = command_stat[j];
				check[1] = command_stat[j + 1];
				check[2] = command_stat[j + 2];
				check[3] = command_stat[j + 3];
				check[4] = command_stat[j + 4];
				check[5] = command_stat[j + 5];

				check[6] = '\0';

				if(strcmp(check, "Modify") == 0)
				{
					for(int k=j+19; k<j+37; k++)
					{
						crtime[k-j-19] = command_stat[k];
					}
					crtime[18] = '\0';
					break;
				}
			}
		
		
			cout<<crtime<<endl;

			int crtime_hr = StrToInt(crtime, 0, 1);
			int crtime_min = StrToInt(crtime, 3, 4);
			int crtime_sec = StrToInt(crtime, 6, 7);
			int crtime_sec_decimal = StrToInt(crtime, 9, 12);

			cout<<"\nHr: "<<crtime_hr<<" - "<<"Min: "<<crtime_min<<" - "<<"Sec: "<<crtime_sec<<" - "<<"dec: "<<(0.0001 * crtime_sec_decimal)<<" - "<<endl;

			double creation_time = 3600 * crtime_hr + 60 * crtime_min + crtime_sec + (0.0001 * crtime_sec_decimal);

			at = creation_time;

	
			cout<<"\nFile "<<i<<".txt was created at "<<creation_time<<"."<<endl;

			// Get BTs
			char cmd_wc[] = "wc -m ";

			strcat(cmd_wc, ci);
			cout<<cmd_wc<<endl;

			string command_wc = GetStdoutFromCommand(cmd_wc);
		
			int letter_count;
			stringstream input_wc(command_wc);
			input_wc >> letter_count;
		
			bt = letter_count;

			cout<<"\nFile "<<i<<".txt has "<<letter_count<<" letters."<<endl;
		}
		else 
		{
			cout<<"Enter AT"<<i<<": ";
			cin>>at;
			cout<<"Enter BT"<<i<<": ";
			cin>>bt;
			cout<<"Enter Priority"<<i<<": ";
			cin>>priority;
		}

		p.AddProcess(pid, at, bt, priority);
	}

	p.Evaluate();
	
	cout<<endl<<"END"<<endl;
	
	return 0;
}
