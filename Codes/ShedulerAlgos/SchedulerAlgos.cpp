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

// ------------------Scheduler Algos-------------------------------------
class SchedulerAlgos
{
	public:
		int no_of_files;
		
		int PID[20], AT[20], BT[20];
		int CT[20], TAT[20], WT[20];
		
		int Priority[20];
		
		int aging_factor;
		int priority_factor;
		
		int tq;

		int size_of_queue;	

		int max_size;

		void Init();
		void AddProcess(int pid, int at, int bt, int priority);
		void RemoveProcess(int pid);
		void SSort();
		float ResponseRatio(int index, int prev_index);
		void Display();
		
		void Evaluate_NP(char value_to_optimise);
		void Evaluate_P(char value_to_optimise, int aging);
		void Evaluate_RoundRobin();
		void Evaluate_FCFS();
		
		
		void FCFS();
		void SJF();
		
		void SRT();
		void RoundRobin();
		
		void Priority_NP();
		void Priority_P();
		void Priority_P_Aging();
		
		void HRRN_NP();
		
};

void SchedulerAlgos::Init()
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

void SchedulerAlgos::AddProcess(int pid, int at, int bt, int priority)
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

void SchedulerAlgos::RemoveProcess(int pid)
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

void SchedulerAlgos::SSort()
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

float SchedulerAlgos::ResponseRatio(int index, int prev_index)
{
	int wt = CT[prev_index] - AT[index];
	int st = BT[index];
	return (1 + (wt/st));
}

void SchedulerAlgos::Display()
{
	for(int i=0;i<size_of_queue;i++)
	{
		cout<<endl<<"PID: "<<PID[i]<<" - AT: "<<AT[i]<<" - BT: "<<BT[i]<<" - CT: "<<CT[i]<<" - TAT: "<<TAT[i]<<" - WT: "<<WT[i]<<endl;
	}
}
// -------------------------------------------------------------------------------------------

void SchedulerAlgos::FCFS()
{
	Evaluate_FCFS();
}
void SchedulerAlgos::SJF()
{
	Evaluate_NP('B');
}
// ------------------------
void SchedulerAlgos::SRT()
{
	Evaluate_P('B', 0);
}
void SchedulerAlgos::RoundRobin()
{
	Evaluate_RoundRobin();
}
// ------------------------
void SchedulerAlgos::Priority_NP()
{
	Evaluate_NP('P');
}
void SchedulerAlgos::Priority_P()
{
	Evaluate_P('P', 0);
}
void SchedulerAlgos::Priority_P_Aging()
{
	Evaluate_P('P', 1);
}

void SchedulerAlgos::HRRN_NP()
{
	Evaluate_NP('H');
}


// --------------------Main---------------------------------------


int main()
{
	// Init
	SchedulerAlgos s;
	
	int algo = 1;
	cout<<"FCFS	-	1\n";
	cout<<"SJF	-	2\n";
	cout<<"SRT	-	3\n";
	cout<<"RoundRobin	-	4\n";
	cout<<"Priority Preemptive	-	5\n";
	cout<<"Priority Non Preemptive	-	6\n";
	cout<<"Priority Preemptive With Aging	-	7\n";
	cout<<"HRRN Non Preemptive	-	8\n";
	
	cout<<"Enter Algo choice: ";
	cin>>algo;

	s.no_of_files = 7;
	cout<<"Enter no of files: ";
	cin>>s.no_of_files;
	
	int custom_input = 0;
	cout<<"Do you want custom input: ";
	cin>>custom_input;
	
	if(algo == 7)
	{
		cout<<"Enter aging factor: ";
		cin>>s.aging_factor;
		
		cout<<"Enter priority factor: ";
		cin>>s.priority_factor;
	}

	s.Init();

	// Get BTs

	for(int i = 1; i <= s.no_of_files; i++)
	{
		int pid = i;
		double at;
		int bt;
		
		int priority;
		
		if(algo == 5 || algo == 6)
		{
			cout<<"Enter Priority for "<<i<<": ";
			cin>>priority;
		}
		
		if(custom_input == 0)
		{
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
		}

		s.AddProcess(pid, at, bt, priority);
	}

	if(algo == 1)s.FCFS();
	if(algo == 2)s.SJF();
	if(algo == 3)s.SRT();
	if(algo == 4)s.RoundRobin();
	if(algo == 5)s.Priority_NP();
	if(algo == 6)s.Priority_P();
	if(algo == 6)s.Priority_P_Aging();
	if(algo == 8)s.HRRN_NP();
	
	cout<<endl<<"END"<<endl;
	
	return 0;
}
// --------------------------------------------------------------------------------------

