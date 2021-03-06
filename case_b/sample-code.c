#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<errno.h>

#define MAX_LINE 4096
#define MAX_WORDS MAX_LINE/2
/* a line can have at most MAX_LINE/2 words, why? */

void tokenize(char *line, char **words, int *nwords);
void find_and_execute(char **arglist);

int main()
{
        char line[MAX_LINE], *words[MAX_WORDS], message[MAX_LINE];
        int stop=0,nwords=0;/* c_id -> child process id */

        while(1)
        {
                printf("OSP CLI $ ");
			
                /* read a line of text here */
                fgets(line, MAX_LINE, stdin);

                tokenize(line,words,&nwords);

                /* More to do here */
                /* Check for exit */
                if (strcmp(words[0], "exit") == 0 && nwords == 1)
                {
                        /* 
                         * Break out of loop. 
                         * Let main program return as normal 
                         */
                        break;
                } 
                else if (strcmp(words[0], "exit") == 0 && nwords > 1)
                {
                        fprintf(stderr, "\e[1;31mError:\e[0m Unexpected argument for command: \e[1;33mexit\e[0m\n");
                        continue;
                }
		else if (strcmp(words[0], "cd") == 0 && nwords > 1)
		{
			printf("Changing to directory: %s\r\n", words[1]);
			chdir(words[1]);
		}
		else
		{
			find_and_execute(words);
		}

		/* 
		 * Clear the memory of the words array for the 
		 * next usage. Reset nwords so that new 
		 * commands are inserted at the beginning of
		 * the words array next iteration.
		 */
		nwords = 0;
		memset(words, 0, MAX_LINE);
        }
        return 0;
}


/* 
 * Execute the command in words and if there is any error
 * output that error
 */
void find_and_execute(char **arglist) 
{
        int wait_rv, c_id; /* return value from waitpid */
        int c_status; /* Status of child process */
	/* fork and run commands */
	if ((c_id = fork()) == -1)
	{
		perror("\e[1;31mError:\e[0m Failed to fork.\r\n");
		exit(EXIT_FAILURE);
	} 
	else if (c_id == 0) 
	{
		int res = execvp(arglist[0], arglist);
		if (res == -1) 
		{
			perror("\e[1;31mError:\e[0m");
			exit(EXIT_FAILURE);
		}
	} else {
		/* Wait for child process to complete */
		waitpid(c_id, &c_status, 0);

		printf("CHILD STATUS: %d\r\n", c_status >> 8);
	}
}

/*
 * Repeatedly get the next word of the string using strtok
 * and store it in words. 
 *
 * Use nwords for the index to insert the word into except for the first
 * word which gets inserted at index 0.
 *
 * Keep doing this until we reach the max number of words, or there are
 * no more tokens.
 */
void tokenize(char *line, char **words, int *nwords)
{
        int i = 0;
        *nwords=1;

        for(words[0]=strtok(line," \t\n");
            (*nwords<MAX_WORDS)&&(words[*nwords]=strtok(NULL, " \t\n"));
            *nwords=*nwords+1
           );


        /* Add null terminator to end of words array */
        words[*nwords + 1] = 0;
        return;
}

