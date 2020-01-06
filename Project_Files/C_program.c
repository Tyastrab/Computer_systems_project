#include<stdio.h>
#include "unistd.h"
#include "stdlib.h"
#include "sys/wait.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
  char word[20];
  printf("Enter the word you're searchign for: ");
  scanf("%s", word); //word = user's search term
  
  int fd[2]; //File Descriptor, where fd[0]=read & fd[1]=write
  pipe(fd); //set up a pipe between the read and write
  int pid2, pid1 = fork(); //create 2 forks for 2 child processes
  if (pid1 == 0){ //if child is successfully forked:
    close(fd[0]); //close the end of the FD not in use (read in this case)
    dup2(fd[1],1); //tie write end of process to write end of pipe
    execlp("cat","cat","sample.txt",NULL); //perform the cat
  }
  else{
    close(fd[1]); //close the end of the FD not in use (write in this case)
    dup2(fd[0],0); //tie read end of process to read end of pipe 
    execlp("grep","grep",word,NULL); //perform the grep
  }
  close(fd[0]); //close the read/write process
  close(fd[1]);
  wait(NULL);
  wait(NULL);
  return 0;
}
