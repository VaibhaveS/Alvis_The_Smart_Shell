#include<iostream>
#include<vector>
#include<algorithm>
#include <unistd.h>
#include<stdio.h>
#include<climits>

using namespace std;

struct process {
	int pid, at, bt, wt, tt, c;
};

bool compare(process p1, process p2) {
	return p1.at < p2.at;
}

void arrangeArrival(int num, vector<process> &arr) {
    sort(arr.begin(), arr.end(), compare);
}
  
void completionTime(int num, vector<process> &arr) {
    /*int temp, val;
    arr[0].c = arr[0].at + arr[0].bt;
    arr[0].tt = arr[0].c - arr[0].at;
    arr[0].wt = arr[0].tt - arr[0].bt;
      
    for(int i=1; i<num; i++) {
        temp = arr[i - 1].c;
        int low = arr[i].bt;
        for(int j=i; j<num; j++)
        {
            if(temp > arr[j].at && low >= arr[j].bt)
            {
                low = arr[j].bt;
                val = j;
            }
        }
        arr[val].c = temp + arr[val].bt;
        arr[val].tt = arr[val].c - arr[val].at;
        arr[val].wt = arr[val].tt - arr[val].bt;
        swap(arr[val], arr[i]);
    }
   	int i = 1;
   	int min = 0;
   	process p = arr[0];
   	while(arr[i].at == p.at && i < arr.size()) {
   		//cout<<i<<" "<<arr[0].bt<<" "<<arr[i].bt<<"\n";
   		if(arr[i].bt < arr[min].bt) {
   			swap(arr[i], arr[min]);
   			min = i;
   		}
   		i++;
   	}*/
   	int cnt = 0, i = 0, time = arr[0].at, j = 0;
   	vector<process> arr1;
   	vector<int> visited(num, 0);
    while(i < num) {
    	int mn = INT_MAX, mnVal = INT_MAX;
    	//sleep(5);
    	cout << "Press Enter to Continue";
			cin.ignore();
      system("clear");
    	cout<<"\nReady Queue at time "<<time<<"\n\n\t\t";
    	cnt = 0;
    	for(int j = 0; j < num; j++) {
    		if(arr[j].at > time)
    			continue;
    		cout<<arr[j].pid<<" | ";
    		//mnVal = INT_MAX;
    		if( mnVal > arr[j].bt && visited[j] == 0) {
    			mnVal = arr[j].bt;
    			mn = j;
    		}
    	}
    	visited[mn] = 1;
    	cnt = mn;
    	arr1.push_back(arr[mn]);
			cout<<"\n\t\t";
    	for(int k = 0; k < cnt; k++) 
    		cout<<"    ";
    	printf("\u2191");
    	cout<<"\n";
    	time += arr[mn].bt;
    	cout<<"Process "<<arr[mn].pid<<" is chosen as it has the least burst time of "<<arr[mn].bt;
    	cout<<"\n";
    	i++;
    }
    arr = arr1;
}
  
int main() {
    int num, temp;
    system("clear");
    cout<<"\tWELCOME TO VISUALIZATION OF SJF SCHEDULING ALGORITHM\n";
    cout<<"Enter number of Process: ";
    cin>>num;
    vector<process> arr;
    for(int i=0; i<num; i++)
    {
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
    cout<<"\nProcess ID\tArrival Time\tBurst Time\n";
    for(int i=0; i<num; i++) {
        cout<<arr[i].pid<<"\t\t"<<arr[i].at<<"\t\t"<<arr[i].bt<<"\n";
    }  
    sleep(1);
    arrangeArrival(num, arr);
    completionTime(num, arr);
    
    //system("clear");
    arr[0].c = arr[0].at + arr[0].bt;
    arr[0].tt = arr[0].c - arr[0].at;
    arr[0].wt = arr[0].tt - arr[0].bt;
    for(int i = 1; i < num; i++) {
    	arr[i].c = arr[i - 1].c + arr[i].bt;
    	arr[i].tt = arr[i].c - arr[i].at;
    	arr[i].wt = arr[i].tt - arr[i].bt;
    }
    cout<<"\nFinal Result\n";
    cout<<"Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    
    for(int i=0; i<num; i++) {
        cout<<arr[i].pid<<"\t\t"<<arr[i].at<<"\t\t"<<arr[i].bt<<"\t\t"<<arr[i].wt<<"\t\t"<<arr[i].tt<<"\n";
    }
}
