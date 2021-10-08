//Restaurant Management Program
//Programmer Kiarash Azarnia 810195576

#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <cctype>// tolower()
#include <conio.h>

/*void scan(char st[STL]) {
	scanf_s("%s", st, __crt_countof(st));
}*/

void low_words(char* st) // changes capital words to lower
{
	int i = 0;
	while(st[i])
	{
		st[i] = tolower(st[i]);
		i++;
	}
}

/**--------------- Customrs --------------**/
/*
 * print all customers in detail sorted by usernames (alphabetically)
 */

void print_one_customer(customer* c)
{
	if(c==NULL)
		return;
	printf(" username:\t%s\n",c->username);
	low_words(c->username);
	printf(" phone number:\t%s\n",c->phone_number);
	printf(" address:\t%s\n",c->address);
	printf("----------------------------------------------------------------------\n");
}

void print_customers(customer* customer_root)
{
	if(customer_root==NULL)
		return;
	print_customers(customer_root->left);
	print_one_customer(customer_root);
	print_customers(customer_root->right);
}

void formal_print_customers(customer* customer_root)
{
	printf("*********************** Customers Information ************************\n");
	print_customers(customer_root);
	printf("***************************** End Print ******************************\n");
}

/*
 * copy(s1,s2) copies string s2 into s1 until end of s2
*/
void copy(char s1[], char s2[])
{
	int i=0;
	while(s2[i]!='\0')
	{
		s1[i]=s2[i];
		i++;
	}
	s1[i]=s2[i];
}
/*
 * comp(s1,s2) returns
	1 if 1st string is alphabetically prime and
	2 if 2nd string is alphabitically prime and
	0 if they equal
*/
int comp(char* s1, char* s2)// assumed all characters are low or capital
{
	int i=0;
	while(s1[i]!='\0' && s2[i]!='\0')
	{
		if(s1[i]<s2[i])
			return 1;
		else if(s1[i]>s2[i])
			return 2;
		i++;
	}
	if(s1[i]=='\0' && s2[i]!='\0')
		return 1;
	else if(s1[i]!='\0' && s2[i]=='\0')
		return 2;
	else
		return 0;
}

bool isEqual(char s1[],char s2[]) //  returns 1 if strings are equal, and 0 otherwise
{
	bool eq=1;
	int i=0;
	while( (s1[i]!='\0' || s2[i]!='\0') && eq)
	{
		eq &= (s1[i] == s2[i]);
		i++;
	}
	return eq;
}

/*
 * returns the pointer that is the parent of the node wanted to insert and NULL if it exists or no tree
*/

customer* parent_of_new(customer* root, customer* node)
{
	if(root==NULL)
	{
		return NULL;
	}
	customer* parent = root;
	int prime = comp (node->username,root->username);
	switch(prime)
	{
	case 1:
		if(parent->left==NULL)
			return parent;
		else 
			return parent_of_new(parent->left,node);
	break;
	case 2:
		if(parent->right==NULL)
			return parent;
		else 
			return parent_of_new(parent->right,node);
	break;
	case 0:
		printf(" Customer's username is already exist!\n");
		return NULL;
	break;
	default:
		return NULL;
	}
}

customer* parentof(customer* root, customer* node)
{
	if (root==NULL)
	{
		printf(" ERROR:\a Root is NULL!\n");
		return NULL;
	}
	customer* parent = root;
	int prime = comp(node->username,parent->username);
	switch(prime)
	{
	case 0:
		return root;
	break;
	case 1:
		if(root->left==node)
			return root;
		else
			return parentof(root->left,node);
	break;
	case 2:
		if(root->right==node)
			return root;
		else
			return parentof(root->right,node);
	break;
	}
	return NULL;
}

