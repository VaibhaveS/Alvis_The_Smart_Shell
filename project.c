


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>



#define MAX_LINE		80 /* 80 chars per line, per command */
char* dp[1]={"open .c"}; //char* , char[] please open lol.c ~9
char* actual[1]={"cat"};
char* history[10][MAX_LINE/2 + 1]; //array which stores the commands
int history_wait[10];
int buffHead = 0; //pointer, which points to the most recent command in the array
int mode=0; //0- normal, 1-newbie
void init_history(void);
void free_history(void);
void print_history(void);
char** history_computation(char** args,int *needWait);
int arr[1024][1024] = {0};
int min_(int a,int b,int c){
	if(a<=b&&a<=c) return a;
	if(b<=a&&b<=c) return b;
	if(c<=a&&c<=b) return c;
}
int minDistance(char *word1, char *word2) { //dp to find the closest match
	int l1 = 0,l2 = 0;
	for(l1 = 0;word1[l1];arr[l1][0] = ++l1);
	for(l2 = 0;word2[l2];arr[0][l2] = ++l2);
	for(int i = 1;i<=l1;i ++)
		for(int j = 1;j<=l2;j ++)
			arr[i][j] = min_(arr[i-1][j-1]+(word1[i-1]!=word2[j-1]),arr[i][j-1]+1,arr[i-1][j]+1);
	return arr[l1][l2];
}
int file_name(char *s){ //returns 1 if s is a filename
	//printf("checking for %s\n",s);
   for(int i=0;i<sizeof(s)/sizeof(s[0]);i++){
 //  printf("chars %c %c\n",s[i],s[i+1]);
      if(s[i]=='.' && i+1 < sizeof(s)/sizeof(s[0]) && s[i+1]=='c') {
    //  	printf("yessss");
      return 1;
      }
   }
   return 0;
}
char* parse_file_name(char **st){ //st="please open lol.c"
    //char parsed[];
    int sz=0,j=0;
    while(st[j]) {
    	j++;
    }
    for(int i=0;i<j;i++){
      //  printf("%d checking for %s\n",i,st[i]);
    	if(file_name(st[i])) { //lol.c
    	   return st[i];	
    	}
    }
    //char *par=parsed;
    //return par;
    return NULL;
}
char* convert(char **args){
  // printf("came %s",args[0]);
  int pts=1e5,best=-1;
  for(int i=0;i<sizeof(dp)/sizeof(dp[0]);i++){
      if(minDistance(dp[i],args[0]) < pts){
        pts=minDistance(dp[i],args[0]);
        best=i;
      }
  }
  if(best==-1) return NULL;
  else {
  	return actual[best];
  }
}
char** fetch_noob(char **st){
    printf("namaste\n");
    for(int i=0;st[i]!=NULL;i++){
        printf("%s\n",st[i]);
    }
}
int main(void)
{
    char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
    int should_run = 1;
	
	/*int i, upper;*/
    printf("Alvis!, the smart shell\n");
    printf("New to shell?, enter 'newbie' to toggle newbie mode...\n");
    init_history();
    while (should_run){   
        printf("alvis>");
        fflush(stdout);
        pid_t pid;
        char cmd_line[MAX_LINE+1];
        char *sptr = cmd_line;
        int av=0;
        if(scanf("%[^\n]%*1[\n]",cmd_line)<1) {
            if(scanf("%1[\n]",cmd_line)<1) {
                printf("STDIN FAILED\n");
                return 1;
            }
            continue;
        }
        //Parse cmd_line
        while(*sptr==' ' || *sptr=='\t')
            sptr++;
        while(*sptr!='\0'){
            char *tempBuff=(char*)malloc((MAX_LINE+1)*sizeof(char));
            args[av]=(char*)malloc((MAX_LINE+1)*sizeof(char));
            int ret = sscanf(sptr,"%[^ \t]",args[av]);
            sptr += strlen(args[av]);
            if(ret<1){
                printf("INVALID COMMAND\n");
                return 1;
            }
            ret = sscanf(sptr,"%[ \t]",tempBuff);
            
            if(ret>0)
                sptr += strlen(tempBuff);
            av++;
            free(tempBuff);
        }
        
        int need_to_wait = 1;
        if(strlen(args[av-1])==1 && args[av-1][0]=='&') {
            need_to_wait = 0;
            free(args[av-1]);
            args[av-1]=NULL;
        } else {
            args[av]=NULL;
        }
        if(strcmp(args[0],"exit")==0){
            free_history();
            return 0;
        }
        //History Computation
	
        if(args[1]==NULL && strcmp(args[0],"newbie")==0){
           mode=1;
           //printf("hello");
           continue;
        }
  	else if(args[1]==NULL && strcmp(args[0],"roundrobin")==0){
  	//printf("ucame");
  	   pid = fork();
  	   if(pid<0) {
            printf("FORK FAILED\n");
            return 1;
           } 
           else if(pid==0) {
         	//printf("executing %s",argsPtr[0]);
         	char *a[]={"./roundrobin",NULL};
            	if(execvp(a[0],a)) {
                    printf("INVALID COMMAND\n");
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
           continue;
  	}
  	else if(args[1]==NULL && strcmp(args[0],"SJF")==0){
  	//printf("ucame");
  	   pid = fork();
  	   if(pid<0) {
            printf("FORK FAILED\n");
            return 1;
           } 
           else if(pid==0) {
         	//printf("executing %s",argsPtr[0]);
         	char *a[]={"./SJF",NULL};
            	if(execvp(a[0],a)) {
                    printf("INVALID COMMAND\n");
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
           continue;
  	}
  	else if(args[1]==NULL && strcmp(args[0],"FCFS")==0){
  	//printf("ucame");
  	   pid = fork();
  	   if(pid<0) {
            printf("FORK FAILED\n");
            return 1;
           } 
           else if(pid==0) {
         	//printf("executing %s",argsPtr[0]);
         	char *a[]={"./FCFS",NULL};
            	if(execvp(a[0],a)) {
                    printf("INVALID COMMAND\n");
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
           continue;
  	}
  	else if(args[1]==NULL && strcmp(args[0],"priority")==0){
  	//printf("ucame");
  	   pid = fork();
  	   if(pid<0) {
            printf("FORK FAILED\n");
            return 1;
           } 
           else if(pid==0) {
         	//printf("executing %s",argsPtr[0]);
         	char *a[]={"./priority",NULL};
            	if(execvp(a[0],a)) {
                    printf("INVALID COMMAND\n");
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
           continue;
  	}
  	else if(args[1]==NULL && strcmp(args[0],"STRF")==0){
  	//printf("ucame");
  	   pid = fork();
  	   if(pid<0) {
            printf("FORK FAILED\n");
            return 1;
           } 
           else if(pid==0) {
         	//printf("executing %s",argsPtr[0]);
         	char *a[]={"./STRF",NULL};
            	if(execvp(a[0],a)) {
                    printf("INVALID COMMAND\n");
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
           continue;
  	}
  	else if(args[1]==NULL && strcmp(args[0],"Paging_one_level")==0){
  	//printf("ucame");
  	   pid = fork();
  	   if(pid<0) {
            printf("FORK FAILED\n");
            return 1;
           } 
           else if(pid==0) {
         	//printf("executing %s",argsPtr[0]);
         	char *a[]={"./level_one_paging",NULL};
            	if(execvp(a[0],a)) {
                    printf("INVALID COMMAND\n");
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
           continue;
  	}
	else if(args[1]==NULL && strcmp(args[0],"Paging_two_level")==0){
  	//printf("ucame");
  	   pid = fork();
  	   if(pid<0) {
            printf("FORK FAILED\n");
            return 1;
           } 
           else if(pid==0) {
         	//printf("executing %s",argsPtr[0]);
         	char *a[]={"./level_two_paging",NULL};
            	if(execvp(a[0],a)) {
                    printf("INVALID COMMAND\n");
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
           continue;
  	}
	else if(args[1]==NULL && strcmp(args[0],"LRU")==0){
  	//printf("ucame");
  	   pid = fork();
  	   if(pid<0) {
            printf("FORK FAILED\n");
            return 1;
           } 
           else if(pid==0) {
         	//printf("executing %s",argsPtr[0]);
         	char *a[]={"./LRU",NULL};
            	if(execvp(a[0],a)) {
                    printf("INVALID COMMAND\n");
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
           continue;
  	}
  	else if(args[1]==NULL && strcmp(args[0],"FIFO")==0){
  	//printf("ucame");
  	   pid = fork();
  	   if(pid<0) {
            printf("FORK FAILED\n");
            return 1;
           } 
           else if(pid==0) {
         	//printf("executing %s",argsPtr[0]);
         	char *a[]={"./FIFO",NULL};
            	if(execvp(a[0],a)) {
                    printf("INVALID COMMAND\n");
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
           continue;
  	}
        if(mode) { //TODO
        //printf("fdf");
           char *st=convert(args);
           char *st2=parse_file_name(args);
         //  printf("file name is %c\n",st2[0]);
           char *argsPtr[3]={st,st2,NULL};
          printf("hai, the command you are looking for is %s\n",st);
          sleep(3);
          printf("this time, we have executed it for you! use %s %s next time!\n",st,st2);
           sleep(3);
           printf("Response for the above command\n");
           sleep(1);
           if(execvp(argsPtr[0],argsPtr)) {
                printf("INVALID COMMAND\n");
                return 1;
            }
           //continue;
        }
        if(args[1]==NULL && strcmp(args[0],"history")==0) {
            print_history();
            continue;
        }
        char **argsPtr = history_computation(args, &need_to_wait);
                //printf("second is %s second is %s third is %s",argsPtr[0],argsPtr[1],argsPtr[2]);
        //Fork child to Execute args
        if(args[1]==NULL && strcmp(args[0],"vis")==0) {
            printf("Visualize with alvis!\n");
            continue;
        }
        pid = fork();
        if(pid<0) {
            printf("FORK FAILED\n");
            return 1;
        } else if(pid==0) {
         //printf("executing %s",argsPtr[0]);
         
            if(execvp(argsPtr[0],argsPtr)) {
                printf("INVALID COMMAND\n");
                return 1;
            }
        } else {
            if(need_to_wait) {
                while(wait(NULL) != pid);
            }
            else {
                printf("[1]%d\n",pid);
            }
        }
        /**
         * After reading user input, the steps are:
         * (1) fork a child process
         * (2) the child process will invoke execvp()
         * (3) if command did not include &, parent will invoke wait()
         */
    }
    
	return 0;
}
char** history_computation(char **args, int *needWait) {
    int i;
  //  if(args[1]==NULL && strcmp(args[0],"vis")==0){
    	//printf("lmao");
    //	return args;
    //}
    if(args[1]==NULL && strcmp(args[0],"!!")==0) {
        if(buffHead>0){
            strcpy(args[0],history[(buffHead-1)%10][0]);
            for(i=1;history[(buffHead-1)%10][i]!=NULL;i++) {
                args[i]=(char*)malloc((MAX_LINE+1)*sizeof(char));
                printf("%s\n",args[i]);
                strcpy(args[i],history[(buffHead-1)%10][i]);
            }
            args[i]=NULL;
            *needWait=history_wait[(buffHead-1)%10];
        } else {
            printf("NO COMMANDS IN HISTORY\n");
            return args;
        }
    } else if(args[1]==NULL && args[0][0]=='!') {
        int idx;
        char *sptr=&(args[0][1]);
        if(sscanf(sptr,"%d",&idx)==1) {
            if(idx>0 && buffHead>idx-1 && idx>buffHead-9) {
                strcpy(args[0],history[(idx-1)%10][0]);
                for(i=1;history[(idx-1)%10][i]!=NULL;i++) {
                    args[i]=(char*)malloc((MAX_LINE+1)*sizeof(char));
                    strcpy(args[i],history[(idx-1)%10][i]);
                }
                args[i]=NULL;
                *needWait=history_wait[(idx-1)%10];
            } else {
                printf("NO SUCH COMMAND IN HISTORY(index out of range)\n");
                return args;
            }
        } else {
            printf("NO SUCH COMMAND IN HISTORY(invalid index)\n");
            return args;
        }
    }
	//adds to the history array
    for(i=0;i<(MAX_LINE/2+1) && history[buffHead%10][i]!=NULL;i++)
        free(history[buffHead%10][i]);
    for(i=0;args[i]!=NULL;i++) {
        history[buffHead%10][i]=args[i];
    }
    history[buffHead%10][i]=args[i];
    history_wait[buffHead%10]=*needWait;
    return history[(buffHead++)%10];
}
void init_history(void) {
    int i,j;
    for(i=0;i<10;i++) {
        for(j=0;j<(MAX_LINE/2+1);j++) {
            history[i][j]=NULL;
        }
        history_wait[i]=0;
    }
}
void free_history(void) {
    int i,j;
    for(i=0;i<10 && i<buffHead;i++) {
        for(j=0;history[i][j]!=NULL;j++) {
            if(history[i][j])
                free(history[i][j]);
        }
    }
}
void print_history(void) {
    int i,j;
    for(i=0;i<10 && i<buffHead;i++) {
        int index;
        if(buffHead>10)
            index=buffHead-9+i;
        else
            index=i+1;
        printf("[%d] ",index);
        for(j=0;history[(index-1)%10][j]!=NULL;j++) {
            printf("%s ",history[(index-1)%10][j]);
        }
        if(history_wait[(index-1)%10]==0) {
            printf("&");
        }
        printf("\n");
    }
}
