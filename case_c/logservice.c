/* logservice.c -- implementation of the log service */
#include "logservice.h"

int logServiceInit()
{
	/* Only let the owner read/write. Others can write only */
	int id = msgget(KEY, IPC_EXCL|0622);
		
	if (id == -1) {
		/* Print no queue msg */
		printf("Queue does not exist:\n");
	}
	return id;

}

int logMessage(int serviceId,char *message)
{
	int rv;
	struct message send_msg;

	/* Set PID */
	send_msg.type = getpid();

	/* store msg in to message */
	strncpy(send_msg.message, message, MSGCHARS);

	printf("The message is \"%s\"\n", message);
	
	/* Validate message length and send message */
	if (strlen(message) > MSGCHARS)
	{
		printf("Message length exceeds max length.\n");
	}
	else if ((rv = msgsnd(serviceId, &send_msg, sizeof(send_msg),1)) == -1) 
	{
		perror("Failed to send message");
		return -1;
	}
	else
	{
		printf("This process id is %d\n", getpid());
		printf("Message send success: \"%s\"\n", message);
	}
	
	return rv;
}
