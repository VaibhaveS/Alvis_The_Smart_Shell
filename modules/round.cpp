#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<unordered_map>
#include <climits>
#include<stdio.h>
using namespace std;  

char getchlin()  
{
char c;
char test;
scanf("%c",&c);
return (c);
}


void Time(string processes[], int n,int bt[], int wt[], int quantum, int tat[])
{
     
    vector<string> gantt;
    char vv;
    int flag=0,flag1=0;
    for(int i=0;i<n;++i)
    gantt.push_back(processes[i]);
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];
  
    int t = 0; 
    while (1)
    {
        bool done = true;
        for (int i = 0 ; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = false; 
  
                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                if(flag==0)
		{
		  system("clear"); 
		  if(flag1==0)
		  {
		  vv=getchlin();
		  flag1=1;
		  }
	          cout<<"Initial Queue : "<<"\n";
		  cout<<"\n";   
		  cout<<"------------------------------------\n";
		  for(int i=0;i<gantt.size();++i) cout<<gantt[i]<<" | ";  	
		  cout<<"\n------------------------------------\n";   
		  vv=getchlin();
		  flag=1;
		}
		string v=gantt[0];
		gantt.erase(gantt.begin());
		gantt.push_back(v);
		system("clear"); 
		cout<<"Process "+v+" Executed For Quantum "+to_string(quantum)+" Hence Removed From Start And Appended To The End Of Queue As Burst Time Not Exhausted "<<"\n";
		cout<<"\n";
		cout<<"------------------------------------\n";
		for(int i=0;i<gantt.size();++i) cout<<gantt[i]<<" | ";  	
		cout<<"\n------------------------------------\n";   				
	        vv=getchlin();
                }
                else
                {
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                    tat[i]=t;
                    string vv=gantt[0];
                    gantt.erase(gantt.begin());
		     system("clear"); 
		     cout<<"Process "+vv+" Has Completed Execution, (Burst Time) Exhausted \n";
		     cout<<"\n";
		     cout<<"------------------------------------\n";
		     for(int i=0;i<gantt.size();++i) cout<<gantt[i]<<" | ";  	
		     cout<<"\n------------------------------------\n";   				
		     vv=getchlin();                
                }
            }
        }
        if (done == true)
          break;
    }
}
  
void findavgTime(string processes[], int n, int bt[],int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    Time(processes, n, bt, wt, quantum, tat);
    system("clear"); 
    cout << "Processes "<< " Burst time "<< " Waiting time " << " Turn around time\n";
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << processes[i] << "\t\t" << bt[i] <<"\t "<< wt[i] <<"\t\t " << tat[i] <<endl;
    }
  
    cout << "Average waiting time = "<< (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "<< (float)total_tat / (float)n;
}
  
int main()
{
    string processes[100];
    int burst_time[100]; 
    int quantum,n;	  
	cout<<"Enter the time quantum"<<"\n"; 
	cin>>quantum;
    cout<<"Enter Total No of Processes"<<"\n";
    cin>>n;
    cout<<"Enter the Processes"<<"\n";
    for(int i=0;i<n;++i)
    {
    	cin>>processes[i];
	}
	cout<<"Enter the Burst Times"<<"\n";
    for(int i=0;i<n;++i)
    {
    	cin>>burst_time[i];
	}	
    findavgTime(processes, n, burst_time, quantum);
    return 0;
}

