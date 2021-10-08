//Restaurant Management Program
//Programmer Kiarash Azarnia 810195576

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
	Akbar_Joojeh* akbar_joojeh = initial_akbar();
	int order_number;
	char name[STL];
	int control = 1;
	bool done;
	do{
		control = whattodo();
		done = 0;
		switch(control)
		{
		case 0:
			goodbye();
		break;
		case 1:
			done = add_food(akbar_joojeh ->list_of_foods);
			report(done);
		break;
		case 2:
			done = insert_customer(&(akbar_joojeh -> list_of_customers));
			report(done);
		break;
		case 3:
			done = add_order(akbar_joojeh);
			report(done);
		break;
		case 4:
			print_foods(akbar_joojeh -> list_of_foods);
		break;
		case 5:
			print_customers(akbar_joojeh -> list_of_customers);
		break;
		case 6:
			print_orders(akbar_joojeh);
		break;
		case 7:
			printf(" Please enter name of food to remove: ");
			scanf("%s",name);
			low_words(name);
			done = remove_food(akbar_joojeh->list_of_foods, name);
			report(done);
		break;
		case 8:
			printf(" Please enter username of customer to remove: ");
			scanf("%s",name);
			low_words(name);
			done = remove_customer(akbar_joojeh, name);
			report(done);
		break;
		case 9:
			printf(" Please enter number of order to remove: ");
			scanf("%d", &order_number);
			done = remove_order(akbar_joojeh -> list_of_orders, order_number);
			report(done);
		break;
		default:
			printf("\aERROR in Whattodo function!\n");
		break;
		}
	}while(control);

	return 0;
}