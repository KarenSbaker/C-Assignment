/*-------------------------------------------------------------------
*/
/* ITS60304– Assignment #1 */
/* C Programming */
/* Student Name: <your name 1> <your name 2> */
/* Student ID: <your ID1> <your ID2> */
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

void purchase(void)
{
	char itemCodeInput[CODELENGTH];
	char itemCode[CODELENGTH];
	char itemName[MAXCHAR];
	int quantityInput;
	int quantity;
	int itemFound;
	double price;
	
	gstText = fopen("gst.txt", "r");
	ngstText = fopen("ngst.txt", "r");

	itemFound = 0;

	printf("------------------------------------\n");
	printf("Purchase\n");
	printf("------------------------------------\n");
	printf("Enter -1 to cancel transaction\n");
	printf("Enter c to conclude transaction\n");
	printf("\n");

	printf("Enter the item code: ");
	scanf("%s", itemCodeInput);
	while(strcmp(itemCodeInput, "-1") && strcmp(itemCodeInput, "c")) {
		while(!feof(gstText)) {
			fscanf(gstText, " %9[^;];%25[^;];%lf;%d", itemCode, itemName, &price, &quantity);
			if (strcmp(itemCodeInput, itemCode) == 0) {
				itemFound = 1;
				break;
			}
			fscanf(ngstText, " %9[^;];%25[^;];%lf;%d", itemCode, itemName, &price, &quantity);
			if (strcmp(itemCodeInput, itemCode) == 0) {
				itemFound = 1;
				break;
			}
		}

		if (itemFound) {
			printf("\n");
			printf("Negative quantities cancel the selected item\n");
			printf("Enter the quantity: ");
			scanf("%d", &quantityInput);
			if (quantityInput >= 0) {
				transactions += quantityInput;
				printf("\n");
				printf("Code       Name                     Price      Quantity\n");
				printf("%-10s %-24s %-10.2lf %-10d\n", itemCode, itemName, price, quantityInput);
				printf("\n");
				printf("Subtotal: %.2lf\n", price * quantityInput);
				printf("\n");
			}
			else
				printf("Item canceled\n");
		}
		else
			printf("Invalid item.\n");

		rewind(gstText);
		rewind(ngstText);
		itemFound = 0;
		printf("Enter the item code: ");
		scanf("%s", itemCodeInput);
	}

	fclose(gstText);
	fclose(ngstText);

	return;
}