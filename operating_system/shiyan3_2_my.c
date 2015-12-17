#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/ipc.h>

#define SIZE 1024

void server(void);
void client(void);

int main(void)
{
	gid_t 	ch1;
	gid_t 	ch2;
	key_t 	key;
	int 	shmid = 0;
	
	//create a new share memory
	key = 75;
	if ((shmid = shmget(key, SIZE, IPC_CREAT|0777)) == -1)
	{
		perror("shmget error");
		exit(1);
	}
	//
	printf("shmid = %d\n", shmid);
	
	
	if ((ch1 = fork()) == -1)
	{
		perror("fork child 1 error");
		exit(1);
	}
	
	if (ch1 == 0)
	{
		//child 1
		client();
	}
	else
	{
		if ((ch2 = fork()) == -1)
		{
			perror("fork child 2 error");
			exit(1);
		}
		
		if (ch2 == 0)
		{
			//child 2
			server();
			
		}
		else
		{
			//parent
			wait(NULL);
			wait(NULL);
			if (shmctl(shmid, IPC_RMID, 0) == -1)
			{
				perror("shmctl error");
				exit(1);
			}
	
		}
	}
	//

	return 0;
}


void server()
{
	key_t key;
	int shmid = 0;
	char *addr = NULL;
	int i = 0;
	//recv
	//huo qu shmid
	key = 75;
	if ((shmid = shmget(key, SIZE, 0777)) == -1)
	{
		perror("server shmget error");
		exit(1);
	}
	
	//ying she share memory
	if ((addr = (char *)shmat(shmid, NULL, 0)) == (char *)-1)
	{
		perror("server shmid error");
		exit(1);
	}
	
	while (1)
	{
		while (*addr != 'a');
		*addr = 'b';
		i++;
		printf("*addr+%d = %c\n", i, *addr+i);
		if (i == 5)
		{
			break;
		}
	}
	
	
}

void client()
{	
	//send
	
	key_t key;
	int shmid = 0;
	char *addr = NULL;
	int i = 0;

	//huo qu shmid
	key = 75;
	if ((shmid = shmget(key, SIZE, 0777)) == -1)
	{
		perror("client shmget error");
		exit(1);
	}
	
	//ying she share memory
	if ((addr = (char *)shmat(shmid, NULL, 0)) == (char *)-1)
	{
		perror("client shmid error");
		exit(1);
	}
	*addr = 'b';
	for (i = 0; i < 5; i++)
	{
		while (*addr != 'b');
		*addr = 'a';
	}
}
