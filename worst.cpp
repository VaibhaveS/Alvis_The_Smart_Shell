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
	cout<<"Enter The Number Of Blocks"<<"\n";
	cin>>hol;
	int h3[hol];
	char t;
	cout<<"Enter The Block Sizes"<<"\n"; 
	for(int i=0;i<hol;++i) cin>>h3[i];	
	cout<<"Enter The Number Of Processes"<<"\n"; cin>>np;
	int p3[np];
	cout<<"Enter The Process sizes"<<"\n";
	for(int i=0;i<np;++i) cin>>p3[i];	
	cout<<"\n";
	cout<<"Worst Fit"<<"\n";
	cout<<"\n";	
	t=getchlin();
	t=getchlin();
	int flag=0;	
  	for(int i=0;i<np;++i)
  	{
  	    int in1,in2,val=INT_MIN; 
		flag=0;   
		int l=0;
		system("clear");  		
  		for(int j=0;j<hol;++j)
  		{
  			if(p3[i]!=INT_MAX && p3[i]<=h3[j] && (h3[j]-p3[i]>=val))
  			{
  				in1=i;
  				in2=j;
  				val=h3[j]-p3[i];
  				flag=1;
			}		
		}
		if(flag==1)
		{				
		h3[in2] -= p3[i];
		p3[in1]=INT_MAX;		
		cout<<"Process "+to_string(in1)+" Goes To Block "+to_string(in2)<<"\n";
		l=in2;
		cout<<"\n";
		for(int v=0;v<l;++v)
	        cout<<"     ";
	        cout<<"↓"<<"\n";
		}
		else 
		{
		cout<<"Process "+to_string(i)+" Doesn't Fit In Any Block "<<"\n";
		cout<<"\n";
		}
		for(int j=0;j<hol;++j) cout<<h3[j]<<" | ";
		t=getchlin();			
	}
	cout<<"\n";	
        system("clear");   	
	cout<<"Fragmentation For Each Block"<<"\n";
	for(int i=0;i<hol;++i)
	cout<<"Block "+to_string(i)+" Remaining Space : "+to_string(h3[i])<<"\n";
	flag=0;
	int sm=0;
	for(int i=0;i<np;++i) if(p3[i]!=INT_MAX) flag=1;
	if(flag==1)
	{
	cout<<"Not All Processes Are Allocated "<<"\n";	
	}
  	for(int i=0;i<hol;++i)
  	sm += h3[i];
  	cout<<"Total Remaining Memory Space is "<<sm<<"\n";  	
  	cout<<"\n";
}
