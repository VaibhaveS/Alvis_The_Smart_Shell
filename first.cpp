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
	int mem,hol,np;
	char t;
	cout<<"Enter The Number Of Blocks"<<"\n";
	cin>>hol;
		int h1[hol];
	cout<<"Enter The Block Sizes"<<"\n"; 
	for(int i=0;i<hol;++i) 
	cin>>h1[i];	
	cout<<"Enter The Number Of Processes"<<"\n"; 
	cin>>np;
	int p1[np];
		//cout<<"↑";	
	cout<<"Enter The Process sizes"<<"\n";
	for(int i=0;i<np;++i) cin>>p1[i];	
	cout<<"\n";
	cout<<"First Fit"<<"\n";
	
	cout<<"\n";
        t=getchlin();
	t=getchlin();
	for(int i=0;i<np;++i)
	{
		int gg=0;
		int l=0;
		for(int j=0;j<hol;++j)
		{   
		    
		    system("clear");
			if(p1[i]!=INT_MAX && p1[i]<=h1[j])
			{   
			     gg=1;
				h1[j]=h1[j]-p1[i];
				p1[i]=INT_MAX;
				cout<<"Process "+to_string(i)+" Goes To Block "+to_string(j)<<"\n";
				cout<<"\n";
				l=j;
				break;
			}
		}
		if(gg=0)
		{
		  cout<<"Process "+to_string(i)+" Doesn't Fit In Any Block "<<"\n";
		  cout<<"\n";
		}
		else
		{
	          for(int v=0;v<l;++v)
	          cout<<"     ";
	          cout<<"↓"<<"\n";
		}
		
		for(int j=0;j<hol;++j) cout<<h1[j]<<" | ";
		t=getchlin();
	}
	system("clear");
	cout<<"Fragmentation For Each Block"<<"\n";
	for(int i=0;i<hol;++i)
	cout<<"Block "+to_string(i)+" Remaining Space : "+to_string(h1[i])<<"\n";
	int flag=0,sm=0;
	for(int i=0;i<np;++i) if(p1[i]!=INT_MAX) flag=1;
	if(flag==1)
	{
	cout<<"Not All Processes Are Allocated "<<"\n";	
	}
  	for(int i=0;i<hol;++i)
  	sm += h1[i];
  	cout<<"Total Remaining Memonry Space is "<<sm<<"\n";
  	cout<<"\n";
}
