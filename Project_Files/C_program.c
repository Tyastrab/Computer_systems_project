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
  scanf("%s", word);                                  //word = user's search term
  
  int fd[2];                                          //File Descriptor, where fd[0]=read & fd[1]=write
  pipe(fd);                                           //set up a pipe between the read and write
  int pid2, pid1 = fork();                            //create 2 forks for 2 child processes

  if (pid1 < 0 || pid2 <0){                           //if fork fails, it returns -1
    perror("Pipe failed");
    exit(EXIT_FAILURE);
  }
    
  if (pid1 == 0){                                      //if child is successfully forked:
    close(fd[0]);                                      //close the end of the FD not in use (read in this case)
    if (dup2(fd[1],1) <0){                             //dup returns negative value if it fails
      perror("dup fail");
      exit(EXIT_FAILURE);
    }                                                  //dup ties write end of pipe to write end of process
    execlp("cat","cat","sample.txt",NULL);             //run cat
  }
  else{
    close(fd[1]);                                      //close the end of the FD not in use (write in this case)
   if (dup2(fd[0],0) <0){
      perror("dup fail");
      exit(EXIT_FAILURE); }                            //tie read end of pipe to read end of process 
    execlp("grep","grep",word,NULL);                   //perform the grep
  }
  close(fd[0]);                                        //close the read/write process
  close(fd[1]);
  wait(NULL);
  wait(NULL);
  return 0;
}
