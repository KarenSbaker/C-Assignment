/*-------------------------------------------------------------------
*/
/* ITS60304– Assignment #1 */
/* C Programming */
/* Student Name: <Wan Yee Xiong> <Karen Sim Tze Mien> */
/* Student ID: <0324206> <0322562> */
/*-------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>

#define MAXCHAR 25
#define CODELENGTH 6

FILE *gstText;
FILE *ngstText;

int transactions;

void purchase(void);

int main(void)
{
	int menuInput;
	int sentinel = 1;
	int flush;

	// Menu
		printf("------------------------------------\n");
		printf("Grocery Retail\n");
		printf("------------------------------------\n");
		printf("1. Purchase items\n");
		printf("2. Edit items\n");
		printf("3. Update items\n");
		printf("4. Delete items\n");
		printf("5. Show inventory\n");
		printf("6. Show daily transaction\n");
		printf("7. Exit\n");
		printf("\n");

	// Options
	while (sentinel) {
		printf("Select an option: ");

		if ((menuInput = getchar()) != '\n') {	// deals with lone '\n' inputs
			switch (menuInput) {
				case '1':
					purchase();
					break;
				case '2':
					printf("stub here\n");
					break;
				case '3':
					printf("stub here\n");
					break;
				case '4':
					printf("stub here\n");
					break;
				case '5':
					printf("stub here\n");
					break;
				case '6':
					printf("stub here\n");
					break;
				case '7':
					printf("Program exiting.\n");
					sentinel = 0;
					break;
				default:
					printf("Invalid input. Please enter your selection again.\n");
					break;
			}
			flush = getchar();	// flushes the '\n' after the input away
		}
	}
			
	return 0;
}

