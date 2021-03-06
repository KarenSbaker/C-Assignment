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
#include <math.h>

#define MAXCHAR 25
#define CODELENGTH 6

enum boolean { NO, YES };

FILE *gstText;
FILE *ngstText;
FILE *transactionsText;

int gstTransactions;
int ngstTransactions;
double gstSales;
double ngstSales;
int flush;

void purchase(void);

void showInventory(void);

int main(void)
{
	int menuInput;
	int sentinel = 1;

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

void purchase(void)
{
	char itemCodeInput[CODELENGTH];
	char itemCode[CODELENGTH];
	char itemName[MAXCHAR];
	char receiptPrompt;
	int quantityInput;
	int quantity;
	int itemFound;
	int transactions = 0;
	int isGST;
	double price;
	double subtotal;
	double gstAmount;
	double total;
	double roundedTotal;
	
	gstText = fopen("gst.txt", "r");
	ngstText = fopen("ngst.txt", "r");
	transactionsText = fopen("transactions.txt", "w");

	itemFound = NO;

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
				itemFound = YES;
				isGST = YES;
				break;
			}
			fscanf(ngstText, " %9[^;];%25[^;];%lf;%d", itemCode, itemName, &price, &quantity);
			if (strcmp(itemCodeInput, itemCode) == 0) {
				itemFound = YES;
				isGST = NO;
				break;
			}
		}

		if (itemFound) {
			printf("\n");
			printf("Quantities less than 1 will cancel the selected item\n");
			printf("Enter the quantity: ");
			scanf("%d", &quantityInput);
			if (quantityInput > 0) {

				subtotal = price * quantityInput;
				gstAmount = subtotal * 0.06;
				// Write to file
				fprintf(transactionsText, "%s;%s;%.2lf;%d\n", itemCode, itemName, price, quantityInput);

				printf("\n");
				printf("Code       Name                     Price      Quantity\n");
				printf("%-10s %-24s %-10.2lf %-10d\n", itemCode, itemName, price, quantityInput);
				printf("\n");
				if (isGST) {	// is the item GST taxable?
					printf("Subtotal: %.2lf (%.2lf + %.2lf GST)\n", subtotal + gstAmount, subtotal, gstAmount);
					gstTransactions += quantityInput;
					gstSales += (subtotal + gstAmount);
				}
				else {
					printf("Subtotal: %.2lf\n", subtotal);
					ngstTransactions += quantityInput;
					ngstSales += subtotal;
				}
				printf("\n");
			}
			else
				printf("Item canceled\n");
		}
		else
			printf("Invalid item.\n");

		rewind(gstText);
		rewind(ngstText);
		itemFound = NO;
		printf("Enter the item code: ");
		scanf("%s", itemCodeInput);
	}

	fclose(transactionsText);

	// Receipt
	if (strcmp(itemCodeInput, "-1") && subtotal > 0) {
		flush = getchar();
		printf("Print receipt? (y/n): ");
		for(;;) {
			receiptPrompt = getchar();
			flush = getchar();
			if (receiptPrompt == 'y') {

				transactionsText = fopen("transactions.txt", "r");

				printf("======== Receipt ========\n");
				printf("Code       Name                     Price      Quantity\n");
				printf("\n");
				while(!feof(transactionsText)) {
					fscanf(transactionsText, " %9[^;];%25[^;];%lf;%d", itemCode, itemName, &price, &quantity);
					
					subtotal = price * quantityInput;
					gstAmount = subtotal * 0.06;

					printf("%-10s %-24s %-10.2lf %-10d\n", itemCode, itemName, price, quantityInput);
					if (itemCode[1] == 'G') {
						total += (subtotal + gstAmount);
						printf("Subtotal: %.2lf (%.2lf + %.2lf GST)\n", subtotal + gstAmount, subtotal, gstAmount);
					}
					else {
						total += subtotal;
						printf("Subtotal: %.2lf\n", subtotal);
					}
					printf("\n");
				}
				printf("Total Sales incl GST: %.2lf\n", total);
				roundedTotal = round(total * 2.0) / 2.0;
				printf("Rounding adjusment: %.2lf\n", roundedTotal - total);
				printf("Total after adj incl GST: %.2lf\n", roundedTotal);
				fclose(transactionsText);
				break;
			}
			else if (receiptPrompt == 'n') {
				printf("Transaction concluded\n");
				break;
			}
			else
				printf("Invalid input, please enter y or n: ");
		}
	}
	else
		printf("Transaction canceled\n");

	fclose(gstText);
	fclose(ngstText);

	return;
}