// --------------Evaluate Functions------------------------------------------------------

void SchedulerAlgos::Evaluate_P(char value_to_optimise, int aging)
{
	if(size_of_queue > 0)
	{
		SSort();
		
		int AT_temp[size_of_queue];
		
		if(aging == 1 && value_to_optimise == 'P') 
		{
			for(int i=0;i<size_of_queue;i++) AT_temp[i] = AT[i];
		}
	
		int BT_temp[size_of_queue];
		for(int i=0;i<size_of_queue;i++) BT_temp[i] = BT[i];

		int no_completed = 0;
		int cur_time = AT[0];
		BT_temp[0] = BT_temp[0] - 1;
		cur_time++;
		CT[0] = cur_time;

		int prev_index = 0;
		
		cout<<"\nCURRENT PID: "<<PID[prev_index]<<", AT: "<<AT[prev_index]<<", BT: "<<BT_temp[prev_index]<<", CT: "<<CT[prev_index]<<endl;
		
		while(no_completed < size_of_queue)
		{
			int opt_index = -1;
			int least_at_index = -1;

			for(int j=0;j<size_of_queue;j++)
			{
				if(BT_temp[j] > 0 && AT[j] <= cur_time)
				{
					bool cond;
					if(value_to_optimise == 'B') cond = BT_temp[opt_index] > BT_temp[j];
					else if(value_to_optimise == 'P') cond = Priority[opt_index] < Priority[j];

					if(opt_index == -1 || cond) opt_index = j;
				}
				if(BT_temp[j] > 0) 
				{
					if((least_at_index == -1 || AT[least_at_index] > AT[j]) && AT[j] <= cur_time) least_at_index = j;
				} 
			}
			if(opt_index == -1)
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
			
				BT_temp[opt_index] = BT_temp[opt_index] - 1;
				CT[opt_index] = cur_time;
				
				if(BT_temp[opt_index] == 0)
				{
					TAT[opt_index] = CT[opt_index] - AT[opt_index];
					WT[opt_index] = TAT[opt_index] - BT[opt_index];

					no_completed++;
				}
				prev_index = opt_index;
			}
			
			
			// Update Aging based Priorities
			if(aging == 1 && value_to_optimise == 'P') 
			{
				for(int j=0;j<size_of_queue;j++)
				{
					if(AT[j] <= cur_time && j != prev_index && BT_temp[j] > 0)
					{
						int wt = cur_time - AT_temp[j];
						if(wt > aging_factor)
						{
							Priority[j] = Priority[j] + priority_factor;
						}
					}
				}
			}
			
			
			
			cout<<"\nCURRENT PID: "<<PID[prev_index]<<", AT: "<<AT[prev_index]<<", BT: "<<BT_temp[prev_index]<<", CT: "<<CT[prev_index]<<endl;
		}
	}

	//Display
	Display();
}

void SchedulerAlgos::Evaluate_NP(char value_to_optimise)
{
	if(size_of_queue > 0)
	{
		int BT_temp[size_of_queue];
		for(int i=0;i<size_of_queue;i++) BT_temp[i] = BT[i];

		SSort();

		CT[0] = AT[0] + BT[0];
		TAT[0] = CT[0] - AT[0];
		WT[0] = TAT[0] - BT[0];

		int prev_index = 0;
		for(int i=1;i<size_of_queue;i++)
		{
			int opt_index = -1;
			int least_at_index = -1;

			for(int j=1;j<size_of_queue;j++)
			{
				if(BT_temp[j] >= 0 && AT[j] <= CT[prev_index])
				{
					bool cond;
					if(value_to_optimise == 'B') cond = BT_temp[opt_index] > BT_temp[j];
					else if(value_to_optimise == 'P') cond = Priority[opt_index] < Priority[j];
					else if(value_to_optimise == 'H') cond = ResponseRatio(opt_index, prev_index) < ResponseRatio(j, prev_index);
					
					if(opt_index == -1 || cond) opt_index = j;
				}
				if(BT_temp[j] >= 0 && AT[least_at_index] > AT[j]) 
				{
					least_at_index = j;
				} 
			}
			if(opt_index == -1)
			{
				BT_temp[least_at_index] = -1;

				CT[least_at_index] = AT[least_at_index] + BT[least_at_index];

				TAT[least_at_index] = CT[least_at_index] - AT[least_at_index];
				WT[least_at_index] = TAT[least_at_index] - BT[least_at_index];

				prev_index = least_at_index;
			}
			else
			{
				BT_temp[opt_index] = -1;

				CT[opt_index] = CT[prev_index] + BT[opt_index];

				TAT[opt_index] = CT[opt_index] - AT[opt_index];
				WT[opt_index] = TAT[opt_index] - BT[opt_index];

				prev_index = opt_index;
			}
		}
	}

	//Display
	Display();
}

