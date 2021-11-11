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
scanf("%c",&c);
return (c);
}
int main()
{
	int n,x,time=0,total=0,flag=0,start=0,flag1=0;
	string v;
	char t;
	vector<int> arrival,burst,priority;
    	unordered_map<string, int> a,b,c,comp;     
	vector<string> process,gantt,visited;
	int pv[100]={0};
	cout<<"Enter the total no of proccesses"<<"\n";
	cin>>n;
	cout<<"Enter The Processes"<<"\n";
	for(int i=0;i<n;++i)
	{
		cin>>v;
		process.push_back(v);
	}
	cout<<"Enter The Arrival Times"<<"\n";
	for(int i=0;i<n;++i)
	{
		cin>>x;
		arrival.push_back(x);
		a["P"+to_string(i+1)]=x;		
	}
	cout<<"Enter The Burst Times"<<"\n";
	for(int i=0;i<n;++i)
	{
		cin>>x;
		burst.push_back(x);
		b["P"+to_string(i+1)]=x;		
	}
	cout<<"Enter The Priority"<<"\n";
	for(int i=0;i<n;++i)
	{
		cin>>x;
		priority.push_back(x);
		c["P"+to_string(i+1)]=x;
	}
	int index=0,temp=0;	
	while(total!=n)
	{
		for(int i=0;i<n;++i)
		if(arrival[i]<=time && pv[i]!=1 )
		{   
		   pv[i]=1;
           	   visited.push_back(process[i]);
    		}
        system("clear");
        if(flag1==0)
        {
        t=getchlin();
        flag1=1;
        }	    
        cout<<"List of Processes in the Ready Queue"<<"\n";
	cout<<"------------------------------------\n";
	for(int i=0;i<visited.size();++i) cout<<visited[i]<<" | ";  	
	cout<<"\n------------------------------------\n";  
	cout<<"\n";
        cout<<"Process in the Running Queue"<<"\n";
	cout<<"------------------------------------\n";
	for(int i=0;i<gantt.size();++i) cout<<gantt[i]<<" | ";  	
	cout<<"\n------------------------------------\n";  
	cout<<"\n";
	t=getchlin();
	if(start==0)
	{				 		 
        if(gantt.size()==0)
        {
        string ans;
	int val=INT_MAX;		   	
        for(int j=0;j<visited.size();++j)
        {
            if(c.at(visited[j])<val)
		    {
				ans=visited[j];
				val=c.at(visited[j]);
				index=j;
			} 
	}
	string ll=visited[index];
	visited.erase(visited.begin()+index);
	gantt.push_back(ans);
	system("clear");
	cout<<"Since the Running Queue Is Empty , Process With Least Priority "+ll+" Selected From The Ready Queue"<<"\n\n";	
	cout<<"List of Processes in the Ready Queue"<<"\n";
	cout<<"------------------------------------\n";
	for(int i=0;i<visited.size();++i) cout<<visited[i]<<" | ";  	
	cout<<"\n------------------------------------\n";  
	cout<<"\n";
        cout<<"Process in the Running Queue"<<"\n";
	cout<<"------------------------------------\n";
	for(int i=0;i<gantt.size();++i) cout<<gantt[i]<<" | ";  	
	cout<<"\n------------------------------------\n";  
	cout<<"\n";
	t=getchlin(); 
	if(flag==0)
	{
	temp=time;
	flag=1;			
	}
	start=1;  
	}
	}
        if((time-temp)==b.at(gantt[0]))
        {
        	++total;
        	comp[gantt[0]]=time;
        	string ll=gantt[0];
        	gantt.erase(gantt.begin());
        	system("clear");
			cout<<"Process "+ll+" Finished Execution Hence It Leaves The Running Queue "<<"\n\n";	
		 	cout<<"List of Processes in the Ready Queue"<<"\n";
			cout<<"------------------------------------\n";
			for(int i=0;i<visited.size();++i) cout<<visited[i]<<" | ";  	
			cout<<"\n------------------------------------\n";  
			cout<<"\n";
        	cout<<"Process in the Running Queue"<<"\n";
			cout<<"------------------------------------\n";
			for(int i=0;i<gantt.size();++i) cout<<gantt[i]<<" | ";  	
			cout<<"\n------------------------------------\n";  
			cout<<"\n";
			t=getchlin();  
		} 
        if(gantt.size()==0 && total!=n)
        {
        string ans;
		int val=INT_MAX;		   	
        for(int j=0;j<visited.size();++j)
        {
            if(c.at(visited[j])<val)
		    {
				ans=visited[j];
				val=c.at(visited[j]);
				index=j;
			} 
		}
		string ll=visited[index];
		visited.erase(visited.begin()+index);
		gantt.push_back(ans);
        temp=time;
        system("clear");
		cout<<"Since the Running Queue Is Empty , Process With Least Priority "+ll+" Selected From The Ready Queue"<<"\n\n";	
		 cout<<"List of Processes in the Ready Queue"<<"\n";
		cout<<"------------------------------------\n";
		for(int i=0;i<visited.size();++i) cout<<visited[i]<<" | ";  	
		cout<<"\n------------------------------------\n";  
		cout<<"\n";
        cout<<"Process in the Running Queue"<<"\n";
		cout<<"------------------------------------\n";
		for(int i=0;i<gantt.size();++i) cout<<gantt[i]<<" | ";  	
		cout<<"\n------------------------------------\n";  
		cout<<"\n";
		t=getchlin();  
		
		}		     
		++time;   
	}

    vector<int> completed;
    vector<int> tat,wt;   
    int TAT_TIME=0,WT_TIME=0;
    int z=0;
    while(z!=n)
    {   
    for (auto x : comp)
    if((x.first).compare("P"+to_string(z+1))==0) completed.push_back(x.second);
    ++z;
    }
	
    for(int i=0;i<n;++i)
    {
    tat.push_back(completed[i]-arrival[i]);
    TAT_TIME += (completed[i]-arrival[i]);
    }
    for(int i=0;i<n;++i)	
    {
    wt.push_back(tat[i]-burst[i]);
    WT_TIME += (tat[i]-burst[i]) ;		
    }
    system("clear");
    cout << "Processes "<< " Burst time "<< " Arrival time " << "Turn around "<< "     Waiting "<< "    Completion \n";
    for(int i=0;i<n;++i)
    {
    	cout << " " << process[i] << "\t\t" << burst[i] <<"\t "<< arrival[i] <<"\t\t " << tat[i]<<"\t\t " << wt[i]<<"\t\t " <<completed[i]<<endl;
     }
    cout<<"\n";
    cout << "Average waiting time = "<< (float)TAT_TIME / (float)n;
    cout << "\nAverage turn around time = "<< (float)WT_TIME / (float)n;
   // for (auto x : comp)
    //  cout << x.first << " " << x.second << endl;
}
	
	

