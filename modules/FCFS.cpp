#include<iostream>
#include<vector>
#include<algorithm>
#include <unistd.h>
#include<stdio.h>

using namespace std;
 
 
 struct process {
	int pid, at, bt, wt, tt, c;
};

bool compare(process p1, process p2) {
	return p1.at < p2.at;
}

void arrange(vector<process> &arr) {
	sort(arr.begin(), arr.end(), compare);
}

void findWaitingTime(vector<process> &arr, int n) {
    
    for (int  i = 1; i < n ; i++ )
        arr[i].wt = arr[i - 1].bt + arr[i - 1].wt;
}
 

void findTurnAroundTime(vector<process> &arr, int n) {
	for (int  i = 0; i < n ; i++)
		arr[i].tt = arr[i].bt + arr[i].wt;
}
 

void findavgTime(vector<process> &arr, int n){
    findWaitingTime(arr, n);
    findTurnAroundTime(arr, n);
    int total_wt = 0, total_tat = 0;
		int cnt = 0, i = 0, time = arr[0].at;
    while(i < n) {
			cout << "Press Enter to Continue";
			cin.ignore();
      system("clear");
    	cout<<"\nReady Queue at time "<<time<<"\n\n\t\t";
    	for(int j = 0; arr[j].at <= time; j++) {
    		if(j == n)
    			break;
    		cout<<arr[j].pid<<" | ";
    	}
			cout<<"\n\t\t";
    	for(int k = 0; k < cnt; k++) 
    		cout<<"    ";
    	cnt++;
    	printf("\u2191");
    	cout<<"\n";
    	cout<<"Process "<<arr[i].pid<<" is chosen";
    	cout<<"\n";
    	time += arr[i].bt;
    	i++;
    }
    cout<<"Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int  i=0; i<n; i++) {
        total_wt = total_wt + arr[i].wt;
        total_tat = total_tat + arr[i].tt;
        //cout << "   " <<arr[i].pid<< "\t\t" <<arr[i].bt <<"\t    "<<arr[i].wt<<"\t\t  " <<arr[i].tt<<endl;
        cout<<arr[i].pid<<"\t\t"<<arr[i].at<<"\t\t"<<arr[i].bt<<"\t\t"<<arr[i].wt<<"\t\t"<<arr[i].tt<<"\n";
    }
    cout << "Average waiting time = "<< (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "<< (float)total_tat / (float)n<<"\n\n";
}
 

int main() {
    int n;
    system("clear");
    cout<<"\tWELCOME TO VISUALIZATION OF FCFS SCHEDULING ALGORITHM\n";
    cout<<"\nEnter the number of processes: ";
    cin>>n;
    vector<process> arr;
    for(int i=0; i<n; i++) {
		process p;
        cout<<"Process "<<i+1<<"\n";
        cout<<"Enter Process Id: ";
        cin>>p.pid;
        cout<<"Enter Arrival Time: ";
        cin>>p.at;
        cout<<"Enter Burst Time: ";
        cin>>p.bt;
        arr.push_back(p);
    }
    vector<process> arr1 = arr;
    arrange(arr);
    arr[0].wt = 0;
    findavgTime(arr, n);
    return 0;
}
