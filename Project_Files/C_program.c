#include<stdio.h>
#include "unistd.h"
#include "stdlib.h"
#include "sys/wait.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  char word[20];
  printf("Enter the word you're searchign for: ");
  scanf("%s", word);
	pid_t pid;
	int fd[2]; //fileDecriptor for read(0) & write(1)
	char* cat_arguments[] = {"cat", "roshei.txt", NULL};
	char* grep_arguments[] = {"grep", word, NULL};
	pipe(fd); //add vals of FD to main's File Table
	pid = fork();
	if(pid==0){ //sucessfully created a child process
	        close(1); //close stdout
		dup(fd[1]); 
		close(fd[0]); //otherwise program will keep trying to read 
		execvp("cat", cat_arguments);
	}
	pid = fork();
	if(pid==0){ 
		close(0);
		close(fd[1]);
		dup(fd[0]);
		execvp("grep", grep_arguments);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return 0;
}
