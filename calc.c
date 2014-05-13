/* Assingment 3 CS354 Section 1
 * Jacob Trotman (trotman) Section 1
 * Joseph Bauer (jbauer) Section 1
 *
 * This program is a simple calculator that performs basic operations in an
 * infinte while loop. The calcultor will only stop with an interupt. One interupts 
 * occurs when the user attempts to divded by 0 or when ^c is  
 * pressed. If there is an arthmitic  If ^c is pressed the handler prints out the   
 * number of calcuations and exits. If the handler for dividing by 0 is used the  
 * program exits.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/*initialize the handlers for the interrupts */
void fpe_handler();
void int_handler();

/*intialize calcuation counter*/
int count;

/* Main method is a calculator that does basic operations and loops until an  
 * interrupt is thrown
 * Parameters:
 *  argv[] : array for the command to start the program
 *  argc : the number of arguments from the command line
 */
int main(int argc, char *argv[]){

	/*check for the correct number of arguments*/
	if (argc != 1)
	{
		/* if incorrect output error message and quit program*/
		fprintf(stderr, "usage: there are no parameters\n");
		exit(1);
	}
    
	/*build the signla action and assign the handler to it */
	struct sigaction sigAct_fpe;
	sigAct_fpe.sa_handler = fpe_handler;
	sigaction(SIGFPE, &sigAct_fpe, NULL);
	struct sigaction sigAct_int;
	sigAct_int.sa_handler = int_handler;
	sigaction(SIGINT, &sigAct_int, NULL);
		
	count = 0;

	/* main while loop of the calculator*/
	while(1){
	/*variables to hold user input*/
        char num1[10000]; //buffer to hold user input
        char num2[10000];
        int result;
	char op;

	//collecting user input
        printf("Enter a number \n");
        scanf("%s", num1);
	printf("Enter a number \n");
       	scanf("%s", num2);
        printf("Enter an operator \n");
        scanf("%s", &op);
	int num11;
	int num22;
	num11 = atoi(num1);
	num22 = atoi(num2);
	
	// decide which operator to use and make calcuation
        switch(op){
                case '-':
                result=num11-num22;
                break;
                case '*':
                result=num11*num22;
                break;
                case '/':
                result=num11/num22;
                break;
                case '+':
                result=num11+num22;
                break;
                default:
                printf("bad operator read. addition was performed\n");
                result=num11+num22;
                break;        
        }
	count++;
        printf("%d \n", result);
    }
    
}

/*Called when a fpe is thrown
 */
void fpe_handler()
{
    printf("You attempted to divide by zero. Program will exit. \n");
	exit(1);
}

/*Called when ^c is pressed
 */
void int_handler()
{
	printf("\n%d operations were completed\n", count);
	exit(1);
}
