#include <bits/stdc++.h>
#include <unistd.h> // for sleep()
using namespace std;
struct Process {
	int pid; // Process ID
	int bt; // Burst Time
	int art; // Arrival Time
};
int calculate(string s,Process p) {
    stack<int> myStack;
    char sign = '+';
    int res = 0, tmp = 0;
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i]=='X' or s[i]=='Y' or s[i]=='Z'){
            
            int value=0;
            if(s[i]=='X') value=p.pid;
            else if(s[i]=='Y') value=p.bt;
            else value=p.art;
            //cout<<value<<"\n";
            tmp = 10*tmp + value;
            
	}
        if (!(s[i]=='X' or s[i]=='Y' or s[i]=='Z') && !isspace(s[i]) || i == s.size()-1) {
            if (sign == '-')
                myStack.push(-tmp);
            else if (sign == '+') {
                myStack.push(tmp);
            }
            else {
                int num;
                if (sign == '*' )
                    num = myStack.top()*tmp;
                else
                    num = myStack.top()/tmp;
                myStack.pop();
                myStack.push(num);
            } 
            sign = s[i];
            tmp = 0;
        }
    }
    while (!myStack.empty()) {
        res += myStack.top();
        myStack.pop();
    }
    //cout<<"RES "<<res<<"\n";
    return res;
}
void findTurnAroundTime(vector<Process> &proc,int n,vector<int> &wt, vector<int> &tat){
	for (int i = 0; i < n; i++)
		tat[i] = proc[i].bt + wt[i];
}
struct cmp{ 
   bool operator()(pair<int,Process> &s1, pair<int,Process> &s2)
   {
      return s1.first < s2.first;
   }
};
void findWaitingTime(vector<Process> &proc, int n,vector<int> &wt,map<int,pair<int,int>> &info)
{
	cout<<"Preemptive - 0/1\n";
	int pre=1;
    cin>>pre;
   // pre=1;
	cout<<"Enter the function in terms of X,Y,Z where X- PID, Y- BT, Z- ART\n";
	string func;
    cin>>func;
    system("clear");
	//func="X+Y*Y";
    //cout<<"Enter 0 if the process with lowest value of the function has higher priority\n";
	//int ascen;cin>>ascen;
	priority_queue<pair<int,Process>,vector<pair<int,Process>>,cmp> pq;
	int t=0;
	
	if(pre) {
	   int time=0,com=0;
	   while(com<proc.size()){
	   	for(int i=0;i<proc.size();i++) {
	   	    if(proc[i].art == time) {  
	   	    cout<<"Process "<<proc[i].pid<<" is pushed into the ready queue\n";
	   	    pq.push({calculate(func,proc[i]),proc[i]});
	   	    }
		}
           if(pq.empty()){
               time++;
               continue;
           }
		auto x=pq.top();
		cout<<"AT TIME: "<<time<<"\n";
		cout<<"\nProcess "<<x.second.pid<<" is picked\n";	
		pq.pop();
           x.second.bt--;
           

           //cout<<x.second.bt<<" \n";
                  
		if(x.second.bt==0) {
			cout<<"\n\nProcess "<<x.second.pid<<" has finished execution..\n";
			com++;
			
			
			cout<<"\nFinish time "<<time+1<<"\n";
			int finish_time = time + 1;
                       
            // if(time==-1) {
            //     cout<<proc.size();
            //     return;
            // }
			// Calculate waiting time
			wt[x.second.pid] = finish_time -
						info[x.second.pid].first -
						info[x.second.pid].second;
            
            
			if (wt[x.second.pid] < 0)
				wt[x.second.pid] = 0;
            
			cout<<"Waiting time "<<wt[x.second.pid]<<"\n\n";		
          //  if(time==3) return;
		}
        else {
            pq.push({x});
        }
		time++;
		cout << "\n\nPress Enter to Continue";
	   cin.ignore();
	   	system("clear");
         //return;
        }
	}
	else {
	    int time=0,com=0;
        vector<int> vis(n+1);
	   while(com<proc.size()){
	   	for(int i=0;i<proc.size();i++) {
	   	    if(proc[i].art <= time and !vis[proc[i].pid]) {
                vis[proc[i].pid]=1;
	   	    cout<<"Process "<<proc[i].pid<<" is pushed into the ready queue\n";
	   	    pq.push({calculate(func,proc[i]),proc[i]});
	   	    }
		}
           if(pq.empty()){
               time++;
               continue;
           }
		auto x=pq.top();
		cout<<"AT TIME: "<<time<<"\n";
		cout<<"Process "<<x.second.pid<<" is picked\n";	
		pq.pop();
           x.second.bt=0;
           

           //cout<<x.second.bt<<" \n";
                  
		if(x.second.bt==0) {
			cout<<"Process "<<x.second.pid<<" has finished execution..\n";
			com++;
			
			
			cout<<"\nFinish time "<<time+info[x.second.pid].first<<"\n";
			int finish_time = time + info[x.second.pid].first;
                       
			// Calculate waiting time
			wt[x.second.pid] = finish_time -
						info[x.second.pid].first -
						info[x.second.pid].second;
            
            
			if (wt[x.second.pid] < 0)
				wt[x.second.pid] = 0;
            
			cout<<"Waiting time "<<wt[x.second.pid]<<"\n\n";		
          //  if(time==3) return;
		}
		cout << "\nPress Enter to Continue";
	   cin.ignore();
		time+=info[x.second.pid].first;
		system("clear");
         //return;
        }
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
   int q=3;
  cout<<"Welcome! You are free to create your own algorithm here! \n";
  cout<<"Enter the number of processes\n";
  int p=2;
    map<int,pair<int,int>> info;
  vector<Process> proc;
  for(int i=0;i<p;i++){
     struct Process obj;
     cout<<"Enter the Process ID\n";
     int pid=i+1;
     obj.pid=pid;
     cout<<"Enter the burst and arrival time for Process "<<pid<<"\n";
     int bt,art;
     if(i==0){
       bt=2;
       art=1;
      }
      else {
      	bt=1;
      	art=2;
      }
     obj.bt=bt,obj.art=art;
     proc.push_back(obj);
      info[pid]={bt,art};
  } 
  system("clear");
  findavgTime(proc,proc.size(),info);
 // system("clear");
  return 0;
}

