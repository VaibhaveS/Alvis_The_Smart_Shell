#include<bits/stdc++.h>
#include<cmath>
#include<unistd.h>
#include<stdio.h>
using namespace std;


int main() {
	int las, pas, fsize;
	cout<<"\nEnter size of logical address space in GB: ";
	cin>>las;
	cout<<"\nEnter size of physical address space in MB: ";
	cin>>pas;
	cout<<"\nEnter frame size in KB: ";
	cin>>fsize;
	int tot_bits = 20 + ceil(log2(pas));
	int t_bits = 30 + ceil(log2(las));
	int offset = 10 + ceil(log2(fsize));
	int Page_no_bits = t_bits - offset;
	int frame_no_bits = tot_bits - offset;
	int tot_pages = 1<<Page_no_bits;
	int tot_frames = 1<<frame_no_bits;
	cout<<"\nTotal Number of pages are: "<<tot_pages;
	cout<<"\nTotal Number of frames are: "<<tot_frames;
	cout<<"\nTotal Number of bits required for Page Number: "<<Page_no_bits;
	cout<<"\nTotal Number of bits required for Frame Number: "<<frame_no_bits;
	cout<<"\nTotal Number of bits offset: "<<offset;
	cout<<"\n\n";
	sleep(5);
	system("clear");
		int no = 0, x = 0, LA;
	cout<<"Enter the logical address: ";
	cin>>LA;
	//LA = 1048575;
	for(int i = 31 - Page_no_bits; i < 32; i++) {
		if(LA & (1<<i))
			no |= 1<<x;
		x++;
	}
	string s = "";
	int cnt = 0;
	for(int i = 31; i >= 0; i--) {
		if(cnt == Page_no_bits)
			s += "|";
		cnt++;
		if(LA & (1<<i))
			s += "1";
		else
			s += "0";
	}
	cout<<"\n"<<s<<"\n";
	cout<<"Page table pointer is "<<no<<"\n";
   cout<<"\t\t\t\t┏━━━━━━┓"<<0<<"\n";
   cout<<"\t\t\t\t┗━━━━━━┛\n";
   cout<<"\t\t\t\t┏━━━━━━┓"<<1<<"\n";
   cout<<"\t\t\t\t┗━━━━━━┛\n";
   cout<<"\t\t\t\t  ...    \n";
   cout<<"\t\t\t\t┏━━━━━━┓"<<no<<" →  "<<"\n";
   cout<<"\t\t\t\t┗━━━━━━┛\n";
   cout<<"\t\t\t\t  ...    \n";
   cout<<"\t\t\t\t┏━━━━━━┓"<<(1<<Page_no_bits)-1<<"\n";
   cout<<"\t\t\t\t┗━━━━━━┛\n";
   no = 0;
   for(int i = 0; i < offset; i++) {
   	if(LA & (1<<i))
   		no |= (1<<i);
   }
   sleep(5);
   cout<<"\n\n";
   /*cout<<"Press Enter to Continue";
	 cin.ignore();*/
		
	 system("clear");
   cout<<"\n"<<s<<"\n";
	 cout<<"Offset in main memory is "<<no<<"\n";
   cout<<"\t\t\t\t"<<"┏━━━┓┏━━━┓..┏━━━┓..┏━━━┓\n";
   cout<<"\t\t\t\t"<<"  d1   d2    d"<<no<<"   d"<<((1<<offset)-1)<<"\n";
   cout<<"\t\t\t\t"<<"┗━━━┛┗━━━┛..┗━━━┛..┗━━━┛\n";
   cout<<"\t\t\t\t"<<" 0     1      "<<no<<"    "<<((1<<offset)-1)<<"\n";
	return 0;
}