/*void*  preNodeof(void* head, void* node)
{
	if(head==NULL)
		return NULL;
	void* p= head;
	bool found=isEqual(node->username,p->next->username);
	if(found)
	{
		printf("Node is head! Head hasn't pre_node!\n");
		return NULL;
	}
	while(p->next!=NULL && !found)
	{
		p=p->next;
		found=isEqual(node->username,p->next->username);
	}		
	if(found)
		return p;
	else
	{
		printf("Node not found!\n");
		return NULL;
	}
}

void* preNodeofNew(void* head, void* node) // returns last node of list! so no order is implicated!
{
	while(head->next!=NULL)
		head=head->next;
	return head;
}*/

 /* add new node in tree in alphabetical order
 *      return 1 if added successfully, otherwise if username is duplicated return 0
 */
bool insert_customer(customer** customer_root/*, customer* new_node*/)
{
	customer* new_node = (customer*) malloc (sizeof(customer));
	if(new_node==NULL)
		return 0;
	new_node->left=NULL;
	new_node->right=NULL;
	printf(" Please enter customer's information:\n");
	printf(" username:\t");
	scanf_s("%s",new_node->username,__crt_countof(new_node->username));
	low_words(new_node->username);
	printf(" phone number:\t");
	scanf_s("%s",new_node->phone_number,__crt_countof(new_node->phone_number));
	printf(" address:\t");
	scanf_s("%s",new_node->address,__crt_countof(new_node->address));
	customer* parent_node;
	parent_node= parent_of_new(*customer_root,new_node);
	if(parent_node!=NULL)
	{
		int prime=comp(new_node->username,parent_node->username);
		if(prime==0 || prime==1)
			parent_node->left=new_node;
		else if(prime==2)
			parent_node->right=new_node;
		else
			return 0;
	}
	else
		*customer_root = new_node;
	return 1;
}
/*int _insert_customer(customer* customer_root, customer** new_node, char username[], char phone_number[], char address[])
{
	customer* parent_node;
	short int prime=comp(node->username,root->username);
	(*new_node)=(*customer) malloc(sizeof(customer));
	if(*new_node==NULL)
		return 0;
	copy((*new_node)->username,username);
	copy((*new_node)->phone_number,phone_number);
	copy((*new_node)->address,address);
	(*new_node).right=NULL;
	(*new_node).left=NULL;
	parent_node=parent_of_new(customer_root,(*new_node));
	switch(prime)
	case 1:
	case 0:
		parent_node->left=(*new_node);
	break;
	case 0:
		parent_node->left=(*new_node);
	break;
	default:
		return 0;
	return 1;
}*/

/* Bonus Part:
 * remove a customer by its username
 * (also you should remove all his/her orders)
 *      return 1 if removed successfully, otherwise return 0
 */

/*void deltree(void* root)
{
	if(root==NULL)
		return;
	if(root->right!=NULL)
	{
		deltree(root->right);
		free(root->right);
	}
	if(root->left==NULL)
	{
		deltree(root->left);
		free(root->left);
	}
	free(root);
}*/
void dellist(food_row* head)
{
	if(head==NULL)
		return;
	if(head->next==NULL)
	{
		dellist(head->next);
		free(head);
		return;
	}
}
/*	if Item not found
	1. Do nothing
	else
	1. if node is a leaf
	change to NULL
	2. if node has one child
	promote child
	3. if node has two children
	find largest in nodes left branch
	recursively remove it. 
	use it as parent of the two subtrees
*/
/*struct _Akbar_Joojeh{
	customer* list_of_customers;
	food_row* list_of_foods;
	order*	list_of_orders;
}*/
void copy_customer(customer* c1, customer* c2)// copies customer c2 information into customer c1
{
	copy(c1->username,c2->username);
	copy(c1->phone_number,c2->phone_number);
	copy(c1->address,c2->address);
}

customer* most_left (customer* customer_root) // returns most left node of tree
{
	customer* p = customer_root;
	if(p==NULL)
		return NULL;
	while(p->left!=NULL)
		p=p->left;
	return p;
}

customer* most_right (customer* customer_root) // returns most right node of tree
{
	customer* p = customer_root;
	if(p==NULL)
		return NULL;
	while(p->right!=NULL)
		p=p->right;
	return p;
}

