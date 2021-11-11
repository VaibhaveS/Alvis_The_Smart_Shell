#include <bits/stdc++.h>
#include <unistd.h> // for sleep()
using namespace std;

struct Process {
	int pid; // Process ID
	int bt; // Burst Time
	int art; // Arrival Time
};

void findTurnAroundTime(vector<Process> &proc,int n,vector<int> &wt, vector<int> &tat) {
	for (int i = 0; i < n; i++)
		tat[i] = proc[i].bt + wt[i];
}

void findWaitingTime(vector<Process> &proc, int n,vector<int> &wt) {

	vector<int> rt(n);
	for (int i = 0; i < n; i++)
		rt[i] = proc[i].bt;
	int complete = 0, t = 0, minm = INT_MAX;
	int shortest = 0, finish_time;
	bool check = false;
	while (complete != n) {
		sleep(5);
		system("clear");
	   cout<<"TIME : "<<t<<"\n";
		vector<int> ready;
		int found=0;
		for(int j=0;j<n;j++){
		   if(proc[j].art <=t and rt[j]>0){
		    	ready.push_back(j);
		    }
		}
		if(ready.size()==0) {
		   cout<<"NO process is in the ready queue at the moment\n";
		}
		else {
		   found=1;
		   cout<<"Ready queue "<<"\n";
		   cout<<"------------------------------------\n";
		   for(auto &x:ready){
		      cout<<proc[x].pid<<" | ";
		   }	
		   cout<<"\n------------------------------------\n";
		}
		int mn=INT_MAX,k=0;	
		if(found){
		   sleep(2);
		   system("clear");
		   cout<<"\n let's decide the process to pick on basis of their remaining burst time...\n";
		   while(k < ready.size()) {
		      sleep(2);
		      system("clear");
		      cout<<"Current min : "<<mn<<"\t\t\tReady queue"<<"\n";
		      cout<<"\t\t\t\t------------------------------------\n";
		      cout<<"\t\t\t\t";
		      for(auto &x:ready) {
		         cout<<proc[x].pid<<" | ";
		      }	
		      cout<<"\n\t\t\t\t------------------------------------\n\t\t\t\t";
		      for(int i=0;i<k;i++){
		         cout<<"    ";
		      }
		      cout<<"↑";
		      cout<<"\n\n";
		      if(rt[ready[k]] < mn) {
		      	cout<<rt[ready[k]]<<" < "<<mn<<"\n";
		      	mn=rt[ready[k]];
		      }
		      else {
		        cout<<rt[ready[k]]<<" >= "<<mn<<"\n";
		      }
		      k++;
		}
		for (int j = 0; j < n; j++) {
			if ((proc[j].art <= t) &&
			(rt[j] < minm) && rt[j] > 0) {
				minm = rt[j];
				shortest = j;
				check = true;
			}
		}
		if (check == false) {
		   cout<<"No process is present in the ready queue at time "<<t<<"\n";
			t++;
			continue;
		}
		cout<<"\nThe process with the shortest burst time is "<<proc[shortest].pid<<"\n";
		rt[shortest]--;
		minm = rt[shortest];
		if (minm == 0)
			minm = INT_MAX;
		if (rt[shortest] == 0) {
			cout<<"\n\nProcess "<<proc[shortest].pid<<" has finished execution \n";
			complete++;
			check = false;
			cout<<"\nFinish time "<<t+1<<"\n";
			finish_time = t + 1;           
			// Calculate waiting time
			wt[shortest] = finish_time -
						proc[shortest].bt -
						proc[shortest].art;
			if (wt[shortest] < 0)
				wt[shortest] = 0;
			cout<<"Waiting time "<<wt[shortest]<<"\n\n";
		}
	}
	cout << "\nPress Enter to Continue";
	cin.ignore();
	t++;
	}
}

void findavgTime(vector<Process> &proc, int n,map<int,pair<int,int>> &info){
	vector<int> wt(n+1), tat(n+1);
	int total_wt = 0,total_tat = 0;

	findWaitingTime(proc, n, wt,info);
	findTurnAroundTime(proc, n, wt, tat);

	sleep(1);
	system("clear");
	cout << "Processes "
		<< " Burst time "
		<< " Waiting time "
		<< " Turn around time\n";

	for (int i = 0; i < n; i++) {
		total_wt = total_wt + wt[i+1];
		total_tat = total_tat + tat[i];
		cout << " " << proc[i].pid << "\t\t"
			<< proc[i].bt << "\t\t " << wt[i+1]
			<< "\t\t " << tat[i] << endl;
	}

	cout << "\nAverage waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n<<"\n";
}

int main(){
   
   cout<<"Welcome! You are free to create your own algorithm here! \n";
   cout<<"Enter the number of processes\n";
   int p; cin>>p;
   map<int,pair<int,int>> info;
   vector<Process> proc;

   for(int i=0;i<p;i++) {
	   struct Process obj;
	   cout<<"Enter the Process ID\n";
	   int pid; cin>>pid;
	   obj.pid=pid;
	   cout<<"Enter the burst and arrival time for Process "<<pid<<"\n";
	   int bt,art; cin>>bt>>art;
	   obj.bt=bt,obj.art=art;
	   proc.push_back(obj);
	   info[pid]={bt,art};
   }

   system("clear");
   findavgTime(proc,proc.size());
   
   return 0;
}



