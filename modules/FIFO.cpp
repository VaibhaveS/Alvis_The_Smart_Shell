#include<bits/stdc++.h>
#include<unistd.h>
#include<cmath>

using namespace std;



int main() {
	cout<<"\nWelcome to FIFO Page replacement algorithm\n";
	cout<<"\nMax size of memory is 5\n";
	cout<<"\nEnter any positive number for referencing page number and -1 to exit\n";
	vector<int> mem(5, -1);
	queue<int> q;
	int page_faults = 0, total = 0;
	int ch = 0;
	while(ch != -1) {
		cout<<"\nEnter Page number: ";
		cin>>ch;
		if(ch == -1)
			break;
		total++;
		int flag = 0;
		cout<<"\nMEMORY BUFFER:\n";
		for(int i = 0; i < 5; i++) {
			if(mem[i] == -1)
				cout<<"NULL |";
			else
				cout<<mem[i]<<"|";
			if(mem[i] == ch)
				flag = 1;
		}
		if(flag == 1) {
			cout<<"\nPage Hit\n";
			cout<<"\n";
			sleep(5);
			system("clear");
			continue;
		}
		cout<<"\nPage miss\n";
		page_faults++;
		int flag1 = 0;
		for(int i = 0; i < mem.size(); i++) {
			if(mem[i] == -1) {
				cout<<"\nFree slot found\n";
				mem[i] = ch;
				q.push(i);
				flag1 = 1;
				break;
			}
		}
		if(flag1 == 0) {
			cout<<"\nFree slot not found\n";
			cout<<"\nFIFO is used.\n";
			int ind = q.front();
			q.pop();
			mem[ind] = ch;
			q.push(ind);
		}
		for(int i = 0; i < 5; i++) {
			if(mem[i] == -1)
				cout<<"NULL |";
			else
				cout<<mem[i]<<"|";
		}
		cout<<"\n";
		sleep(5);
		system("clear");
	}
	cout<<"PAGE FAULTS : "<<page_faults<<"\n";
  cout<<"TOTAL NUMBER OF MEMORY CALLS : "<<total<<"\n";
  cout<<"ACCURACY : "<<((double)(total-page_faults)/total)*100<<"\n";
}