bool remove_customer_by_parent(customer* removing_customer,customer* parent_of_removing) // removes node that has 1 child at best.
{
	if(removing_customer->right == NULL && removing_customer->left == NULL)
	{
		if(parent_of_removing->right == removing_customer)
			parent_of_removing->right=NULL;
		else if(parent_of_removing->left == removing_customer)
			parent_of_removing->left=NULL;
		else
			return 0;
		free(removing_customer);
	}
	else if(removing_customer->right==NULL)
	{
		if(parent_of_removing->right == removing_customer)
			parent_of_removing->right=removing_customer->left;
		else if(parent_of_removing->left == removing_customer)
			parent_of_removing->left=removing_customer->left;
		else
			return 0;
		free(removing_customer);

	}
	else if(removing_customer->left==NULL)
	{
		if(parent_of_removing->right == removing_customer)
			parent_of_removing->right=removing_customer->right;
		else if(parent_of_removing->left == removing_customer)
			parent_of_removing->left=removing_customer->right;
		else
			return 0;
		free(removing_customer);
	}
	else
		return 0;
	return 1;
}

bool remove_customer_root(Akbar_Joojeh* akbar_joojeh) //Injaee!!!!!!!
{
	customer* root = akbar_joojeh -> list_of_customers;
	if(root == NULL)
		return 0;
	customer* moving_customer;
	customer* parent_of_removing;
	if(most_left(root->right)!=NULL)
	{
		moving_customer = most_left(root->right);
		parent_of_removing = parentof (root->right , moving_customer);
		if(parent_of_removing == moving_customer)
		{
			copy_customer(root , moving_customer);
			root -> right = root -> right -> right;
			free(moving_customer);
			return 1;
		}
	}
	else if(most_right(root->left)!=NULL)
	{
		moving_customer = most_right(root->left);
		parent_of_removing = parentof (root->left , moving_customer);
		if(parent_of_removing == moving_customer)
		{
			copy_customer(root , moving_customer);
			root -> left = root -> left -> left;
			free(moving_customer);
			return 1;
		}
	}
	else // root with no children
	{
		free(akbar_joojeh -> list_of_customers);
		akbar_joojeh -> list_of_customers = NULL;
		return 1;
	}
	copy_customer(root , moving_customer);
	return remove_customer_by_parent( moving_customer, parent_of_removing);
}


bool remove_customer(Akbar_Joojeh* akbar_joojeh, char username[])
{
	customer* removing_customer = search_customer (akbar_joojeh->list_of_customers , username);
	if (removing_customer == NULL)
		return 0;
	customer* parent_of_removing = parentof (akbar_joojeh->list_of_customers , removing_customer);
	order* removing_order = search_order(akbar_joojeh->list_of_orders, removing_customer->username);
	bool removed=1; 
	if(removing_order != NULL)
	{
		removed &= remove_order(akbar_joojeh->list_of_orders, removing_order -> number);
	}
	//^^^^^^^^^^^^^^^^^^ removing a node of customers tree ^^^^^^^^^^^^^^^^^^^^^^^^^^^
	if(akbar_joojeh->list_of_customers == removing_customer)
		return remove_customer_root(akbar_joojeh);
	removed &= remove_customer_by_parent(removing_customer, parent_of_removing);
	if(!removed)
	{
		customer* moving_customer = most_left(removing_customer->right);
		if(moving_customer==NULL)
			return 0;
		copy_customer(removing_customer,moving_customer);
		removing_customer = moving_customer;
		parent_of_removing = parentof (akbar_joojeh->list_of_customers , removing_customer);
		removed &= remove_customer_by_parent(removing_customer, parent_of_removing);		
	}
	return removed;
}

/*
 * search a customer by username and return its pointer
 *     return NULL if customer did not find
 */
customer* search_customer(customer* customer_root, char username[])
{
	if(customer_root==NULL)
	{
		printf(" ERROR:\a There is no tree to search for customers.\n");
		return NULL;
	}
	int prime = comp(username,customer_root->username);
	switch(prime)
	{
	case 0:
		return customer_root;
	break;
	case 1:
		if(customer_root->left!=NULL)
			return search_customer(customer_root->left,username);
		else
			printf(" ERROR:\a Customer not found.\n");
	break;
	case 2:
		if(customer_root->right!=NULL)
			return search_customer(customer_root->right,username);
		else
			printf(" ERROR:\a Customer not found.\n");
	break;
	}
	return NULL;
}


