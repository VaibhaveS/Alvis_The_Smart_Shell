#include <bits/stdc++.h>
#include <unistd.h> // for sleep()
#include <cmath>
using namespace std;
int main() {
  //PAS
   cout<<"Enter Physcial addr space in MB\n";
   int ps;
   cin>>ps;
  // ps=256;
   cout<<"Enter Logical addr space in GB\n";
   int ls;
   cin>>ls;
   //ls=4;
   cout<<"Enter frame size in KB\n";
   int fs;
   cin>>fs;
   //fs=4;
   int offset_b=fs*1024;
   int offset_bits=ceil(log2(offset_b));
   
   int total_memory_bits=20+(ceil(log2(ps)));
   
   int f_no_bits=total_memory_bits-offset_bits;
   
   int f_total=1<<f_no_bits;
   
   cout<<"Total number of frames are "<<f_total<<"\n";
   cout<<"Size of every frame is "<<fs<<"\n";
   cout<<"total size is "<<ps<<"\n";
   sleep(0.5);
   cout<<"\n\n";
   //LAS
   //process divided into pages
   cout<<"PAGE SIZE = FRAME SIZE\n";
   int page_bits=offset_bits;
   
   int total_logical_bits=30+(ceil(log2(ls)));
   
   int p_no_bits= total_logical_bits-page_bits;
   
   int p_total=1<<p_no_bits;
   
   cout<<"Total number of pages are "<<p_total<<"\n";
   cout<<"Size of every page is "<<fs<<"\n";
   cout<<"total size is "<<ls<<"\n";
      sleep(0.5);
   cout<<"\n\n";
   //PAGE TABLE
   //no of entries is same as #pages
   int no_entries=p_total;
   //in page table we give frame no for every page , total frames are f_total and f_no_bits would be the entry size
   int page_table_entry_bits = f_no_bits;
   cout<<"Page table entry size is "<< f_no_bits/8 <<" Bytes\n";
   
   int page_size=no_entries*(f_no_bits) /8;
   cout<<"Since "<<page_size<<" B is greater than "<<fs<<" KB, we can't fit the page table into the main memory frame...\n";
   cout<<"So now we need to divide the page table...\n";
   
   int divide=page_size / (fs * (1<<10));
   cout<<"Inner page table divided into "<<divide<<" entries\n";
   
   cout<<"Total number of entries in outer page table are "<<divide<<"\n";
   int out_page_table_entry_bits = f_no_bits;
   cout<<"Outer Page table entry size is "<< divide*f_no_bits/8 <<" Bytes\n";
   cout<< divide*f_no_bits/(8*(1<<10)) <<" KB is less than "<<fs<<" KB..hence this arragement fits well\n";
   
   cout<<"LAS \n";
   cout<<"TOTAL "<<total_logical_bits<<"\n";
   cout<<"OUTER PAGE TABLE "<<ceil(log2(divide))<<"\n";
   cout<<"INNER PAGE TABLE "<<total_logical_bits-ceil(log2(divide))-page_bits<<"\n";
   cout<<"PAGE OFFSET "<<page_bits<<"\n";
   	sleep(4);
	   
      	cout << "\n\nPress Enter to Continue";
	   cin.ignore();
	      system("clear");
   cout<<"Enter the logical address...";
   int log;
   cin>>log;
   //log=1073741824+(1<<16)+(1<<5);
   cout<<"Since the first "<<ceil(log2(divide))<<" bits point to the location in the outerpage table, we extract it...";
   int no=0,i=0,x=0; 
   string s="→ ";
   cout<<"\n\n";
   for(int i=31;i>=0;i--) {
   	if(log&(1<<i)) s+="1";
   	else s+="0";
   	x++;
   	if(x==ceil(log2(divide))) s+=" ← ";
   }
   x=0;
   cout<<"\t\t\t\t\t"<<s<<"\n";
   for(int i=32-ceil(log2(divide));i<32;i++) {
   	if(log&(1<<i)) {
   	   no|=1<<x;
   	}
   	x++;
   }
   cout<<"outer page pointer is "<<no<<"\n";
   cout<<"\t\t\t\t┏━━━━━━┓"<<0<<"\n";
   cout<<"\t\t\t\t┗━━━━━━┛\n";
   cout<<"\t\t\t\t┏━━━━━━┓"<<1<<"\n";
   cout<<"\t\t\t\t┗━━━━━━┛\n";
   cout<<"\t\t\t\t  ...    \n";
   cout<<"\t\t\t\t┏━━━━━━┓"<<no<<" →  "<<"\n";
   cout<<"\t\t\t\t┗━━━━━━┛\n";
   cout<<"\t\t\t\t  ...    \n";
   cout<<"\t\t\t\t┏━━━━━━┓"<<divide-1<<"\n";
   cout<<"\t\t\t\t┗━━━━━━┛\n";
   int prev_no=no;
   sleep(5);
         	cout << "\n\nPress Enter to Continue";
	   cin.ignore();
   system("clear");
   s="";
   cout<<"\n\n";
   x=0;
   for(int i=31;i>=0;i--) {
   	if(log&(1<<i)) s+="1";
   	else s+="0";
   	x++;
   	//cout<<x<<" "<<ceil(log2(divide))<<"\n";
   	if(x==ceil(log2(divide))) s+=" → ";
   	if(x== ceil(log2(divide))+total_logical_bits-ceil(log2(divide))-page_bits) s+=" ← ";
   }
   x=0,no=0;
   cout<<"\t\t\t\t\t"<<s<<"\n";
   for(int i=32-ceil(log2(divide))-page_bits;i<32-ceil(log2(divide));i++) {
   	if(log&(1<<i)) {
   	   no|=1<<x;
   	}
   	x++;
   }
   int hm=total_logical_bits-ceil(log2(divide))-page_bits;
   //cout<<hm<<"\n";
   cout<<"inner page pointer is "<<no<<"\n";
   cout<<"\t\t\t\t         "<<"\t┏━━━━━━┓"<<0<<"\n";
   cout<<"\t\t\t\t         "<<"\t┗━━━━━━┛\n";
   cout<<"\t\t\t\t         "<<"\t┏━━━━━━┓"<<1<<"\n";
   cout<<"\t\t\t\t         "<<"\t┗━━━━━━┛\n";
   cout<<"\t\t\t\t         "<<"\t"<<"\n";
   cout<<"\t\t\t\t  ...    "<<"\t  ... \n";
   cout<<"\t\t\t\t┏━━━━━━┓"<<prev_no<<" →  "<<"\t┏━━━━━━┓"<<no<<" → \n";
   cout<<"\t\t\t\t┗━━━━━━┛"<<"\t┗━━━━━━┛\n";
   cout<<"\t\t\t\t  ...    "<<"\t  ...\n";
   cout<<"\t\t\t\t         "<<"\t┏━━━━━━┓"<<((1<<hm) -1)<<"\n";
   cout<<"\t\t\t\t         "<<"\t┗━━━━━━┛\n";
   
   cout<<"\nNow we travel to the memory location pointed by the inner page table..";
      	cout << "\n\nPress Enter to Continue";
	   cin.ignore();
   system("clear");
   s="";
   cout<<"\n\n";
   x=0;
   for(int i=31;i>=0;i--) {
   	if(log&(1<<i)) s+="1";
   	else s+="0";
   	x++;
   	//cout<<x<<" "<<ceil(log2(divide))<<"\n";
   	if(x== ceil(log2(divide))+total_logical_bits-ceil(log2(divide))-page_bits) s+=" → ";
   }
   s+=" ← ";
   x=0,no=0;
   cout<<"\t\t\t\t\t"<<s<<"\n";
   for(int i=0;i<32-hm-ceil(log2(divide));i++) {
   	if(log&(1<<i)) {
   	   no|=1<<x;
   	}
   	x++;
   }
   hm=32-hm-ceil(log2(divide));
   cout<<"Offset in main memory is "<<no<<"\n";
   cout<<"\t\t\t\t"<<"┏━━━┓┏━━━┓..┏━━━┓..┏━━━┓\n";
   cout<<"\t\t\t\t"<<"  d1   d2    d"<<no<<"   d"<<((1<<hm)-1)<<"\n";
   cout<<"\t\t\t\t"<<"┗━━━┛┗━━━┛..┗━━━┛..┗━━━┛\n";
   cout<<"\t\t\t\t"<<" 0     1      "<<no<<"    "<<((1<<hm)-1)<<"\n";
   return 0;
   }
