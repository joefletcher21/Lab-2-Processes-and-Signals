/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h> 
#include <sys/wait.h>


#define   MAX_COUNT  2

pid_t getpid(void);
pid_t getppid(void);

void childProcess(){

  // this is what each child process does

  srand(time(0));
  int numLoop = (rand() % 30 + 1);

  for (int k = 1; k <= numLoop; k++) {
    int timeSleep = (rand() % 10 + 1);

    // get the pid of the parent and the child
    pid_t child = getpid();
    pid_t parent = getppid();

    printf("Child Pid: %d is going to sleep!\n", child);

    // pause execution 
    sleep(timeSleep);

    printf(" Child Pid: %d is awake!\n Where is my Parent: %d?\n", child, parent);
  }
  exit(0);

}


int main()
{
  int status;
  int pid[MAX_COUNT];

  // the make amount of child processes should be 2
  for(int j = 0; j < MAX_COUNT; j++){
    pid[j] = fork();

    // if a child process is created success
    if(pid[j] == 0){
      childProcess();
    } else if (pid[j] == -1){
      printf("There was an error in created a child process.");
    }
  }

  for(int n = 0; n < MAX_COUNT; n++){
    //iter twice because 2 children
    
    wait(&status); // parent process waits for everything to finish

    // notify
    printf("Child Pid: %d has completed!\n", pid[n]);
  }

  return 0;
}