/**--------------- Foods --------------**/
/*
 * print all foods
 */
void print_foods(food* food_list)
{
	printf("**************************** Foods List ******************************\n");
	int i=1;
	food_list=food_list->next; // before while because of food_list's dummy node
	while(food_list!=NULL)
	{
		printf(" %d\n",i); // number 
		printf("\tname:\t%s\n",food_list->name);
		printf("\tprice:\t%d $\n",food_list->price);
		i++;
		food_list=food_list->next;
	}
	printf("***************************** End Print ******************************\n");
}
 
/*
 * add new food
 *     return 1 if added successfully, otherwise if name is duplicated return 0
 */
int ten(int n) // return 10^n
{
	int result=1;
	while(n>0)
	{
		result*=10;
		n--;
	}
	return result;
}
void input_price(food* new_food)
{
	new_food->price = 0;
	char price_temp[STL];
	do{
		int i = 0, j=0;
		printf(" Enter price of new food: ");
		scanf_s("%s",price_temp,__crt_countof(price_temp));
		while(price_temp[i])
			i++;
		do{
			if(int(price_temp[j])>'9' || int(price_temp[j])<'0')
			{
				new_food->price = -1;
				break;
			}
			new_food->price += ten(i-j-1)*(int(price_temp[j])-'0');
			j++;
		}while(j<i);
	}while(new_food->price < 0);
}

bool add_food(food* food_list) // non sorted
{
	food* new_food = (food*) malloc(sizeof(food));
	if(new_food==NULL)
		return 0;
	printf(" Enter name of new food: ");
	scanf_s("%s",new_food->name,__crt_countof(new_food->name));
	low_words(new_food->name);
	input_price(new_food);
	new_food->next=NULL;

	while(food_list->next!=NULL)
	{
		if(isEqual(food_list->name,new_food->name))
		{
			free(new_food);
			printf(" Your entered food name is already exist! Try again please.\n");
			return 0;
		}
		food_list=food_list->next;
	}
	if(isEqual(food_list->name,new_food->name))
	{
		free(new_food);
		printf(" Your entered food name is already exist! Try again please.\n");
		return 0;
	}
	else
		food_list->next=new_food;
	return 1;
}

bool _add_food(food* food_list, food* new_food);
/*
 * search a food by name and return its pointer
 *      return NULL if food did not find
 */
food* search_food(food* food_list, char name[])
{
	while(food_list != NULL)
	{
		if(isEqual(food_list->name,name))
			return food_list;
		food_list=food_list->next;
	}
	return NULL;
}
 

/**--------------- Orders --------------**/
/*
 * print all orders with user informatin and total price
 */
order* search_order(order* order_list, char username[])
{
	while(order_list!=NULL)
	{
		if(isEqual(order_list->username,username))
			return order_list;
		order_list=order_list->next;
	}
	return NULL;
}

bool print_customer(customer* customers, char username[])
{
	customer* found_customer= search_customer(customers, username);
	if(found_customer==NULL)
		return 0;
	printf("\tcustomer's information:\n");
	printf("\tusername:\t%s\n",found_customer->username);
	printf("\tphone number:\t%s\n",found_customer->phone_number);
	printf("\taddress:\t%s\n",found_customer->address);
	return 1;
}

int total_price(food_row* head_of_food_rows, food* list_of_foods) // returns -1 if cant find food
{
	if(head_of_food_rows == NULL)
		return 0;
	int sum=0;
	food_row* order_food_row=head_of_food_rows->next; //because of dummy
	food* food=list_of_foods;
	while(order_food_row!=NULL)
	{
		food = search_food(list_of_foods,order_food_row->name);
		if(food == NULL)
		{
			printf(" ERROR:\a <%s> not found in food list.\n",order_food_row->name);
		}
		else
			sum += (order_food_row->quantity) * (food->price);
		order_food_row = order_food_row->next;
	}
	return sum;
}
void print_food_rows(food_row* row)
{
	if(row == NULL) return;
	row = row -> next; // because of list_of_food_row dumy node
	printf("\tcustomer's food row:\n");
	while(row != NULL)
	{
		printf("\tfood name:\t%s\tquantity:\t%d\n",row->name,row->quantity);
		row=row->next;
	}
}

