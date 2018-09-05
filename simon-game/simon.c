#include <stdio.h>
#include <stdlib.h>
#include <DAQlib.h>
#include <time.h>
#include <Windows.h>

#define GREEN 0
#define RED 1
#define YELLOW 2
#define BLUE 3
#define BUTTON0 0
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3
#define MAXLENGTH 5
#define WINNINGLENGTH 3
#define LOSINGLENGTH 3
#define ONESEC 1000

#define ON 1
#define OFF 0
#define HIGH 1
#define LOW 0
#define TRUE 1
#define FALSE 0

/* Function prototypes*/

void runSimon (void);
void displaysequence (int count, int sequence []);
void generatesequence (int sequence []); 
int checkanswer (int count, int sequence [], int answer[]);
void displaywinningsequence (void);
void displaylosingsequence (void);
void recordanswer (int answer [], int count);


int main (void){
	int setupNum;
	printf("Enter the setup number for DAQ (0 for the device or 6 for the simulator): ");
    scanf("%d", &setupNum);

	/*
	** Calling the setupDAQ function to initialise DAQ
    ** If the return value of the setupDAQ function call is TRUE, initialisation is
	** successful.
	*/

    if ( setupDAQ(setupNum) == TRUE )
        runSimon();
	else
        printf("ERROR: Cannot initialise DAQ\n");

    system("PAUSE");
    return 0;
}

/* Purpose: Runs the Simon game.
   Parameters: None.
*/

void runSimon () {
	/* Initialization of variables used to test the random number generator. */
	int test;
	int i;


	int count;
	int sequence [MAXLENGTH];
	int UserCorrect;
	int response;
	int answer [MAXLENGTH];

	while (continueSuperLoop () == TRUE) {
		printf("New game has started!\n");
		/* Generates random sequence for current game */
		generatesequence (sequence);
		
		/* Test to see results of random sequence generated
		for (test = 0; test< MAXLENGTH; test++){
			printf("%d\n", sequence [test]);
		}	*/

		/* Sets all values in answer array to 5 so that values can be changed to 0, 1, 2, or 3 depending on user's input.*/

		for (count = 0; count < MAXLENGTH; count++){
			for (i = 0; i < MAXLENGTH; i ++){
				answer [i] = 5;
			}

			displaysequence ((count + 1), sequence);
			recordanswer(answer, (count+1));
			UserCorrect = checkanswer((count + 1), sequence, answer);

			if (UserCorrect == FALSE)
				break;

		}

		/* If the player gets the entire sequence correct, the green LED flashes and the player gets a chance to restart the game.*/

		if (UserCorrect == TRUE){
			displaywinningsequence ();
			printf("Congratulations! You won the game! (Enter 1 to start new game, 0 to end the game).");
			scanf_s("%d", &response);

			/* Checks if user wants to continue playing*/
			if (response == FALSE){
				break;
			}
		}
		/* If the player enters the incorrect sequence, the current game ends and the red LED flashes and the player gets a chance to restart.*/
		else {
			displaylosingsequence ();
			printf("Sorry you lose! Do you want to play again? (Enter 1 to restart game, 0 to end).");
			scanf_s("%d", &response);

			/* Checks if user wants to continue playing*/
			if (response == FALSE){
				break;
			}
		}
		}
	}
/* Purpose: Generates 5 random numbers from 0 to 3. 
* Input: 1D array that stores generated numbers from 0 to 3 that represent the sequence of numbers for the particular game.
* Returns: Nothing.
*/

void generatesequence (int sequence []){
   int i, n;
   time_t t;
   n = MAXLENGTH;
   
   /* Intializes random number generator */
   srand((unsigned) time(&t));

   /* Assigns random number to sequence array */
   for( i = 0 ; i < n ; i++ ) 
   {
	  sequence [i] = rand() % (MAXLENGTH - 1);
   }
}

/* Purpose: Displays random number sequence that the player has to memorzize. 
* Inputs: Count integer that represents how far the player is into the game and how many colours they have correctly remembered.
*         1D array with random number sequence. 
* Returns: Nothing.
*/

void displaysequence (int count, int sequence []){
	int count2;
	Sleep (ONESEC/2);
	for (count2 = 0; count2 < count; count2++){
		digitalWrite (sequence [count2], ON);
		Sleep (ONESEC/2);
		digitalWrite (sequence [count2], OFF);
		Sleep (ONESEC/10);
	}
}

/* Purpose: Checks whether the player clicked the correct sequence of LEDs. 
 * Inputs: Count integer that represents how far the player is into the game and how many colours they have correctly remembered.
*          1D array with random number sequence for the particular game.    
*          1D array with player's input. 
*  Returns: Whether the player has inputted the correct sequence. 
*/
int checkanswer (int count, int sequence [], int answer []){
	int UserCorrect = TRUE;
	int check;
	
	for (check = 0; check < count; check++) {
		if (sequence [check] != answer [check]){
			UserCorrect = FALSE;
		}
	}
	return UserCorrect;
}

/* Purpose: Records the player's inputted sequence. 
*  Input: Count integer that represents how far the player is into the game and how many colours they have correctly remembered.
*         1D array with player's input.
*  Returns: Nothing.
*/

void recordanswer (int answer [], int count){
	int button0, button1, button2, button3;
	int count3;
	for (count3 = 0; count3 < count; count3++){
		while (ON){
			
			/* Reads each button twice to determine if the user has actually pressed the button and to avoid recording
			*  random bounces of the button. 
			*  The LED flashes if the program has recorded the user's input. 
			*/
			button0 = digitalRead (BUTTON0);
				if (button0 == TRUE) {
					Sleep (ONESEC/5);
				if (button0 == TRUE) {
				digitalWrite (BUTTON0, ON);
				Sleep (ONESEC/2.5);
				digitalWrite (BUTTON0, OFF);
				answer [count3] = 0;
				break;
				}
			}
			button1 = digitalRead (BUTTON1);
			
			if (button1 == TRUE) {
				Sleep (ONESEC/5);
				if (button1 == TRUE) {
				digitalWrite (BUTTON1, ON);
				Sleep (ONESEC/2.5);
				digitalWrite (BUTTON1, OFF);
				answer [count3] = 1;
				break;
				}
			}

			button2 = digitalRead (BUTTON2);
			
			if (button2 == TRUE) {
				Sleep (ONESEC/5);
				if (button2 == TRUE) {		
				digitalWrite (BUTTON2, ON);
				Sleep (ONESEC/2.5);
				digitalWrite (BUTTON2, OFF);
				answer [count3] = 2;
				break;
				}
			}
			button3 = digitalRead (BUTTON3);

			if (button3 == TRUE) {
				Sleep (ONESEC/5);
				if (button3 == TRUE) {
				digitalWrite (BUTTON3, ON);
				Sleep (ONESEC/2.5);
				digitalWrite (BUTTON3, OFF);
				answer [count3] = 3;
				break;
				}
			}
		}
	}
}

/* Purpose: Displays winning sequence (Three flashes of the green LED.*/

void displaywinningsequence (void){
	int count;
	for (count = 0; count <WINNINGLENGTH; count ++) {
	digitalWrite (GREEN, ON);
	Sleep (ONESEC/3);
	digitalWrite (GREEN, OFF);
	Sleep (ONESEC/10);
	}
}

/* Purpose: Displays losing sequence (Three flashes of the red LED.*/

void displaylosingsequence (void){
	int count;
	for (count = 0; count <LOSINGLENGTH; count ++) {
	digitalWrite (RED, ON);
	Sleep (ONESEC/3);
	digitalWrite (RED, OFF);
	Sleep (ONESEC/10);
	}
}