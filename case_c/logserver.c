/* logserver.c -- implementation of the log server */
#include <signal.h>
#include "logservice.h"

int queue_id; /* stores queue_id for use in signal handler */

void handler(int sig);


int main()
{
	int rec;
	struct message rec_msg;

	/* initialise the message queue here */
	queue_id = msgget(KEY, IPC_CREAT | IPC_EXCL | 0622);

	/* Check if the queue already exists */
	if (queue_id == -1) 
	{
		printf("Message queue already exist.\n");
		exit(1);
	}

	/* install signal handler to clean up queue
	 * do this after you have created the queue
	 * then you dont need to check if it is valid!
	 */
	signal(SIGINT, handler);
	
	
	while (1)
	{
		if ((rec = msgrcv(queue_id, (void*) &rec_msg, sizeof(rec_msg), 0, IPC_NOWAIT)) == -1) {
			/* Do nothing */
		}
		else
		{
			printf("%d: %s\n", (int)rec_msg.type, rec_msg.message);
		}
	}
	
	return 0;
}


void handler(int sig)
{
	if (msgctl(queue_id, IPC_RMID, NULL) == -1)
	{
		printf("Failed to cleanup\n");
		exit(1);
	}
	else
	{
		printf("Cleanup queue %d success\n", queue_id);
		exit(0);
	}
}