void print_orders(Akbar_Joojeh* akbar_joojeh)
{
	customer* customers=akbar_joojeh->list_of_customers;
	order* orders=akbar_joojeh->list_of_orders->next; // next because of first dummy
	food* foods=akbar_joojeh->list_of_foods->next; // next because of first dummy
	int TotalPrice=0;
	printf("**************************** Orders List *****************************\n");
	while(orders!=NULL)
	{
		printf("\tnumber:\t%d\n",orders->number); // number 
		print_customer(customers,orders->username);
		printf("\tdate: %s\ttime: %s\n",orders->date,orders->time);
		print_food_rows(orders->list_of_food_row);//printing food rows
		TotalPrice = total_price(orders->list_of_food_row,foods);
		printf("\ttotal price:\t%d $\n",TotalPrice);
		printf("----------------------------------------------------------------------\n");
		orders=orders->next;
	}
	printf("***************************** End Print ******************************\n");

}

/*
 * add new order
 *     return 1 if added successfully, otherwise if order number is duplicated or entered invalid username or invalid food return 0
 */
void input_frn(int* frn)
{
	*frn = 0;
	char temp[STL];
	do{
		int i = 0, j=0;
		printf(" How many food rows does this order include? ");
		scanf_s("%s",temp,__crt_countof(temp));
		while(temp[i])
			i++;
		do{
			if(int(temp[j])>'9' || int(temp[j])<'0')
			{
				*frn = -1;
				break;
			}
			*frn += ten(i-j-1)*(int(temp[j])-'0');
			j++;
		}while(j<i);
	}while(*frn < 0);
}

void input_quantity(int* frn)
{
	*frn = 0;
	char temp[STL];
	do{
		*frn = 0;
		int i = 0, j=0;
		printf("\t Quantity: ");
		scanf_s("%s",temp,__crt_countof(temp));
		while(temp[i])
			i++;
		do{
			if(int(temp[j])>'9' || int(temp[j])<'0')
			{
				*frn = -1;
				break;
			}
			*frn += ten(i-j-1)*(int(temp[j])-'0');
			j++;
		}while(j<i);
	}while(*frn < 0);
}

bool add_food_row(order* new_order)
{
	new_order -> list_of_food_row = (food_row*) malloc (sizeof(food_row));
	if(new_order -> list_of_food_row == NULL)
		return 0;
	new_order -> list_of_food_row -> next = NULL;
	food_row* point_food_row = new_order -> list_of_food_row;
	int frn=0;//for Food Rows Number
	input_frn(&frn);
	for(int i=1;i<=frn;i++)
	{
		point_food_row->next= (food_row*) malloc (sizeof(food_row));
		point_food_row=point_food_row->next;
		if(point_food_row==NULL)
			return 0;
		point_food_row->next=NULL;
		printf("^^^^^^^^ Food row %d# \n",i);
		printf("\t Food name: ");
		scanf_s("%s",point_food_row->name,__crt_countof(point_food_row->name));
		low_words(point_food_row->name);
		input_quantity(&(point_food_row->quantity));
	}
	return 1;
}

void input_number(int* frn)
{
	*frn = 0;
	char temp[STL];
	do{
		int i = 0, j=0;
		printf(" Please enter the order number: ");
		scanf_s("%s",temp,__crt_countof(temp));
		while(temp[i])
			i++;
		do{
			if(int(temp[j])>'9' || int(temp[j])<'0')
			{
				*frn = -1;
				break;
			}
			*frn += ten(i-j-1)*(int(temp[j])-'0');
			j++;
		}while(j<i);
	}while(*frn < 0);
}


