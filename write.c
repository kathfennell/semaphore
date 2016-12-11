#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
  int semkey = ftok("makefile", 22);
  int semid = semget(semkey, 1, 0);
 struct sembuf sb;


  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;

  //Down the semaphore
  sb.sem_op = -1;
  sb.sem_num = 1;
  semop(semid, &sb, 1);


  //access shared memory 
  int shmkey = ftok("control.c", 22);
  int shmid = shmget(shmkey, sizeof(long), 0);
  
  long *shared = shmat(shmid, 0, 0);

  char *x = (char *)malloc(*shared + 1);

  //printing last line
  int fd = open("foo.txt", O_RDWR | O_APPEND);
  lseek(fd, -(*shared), SEEK_END);
  read(fd, x, *shared);
  if(!*shared){
    printf("Add a word to start the story!: ");
  }
  else{
    printf("Last Addition %s", x);
    printf("Enter words: ");
  }

  char new[500];
  fgets(new, 500, stdin);

  *shared = strlen(new);

  write(fd, new, *shared);
  close(fd);

  shmdt(shared);

  sb.sem_op = 1;
  sb.sem_num = 1;

  return 0;
}