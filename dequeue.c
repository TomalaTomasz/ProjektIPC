#include <stdio.h>
#include <sys/msg.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

struct bufor 
{
    long mtype;
    char message[100];
};

int main(int argc, char* argv[])
{
	key_t key;
	int msgID;	
	struct bufor msg;	
	int size;
	
	time_t czas;
    struct tm * ptr;
    time( & czas );
    ptr = localtime( & czas );
    
    if ( (ptr->tm_wday == 0) || (ptr->tm_wday == 5) || (ptr->tm_wday == 6) )
    {
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
		
		if ((msgrcv(msgID, &msg, size, 1, IPC_NOWAIT)) == -1)
		{
			perror("msgrcv");
			exit(1);
		}
		
		//Sprawdzenie czy komunikat zaczyna się od litery
		int bool=1;
		if (!(((int)msg.message[0] >= 65 && (int)msg.message[0] <= 90) || ((int)msg.message[0] >= 97 && (int)msg.message[0] <= 122)))
			bool = 0;
		
		//Sprawdzenie czy komunikat składa się ze znaków ASCII
		int i=0;
		if (bool)
		{
			while (msg.message[i] != '\0')
			{
				if (!((int)msg.message[i] >= 32 && (int)msg.message[i] <= 126))
					bool = 0;
				i++;
			}
		}
	
		if (bool)
		{
			printf("Otrzymany komunikat: %s\n", msg.message);
			msgctl(msgID, IPC_RMID, NULL);
			execl("./aspell.sh", "./aspell.sh", msg.message, NULL);
			
		}
		else
			printf("\nPodany komunikat nie jest poprawny.\n");
	}
	else
		printf("Nie ma weekendu więc nie odczytam wiadomości.\n");
	
	msgctl(msgID, IPC_RMID, NULL);
	return 0;
}