void SchedulerAlgos::Evaluate_RoundRobin()
{
	if(size_of_queue > 0)
	{
		SSort();
		
		int ready_queue_index[size_of_queue];
		int ready_queue_size = 0;
	
		int BT_temp[size_of_queue];
		for(int i=0;i<size_of_queue;i++)
		{
			BT_temp[i] = BT[i];
			ready_queue_index[i] = -1;
		} 

		int no_completed = 0;
		int cur_time = AT[0];
		
		ready_queue_index[0] = ready_queue_size;
		ready_queue_size++;

		int proc_end_time = 0;
		
		//cout<<"\nCURRENT PID: "<<PID[prev_index]<<", AT: "<<AT[prev_index]<<", BT: "<<BT_temp[prev_index]<<", CT: "<<CT[prev_index]<<endl;
		
		while(no_completed < size_of_queue)
		{
			
			cur_time++;
			proc_end_time++;

			cout<<"Time: "<<cur_time<<endl;
			
			// FIND NEW ARRIVALS

			cout<<"READYQUEUE: ";

			for(int j=0;j<size_of_queue;j++)
			{
				if(BT_temp[j] > 0 && AT[j] == cur_time)
				{
					if(ready_queue_index[j] == -1)
					{
						ready_queue_index[j] = ready_queue_size;
						ready_queue_size++;
					} 			
				}
				cout<<"("<<j+1<<" - "<<ready_queue_index[j]<<"), ";
			}

			cout<<endl;

			int no_to_exec = 0;
			for(int ne=0;ne<size_of_queue;ne++)
			{
				if(BT_temp[ne] > 0 && ready_queue_index[ne] >= 0) no_to_exec++;
			}

			if(no_to_exec == 0)
			{
				proc_end_time = 0;
				continue;
			} 

			int least_at_index = -1;
		
			for(int j=0;j<size_of_queue;j++)
			{
				if(BT_temp[j] > 0)
				{
					if(least_at_index == -1) least_at_index = j;
					if(ready_queue_index[j] > -1 && ready_queue_index[j] < ready_queue_index[least_at_index])
					{
						least_at_index = j;
					} 
				}
			}
			
			
			// NEXT
		
			BT_temp[least_at_index] = BT_temp[least_at_index] - 1;
			CT[least_at_index] = cur_time;
			 
			if(BT_temp[least_at_index] == 0)
			{
				TAT[least_at_index] = CT[least_at_index] - AT[least_at_index];
				WT[least_at_index] = TAT[least_at_index] - BT[least_at_index];

				no_completed++;
				
				ready_queue_index[least_at_index] = -2;
				
				proc_end_time = 0;
			}
			else 
			{
				if((proc_end_time) % tq == 0)
				{
					if(ready_queue_index[least_at_index] != -2)
					{
						ready_queue_index[least_at_index] = ready_queue_size;
						ready_queue_size++;
					}
					proc_end_time = 0;
				}
			}

		}
	}

	//Display
	Display();
}

void SchedulerAlgos::Evaluate_FCFS()
{
	if(size_of_queue > 0)
	{
		SSort();

		CT[0] = AT[0] + BT[0];
		TAT[0] = CT[0] - AT[0];
		WT[0] = TAT[0] - BT[0];

		for(int i=1;i<size_of_queue;i++)
		{
			if(AT[i] > CT[i-1])
			{
				CT[i] = AT[i] + BT[i];
			}
			else 
			{
				CT[i] = CT[i-1] + BT[i];
			}

			TAT[i] = CT[i] - AT[i];
			WT[i] = TAT[i] - BT[i];
		}

		//Display
		Display();
	}
}
// --------------------------------------------------------------------------------------

