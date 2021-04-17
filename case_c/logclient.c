/* logclient.c -- implements a simple log service client */
#include "logservice.h"

int main(int argc,char **argv)
{
	int id;
	char *send;

	/* Check if arguments are present on command line */
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s message", argv[0]);
		exit(1);
	} 
	else if (argc >= 2)
	{
		/* combine subsequent arguments into a single message */
		int msg_len = 0;
		int i = 1; 

		while(i < argc) 
		{
			msg_len += (strlen(argv[i]));
			i++;
		}

		/* handle spaces */
		msg_len += argc - 2;

		/* ensure send has the correct amount of memory */
		send = malloc(msg_len);

		/* Reset i for while loop */
		i = 1;

		while ( i < argc)
		{
			/* Append arguments to message */
			strcat(send, argv[i]);

			/* Append space unless this is the last argument */
			if ( i < argc - 1) 
			{
				strcat(send, " ");
			}

			i++;
		}
	}
	
	/* connect to the log service */
	if(-1 == (id = logServiceInit()))
	{
		perror("Connecting to queue");
		exit(1);
	}
	
	/* log the message supplied on the command line */ 
	if(-1 == logMessage(id, send))
	{
		perror("Sending Message");
		exit(1);
	}

	free(send);

	return 0;
}

