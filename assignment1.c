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

void showInventory(void);

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
		scanf("%d", &menuInput)

		if ((menuInput = getchar()) != '\n') {	// deals with lone '\n' inputs
			switch (menuInput) {
				case '1':
					purchase();
					break;
					
				case '2':
					printf("This option allows user to edit items.\n");
					break;
					
				case '3':
					printf("This option allows user to update items.\n");
					break;
					
				case '4':
					printf("This option allows user to delete items.\n");
					break;
					
				case '5':
                    showInventory();
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

void showInventory (void)
{  

				char itemCode[6];
				char itemName[20];
				double itemPrice;
				int quantity;

				    printf("GST included Items\n");
				    if ((gstText = fopen("/home/0322562/karen/Assignement1/gst.txt", "r")) == NULL ){
						puts("File could not be opened");
					}
					else {
						printf("%s \t %s \t %s \t %s \n", "Item Code", "Item Name", "Item Price", "Quantity");
					    fscanf( gstText, "%s %s %lf %d", itemCode, itemName, &itemPrice, &quantity);

						while (!feof(gstText)){
						printf("%s %s %.2lf %d \n", itemCode, itemName, itemPrice, quantity);
					    fscanf( gstText, "%s %s %lf %d", itemCode, itemName, &itemPrice, &quantity);
						}

						fclose(gstText);
					}

					printf("Non-GST included Items\n");
				    if ((ngstText = fopen("/home/0322562/karen/Assignment1/ngst.txt", "r")) ==NULL ){
						puts("File could not be opened");
					}
					else {
						printf("%s \t %s \t %s \t %s\n", "Item Code", "Item Name", "Item Price", "Quantity");
					    fscanf( ngstText, "%s %s %lf %d", itemCode, itemName, &itemPrice, &quantity);

						while (!feof(ngstText)){
					    printf("%s %s %.2lf %d \n", itemCode, itemName, itemPrice, quantity);
					    fscanf( ngstText, "%s %s %lf %d", itemCode, itemName, &itemPrice, &quantity);
						}

						fclose(ngstText);
					}

}


