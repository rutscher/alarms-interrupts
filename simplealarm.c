/* Assingment 3 CS354 Section 1
 * Jacob Trotman (trotman) Section 1
 * Joseph Bauer (jbauer) Section 1
 *
 * This program is like an alarm clock that goes on forever
 * There is an inefficient algorithm that displays prime numbers
 * starting from 1000001 and counting up, that is supposed to take
 * a bunch of time up so we know that something is going on in the program
 * The alarm displays the current time every single second.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>

// create our boolean variable for the prime number inefficient alogrithm
#define TRUE 1;
#define FALSE 0;
typedef int boolean;

/* The flag that is set by the signal */
volatile int flag = FALSE;

/*initialize the handler for the interrupt */
void handler();

/* main is our main method of the program. It is an alarm clock
 * that goes on forever and prints the current time until a signal
 * is sent to the program to end. THis signal is an interrupt and 
 * is flagged by typing ctrl+c. (or ^C)
 * Parameters:
 *  argv[] : array for the command to start the program
 *  argc : the number of arguments from the command line
 */

int main (int argc, char *argv[])
{
	/* tell the user how to exit the program */
	printf("Enter ^C to end the program: \n");
	
	
	/*check for the correct number of arguments*/
	if (argc != 1)
	{
		/* if incorrect output error message and quit program*/
		fprintf(stderr, "usage: there are no parameters\n");
		exit(1);
	}
	/*build the signla action and assign the handler to it */
	struct sigaction sigAct;
	sigAct.sa_handler = handler;
	
	/* create and start a alarm timer*/
	sigaction(SIGALRM, &sigAct,NULL);
	alarm(1);
	
	/* Infinite while loop, to be exited on SIGINT 
	 * There is also an inefficient algorithm that displays
	 * large prime numbers above 1000001
	*/
	while(1)
	{
		int i;
		int j;
		boolean prime;
		prime = TRUE;
		for(i = 1000001; i < 100000000; i++)
		{
			for(j = (i-1); j > 1; j--)
			{
				if((i % j) == 0)
				{
					prime = FALSE;
				}
			}
			if(prime)
			{
				printf("%d ", i);
			}
			prime = TRUE;
			// get the current time and if the flag is true print
			time_t t;
			time(&t);
			if(flag==1)
			{
                		printf("current time is %s", ctime(&t));
                		flag=FALSE;
                		alarm(1);
			}
            
		}
	}
	return 0;
}

/*call from sigAct sets the flag to true and the time is
 * printed within the main method
 *
 */
void handler()
{
	flag=TRUE;
}
