#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/*
union semun{
	int val;
	struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
  };
  */

void readStory(){
	int fd = open("story.txt", 0_RDONLY);
	char story[200];
	int len = read(fd, story, sizeof(story)-1);
	story[len] = 0;
	close(fd);
	printf("%s", story);
}

int main(int argc, char *argv[]){
//	struct stat st;
	int size;
	int semid; 
	int key = ftok("makefile", 22);
	int sc;
	int sd;
	int fd;
	char* buff;
	if (strncmp((argv[1]), "-c", strlen(argv[1])) == 0){
		sd = shmget(24601, 1000, IPC_CREAT | 0664);
		fd = open("story.txt", O_CREAT | 0_TRUNC, 0644); 
		smid = semget(key, 1, IPC_CREAT | 0644);
		printf("semaphore created: %d\n", semid);
		union semun su;
		su.val = 1;
		sc = semctl(semid, 0, SETVAL, su)

		printf("value set: %d\n", sc);	
	}
	else if (strncmp ((argv[1]), "-v", strlen(argv[1])) == 0){
		semid = semget(key, 1, 0);
		fd = open("story.txt", O_RDONLY); 

		sc = semctl(semid, 0, GETVAL );
		printf("semaphore value: %d\n", sc);
		
		read(fd, buff, 100);
		printf("%s\n", buffer);

		close(fd);
	}


	else if (strncmp((argv[1]), "-r", strlen(argv[1])) == 0){
		fd = open("story.txt", O_RDONLY); 
		semid = semget(key, 1, 0);
		sc = semctl(semid, 0, IPC_RMID);
		printf("semaphore removed: %d\n", sc);
		read(fd, buff, 100);
		close(fd);

	}
	return 0;
}