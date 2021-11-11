#include <bits/stdc++.h>
#include <unistd.h> // for sleep()
#include <cmath>
using namespace std;

int main() {

   cout<<"Welcome to least recently used page replacement algorithm...\n";
   cout<<"The memory size is 5...\n";
   cout<<"\nEnter any positive integer to represent the page reference number and -1 to EXIT...\n";
   int no;cin>>no;
   vector<int> memory(5,-1);
   vector<int> LRU;
   int page_faults=0,total=0;

   while(no!=-1) {

      total++;
      cout<<"\nMemory BUFFER\n";
      int hit=0;
      for(int x=0;x<5;x++){
         if(!x) cout<<"\t\t\t";
         if(memory[x]==no) hit=1;
        	if(memory[x]==-1) cout<<" NULL | ";
        	else cout<<memory[x]<<" | ";
      }
      cout<<"\n";
      if(hit==1){
         cout<<"PAGE HIT!!!\n";
         for(int x=0;x<5;x++){
            if(memory[x]==no){
          	   LRU.erase(LRU.begin() + x);
          	   break;
            }
         }
      }
      else {
      	cout<<"PAGE MISS\n";
      	int replace=1;
         for(int x=0;x<5;x++){
            if(memory[x]==-1){
               replace=0;
               cout<<"\nFREE SLOT FOUND!!\n";
               memory[x]=no;
               break;
            }
         }
         if(replace==1){
            page_faults++;
            cout<<"\nNo FREE SLOT, LRU is used\n";
            int least_recently_used=LRU[0];
            for(int x=0;x<5;x++){
   	         if(memory[x]==least_recently_used){
   		         memory[x]=no;
   		         break;
               }
            }
         }
      }
      cout<<"\nMemory BUFFER\n";
      for(int x=0;x<5;x++){
         if(!x) cout<<"\t\t\t";
        	if(memory[x]==-1) cout<<" NULL | ";
        	else cout<<memory[x]<<" | ";
      }
      cout<<"\n";
      LRU.push_back(no);
      sleep(2);
      system("clear");
      cout<<"\nEnter any positive integer to represent the page reference number and -1 to EXIT...\n";
      cin>>no;
      
   }

   cout<<"PAGE FAULTS : "<<page_faults<<"\n";
   cout<<"TOTAL NUMBER OF MEMORY CALLS : "<<total<<"\n";
   cout<<"ACCURACY : "<<((double)(total-page_faults)/total)*100<<"\n";
     
   return 0;

}
