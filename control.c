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

union semun {
  int val; 
  struct semid_ds *buf; 
  unsigned short *array;
  struct seminfo *__buf;
};

int viewFile(){
	int filedesc = open("foo.txt", O_RDONLY);
	struct stat data;
  	int info = stat("foo.txt", &data);
  	if (info == -1){
    	printf("error: %d - %s\n", errno, strerror(errno));
    	return -1;
  	}
  	int size = data.st_size;
  	char text[size + 1];
  	read(filedesc, text, size);
  	text[size] = '\0';
	close(filedesc);
	printf("printing foo.txt...\n%s", text);
}

int main(int argc, char* argv[]){
	int shmkey = ftok("control.c", 66);
	int semkey = ftok("write.c", 21);
	int shmid;
	int semid;

  	if (strncmp(argv[1], "-c", strlen(argv[1])) == 0){
  		shmid = shmget(shmkey, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
      	semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0644);
    	union semun su; 
    	su.val = 1;
    	semctl(semid, 0, SETVAL, su);
    	int filedesc = open("foo.txt", O_CREAT | O_TRUNC, 0644);
    	close(filedesc);
  	}

  	else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0){
  		viewFile();
  	}

    else if (strncmp(argv[1], "-r", strlen(argv[1])) == 0){
    	shmid = shmget(shmkey, sizeof(int), 0);
    	shmctl(shmid, IPC_RMID, 0);
    	semid = semget(semkey, 1, 0);
    	semctl(semid, 0, IPC_RMID);
    	viewFile();
    }

    return 0;
}

