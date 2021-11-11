
        /**
         * After reading user input, the steps are:
         * (1) fork a child process
         * (2) the child process will invoke execvp()
         * (3) if command did not include &, parent will invoke wait()
       */


#include<iostream>
#include<vector>
#include <sys/wait.h>
#include <regex> 
#include<algorithm>
#include <unistd.h>
#include<stdio.h>
#include <map>
#include <deque>
#include <cstring>
using namespace std;
#define BUFFER_SIZE 10

vector<string> dp{"open .c","show directory","make new directory"};
vector<string> actual{"cat","ls","mkdir"};

deque<string> buffer_queue;

int minDistance(string &word1, string &word2) {
        int n=word1.length(),m=word2.length();
        vector<vector<int>> dp(n+1,vector<int>(m+1));
        for(int i=1;i<=n;i++){
            dp[i][0]=i;
        }
        for(int i=1;i<=m;i++){
            dp[0][i]=i;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(word1[i-1]==word2[j-1]) {
                    dp[i][j]=dp[i-1][j-1];
                }
                else {
                    dp[i][j]=1+min({dp[i-1][j],dp[i][j-1],dp[i-1][j-1]});
                }
            }
        }
        return dp[n][m];
}

string parse_file_name(vector<string> &arguments){ 
 	regex regexp("([a-zA-Z0-9\\s_\\.\\-\\(\\):])+(.doc|.docx|.pdf|.c|.cpp|.py)$"); 
    // flag type for determining the matching behavior (in this case on string objects)
    for(auto &input:arguments){
     	if(regex_match(input,regexp)){
     		return input;
     	}
  	}
    return "";
}

vector<string> convert(string &argument){
  int pts=1e5,best=-1;
  for(int i=0;i<dp.size();i++){
      if(minDistance(dp[i],argument) < pts){
        pts=minDistance(dp[i],argument);
        best=i;
      }
  }
  if(best==-1) return {};
  else {
  	return {actual[best]};
  }
  return {};
}

vector<string> split_line(string &cmd_line){
	vector<string> arguments;
	const int n=cmd_line.length();
	string argument="";
	for(int i=0;i<n;){
		while(i<n and cmd_line[i]==' ') i++;
		argument="";
		while(i<n and cmd_line[i]!=' ') {
			argument+=cmd_line[i];
			i++;
		}
		arguments.push_back(argument);	
	}
	return arguments;
}


void remove_from_buffer(){
	if(!buffer_queue.empty()) buffer_queue.pop_back();
}

void update_buffer(vector<string> &argument){
	if(buffer_queue.size()==BUFFER_SIZE) remove_from_buffer();
	string command="";
	for(auto &x:argument) {
		command+=x;
		command+=" ";
	}
	buffer_queue.push_back(command);
}

void print_history() {
	deque<string> dq=buffer_queue;
	cout<<dq.size()<<"\n";
	while(!dq.empty()){
		cout<<dq.front()<<"\n";
		dq.pop_front();
	}
}

enum Mode { Normal, Newbie };

int main(void) {
  	
  	string cmd_line;
    int should_run = 1;
    printf("Alvis!, the smart shell\n");
    printf("New to shell?, enter 'newbie' to toggle newbie mode...\n");
	Mode mode=Normal;
	
    while (should_run) {   
    
        printf("alvis>");
        fflush(stdout);
      //  buffer_queue.push_back("gg");
    	cout<<buffer_queue.size()<<"\n";    
    	
        pid_t pid;
       
        getline(cin, cmd_line);
        vector<string> arguments = split_line(cmd_line);
        const int n=arguments.size();
        
        bool need_to_wait = true;
        if(arguments[n-1]=="&") {
            need_to_wait = false;
        } 
        
        vector<string> keywords{"exit","newbie","history","roundrobin","SJF","FCFS","priority","STRF","Paging_one_level",
        "Paging_two_level","LRU","FIFO","NEXT_FIT","FIRST_FIT","BEST_FIT"};
        map<string,int> hash;
        for(int i=1;i<=keywords.size();i++){
        	hash[keywords[i-1]]=i;
        }
        
        if(mode==Normal) {
		    switch(hash[arguments[0]]) {
		    	case 0: 
		    			pid = fork();
				  	    if(pid<0) {
							printf("FORK FAILED\n");
							return 1;
						} 
						else if(pid==0) {
						 	char *a[arguments.size()+1];
						 	int i=0;
							for(auto &x:arguments) {
								char *path_array=&x[0];
								a[i]=path_array;
								i++;
							}
							a[i]=NULL;
							update_buffer(arguments);
							if(execvp(a[0],a)) {
								  printf("INVALID COMMAND\n");
								  remove_from_buffer();
								  return 1;
							}
						} 
						else {
							if(need_to_wait) {
								while(wait(NULL) != pid);
							}
							else {
								printf("[1]%d\n",pid);
							}
						}
						break;
		    	case 1: return 0;
		    			break;
		    	case 2: mode=Newbie;
		    			break;
		    	case 3: print_history();
		    			break;
		    	default:
		    			printf("Visualize with alvis!\n");
		    			pid = fork();
				  	    if(pid<0) {
							printf("FORK FAILED\n");
							return 1;
						} 
						else if(pid==0) {
							string path="./"+arguments[0];
							char path_array[path.length()];
							strcpy(path_array,path.c_str());
						 	char *a[]={path_array,NULL};
						 	update_buffer(arguments);
							if(execvp(a[0],a)) {
								  printf("INVALID COMMAND\n");
								  remove_from_buffer();
								  return 1;
							}
						} 
						else {
							if(need_to_wait) {
								while(wait(NULL) != pid);
							}
							else {
								printf("[1]%d\n",pid);
							}
						}
		    	}
		    }
		   	else {
		       vector<string> new_arguments=convert(arguments[0]);
		       new_arguments.push_back(parse_file_name(arguments));
		       arguments=new_arguments;
		       char *a[arguments.size()+1];
			   int i=0;
			   for(auto &x:arguments) {
					char *path_array=&x[0];
					a[i]=path_array;
					i++;
				}
				a[i]=NULL;
		      	cout<<"hai, the command you are looking for is "<<arguments[0]<<"\n";
		      	sleep(3);
		      	cout<<"this time, we have executed it for you! use "<<arguments[0]<<" "<<arguments[arguments.size()-1]<<" next time!\n";
		       	sleep(3);
		       	printf("Response for the above command\n");
		       	sleep(1);
		       	update_buffer(arguments);
		        if(execvp(a[0],a)) {
					printf("INVALID COMMAND\n");
					remove_from_buffer();
					return 1;
				}
			
        	}
        }
	return 0;
}