bool add_order(Akbar_Joojeh* akbar_joojeh)
{
	order* new_order = (order*) malloc (sizeof(order));
	if(new_order==NULL)
		return 0;
	new_order -> next = NULL;
	if(!add_food_row(new_order)) return 0;
	input_number(&(new_order->number));
	printf(" Please enter the order customer's username: ");
	scanf_s("%s",new_order->username,__crt_countof(new_order->username));
	low_words(new_order->username);
	printf(" Date of order: ");
	scanf_s("%s",new_order->date,__crt_countof(new_order->date));
	printf(" Time of order: ");
	scanf_s("%s",new_order->time,__crt_countof(new_order->time));
	order* point_order = akbar_joojeh -> list_of_orders;
	while(point_order->next!=NULL)
	{
		if(point_order->number == new_order->number)
		{
			printf(" Duplicated order number!\n");
			return 0;
		}
		point_order=point_order->next;
	}
	point_order->next=new_order;
	return 1;
}

bool _add_order(Akbar_Joojeh* akbar_joojeh, order* new_order);

/*
 * remover a order by its number
 *      return 1 if removed successfully, otherwise return 0
 */
bool remove_order(order* order_list, int order_number)
{
	order* point_order = order_list;
	bool removed=0;
	while(point_order->next!= NULL)
	{
		if(point_order->next->number==order_number)
		{
			order* removing_order = point_order->next;
			point_order->next=point_order->next->next;
			dellist(removing_order->list_of_food_row);
			free(removing_order);
			removed=1;
			break;
		}
		else
			point_order=point_order->next;
	}
	return removed;	 
}

bool remove_food(food* food_list, char* food_name)
{
	food* point_food = food_list;
	bool removed=0;
	while(point_food->next!= NULL)
	{
		if(isEqual(point_food->next->name,food_name))
		{
			food* removing_food = point_food->next;
			point_food->next=point_food->next->next;
			free(removing_food);
			removed=1;
			break;
		}
		else
			point_food=point_food->next;
	}
	return removed;	 
}

// intializing Akbar_Joojeh first dummy nodes
void welcome()
{
	printf("\a**********************************************************************\n"); //70 stars just because of you!
	printf("******* Welcome to AKBAR JOOJEH restaurant management program! *******\n");
	printf("**********************************************************************\n");
}


Akbar_Joojeh* initial_akbar()
{
	welcome();
	Akbar_Joojeh* akbar_joojeh = (Akbar_Joojeh*) malloc (sizeof(Akbar_Joojeh));
	akbar_joojeh->list_of_customers = NULL;
	akbar_joojeh->list_of_foods = (food*) malloc (sizeof(food));
	akbar_joojeh->list_of_foods->next = NULL;
	akbar_joojeh->list_of_orders = (order*) malloc (sizeof(order));
	akbar_joojeh->list_of_orders->next = NULL;
	return akbar_joojeh;
}

int whattodo()
{
	char charcontrol[STL];
	int control;
	printf("______________________________________________________________________\n");
	printf(" Please enter:\n");
	printf(" 1 to Add food to menu\n");
	printf(" 2 to Add a customer\n");
	printf(" 3 to Add an order\n");
	printf(" 4 to Print food menu\n");
	printf(" 5 to Print customer list\n");
	printf(" 6 to Print order list with total prices\n");
	printf(" 7 to Remove a food\n");
	printf(" 8 to Remove a customer\n");
	printf(" 9 to Remove an order\n");
	printf(" 0 to Exit program  ");
	printf("\t\t\t\t");
	do{
		scanf_s("%s",charcontrol,__crt_countof(charcontrol));
		control = int(charcontrol[0]) - '0';
		if(control<0 || control>9 || charcontrol[1])
		{
			printf("\n Invalid input! Try again:");
			printf("\t\t\t");
		}
		else
		{
			printf("______________________________________________________________________\n");
			break;
		}
	}while(true);
	return control;
}

void goodbye()
{
	printf("****************************** GOOD BYE! *****************************\n\a");
	getchar();
}

void report(bool done)
{
	if(done)
		printf(" complete done...\n");
	else
		printf(" Failed, Try again...\n");
}