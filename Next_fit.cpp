#include<bits/stdc++.h>
#include<unistd.h>
#include<cmath>

using namespace std;

void findNextFit(vector<int> jobs, vector<int> block) {
	system("clear");
    cout<<"\n\nNEXT FIT\n";
    int intfrag = 0;
    int prev = -1;
    vector<int> visited(block.size(), 0);
    for(int i = 0; i < jobs.size(); i++) {
    	vector<int> visited1(block.size(), 0);
    	cout<<"\n";
    	for(int j = 0; j < block.size(); j++) 
    		cout<<block[j]<<" | ";
    	int flag = 0;
    	int res = -1;
    	int j = (prev + 1) % block.size();
    	while(visited1[j] == 0) {
    		if(block[j] >= jobs[i]) {
    			flag = 1;
    			res = j;
    			prev = j;
    			visited[j] = 1;
				block[j] -= jobs[i];
				break;
    		}
    		visited1[j] = 1;
    		j = (j + 1) % block.size();
    	}
    	cout<<"\n";
    	if(flag == 0) {
    		cout<<"\nProcess "<<i + 1<<" cannot be allocated\n";
    		continue;
    	}
    	cout<<"\nProcess "<<i + 1<<" is allocated to block "<<res + 1<<"\n";
    	for(int k = 0; k < block.size(); k++) {
    		cout<<block[k]<<" | ";
    	}
    	cout<<"\n";
    	for(int k = 0; k < res; k++) {
    		cout<<"     ";
    	}
    	printf("\u2191");
    	cout<<"\n\nPress Enter to continue\n";
		//sleep(2);
		cin.ignore();
		system("clear");
    }
    for(int i = 0; i < block.size(); i++) {
        if(visited[i] == 1)
        intfrag += block[i];
    }
    cout<<"\nTotal memory wastage is: "<<intfrag<<"\n";  
}

int main() {
    int n;
    cout<<"\nEnter the total number of jobs: ";
    cin>>n;
    vector<int> jobs(n);
    cout<<"\nEnter the jobs: ";
    for(int i = 0; i < n; i++)
        cin>>jobs[i];
    cout<<"\nEnter the number of blocks: ";
    int m;
    cin>>m;
    vector<int> block(m);
    cout<<"\nEnter the block size: ";
    for(int i = 0; i < m; i++)
        cin>>block[i];
    cin.ignore();
    findNextFit(jobs, block);
    return 0;
}



