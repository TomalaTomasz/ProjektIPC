#include <stdio.h>
#include <sys/msg.h>
#include <stdlib.h>

struct bufor 
{
    long mtype;
    char message[100];
};

int main(int argc, char* argv[])
{
	key_t key;
	int msgID;
	int size;
	struct bufor msg;
	
	printf("Podaj komunikat do wysłania: ");
	scanf("%s", msg.message);
	msg.mtype = 1;

	size = sizeof msg.message;
	
	if ((key = ftok("./queue", 286257)) == -1)
	{
		perror("ftok");
		exit(1);
	}
	
	if ((msgID = msgget(key, 0666 | IPC_CREAT)) == -1)
	{
		perror("mssget");
		exit(1);
	}
	
	if ((msgsnd(msgID, &msg, size, IPC_NOWAIT)) == -1)
	{
		perror("msgsnd");
	}
	
	return 0;
}
