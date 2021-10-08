//Restaurant Management Program
//Programmer Kiarash Azarnia 810195576

#ifndef CODE_HEADER_H
#define CODE_HEADER_H
#define STL 100 // strings length

typedef struct _Akbar_Joojeh Akbar_Joojeh;
typedef struct _customer customer;
typedef struct _food food;
typedef struct _food_row food_row;
typedef struct _order order;

/* This Struct must contain:
 *     list of customers
 *     list of foods
 *     list of orders
 */
struct _Akbar_Joojeh{
 	customer* list_of_customers;
	food* list_of_foods;
	order*	list_of_orders;
};


/* This Struct must contain:
 *     username
 *     phone number
 *     address
 *     left_child
 *     right_child
 */
struct _customer{
	char username[STL];
	char phone_number[STL];
	char address[STL];
    customer* left;
    customer* right;
};


/* This Struct must contain:
 *     name
 *     price
 *     next_node
 */
struct _food{
	char name[STL];
	int price;
	food* next;
};


/* This Struct must contain:
 *     food name
 *     quantity
 *     next
 */
struct _food_row{
	char name[STL];
	int quantity;
	food_row* next;
};


/* This struct must contain:
 *     order number
 *     customer username
 *     list of food_row
 *     Date and Time
 *     next_node
 */
struct _order{
	int number;
	char username[STL];
	food_row* list_of_food_row;
	char date[STL];
	char time[STL];
	order* next;
};

void low_words(char* st);

/**--------------- Customrs --------------**/
/*
 * print all customers in detail sorted by usernames (alphabetically)
 */

void prind_one_customer(customer* c);


void print_customers(customer* customer_root);

void formal_print_customers(customer* customer_root);


/*
 * copy(s1,s2) copies string s2 into s1 until end of s2
*/
void copy(char s1[], char s2[]);

/*
 * comp(s1,s2) returns
	1 if 1st string is alphabetically prime and
	2 if 2nd string is alphabitically prime and
	0 if they equal
*/
int comp(char s1[], char s2[]);// assumed all characters are low or capital


bool isEqual(char s1[],char s2[]); //  returns 1 if strings are equal, and 0 otherwise


/*
 * returns the pointer that is the parent of the node wanted to insert
*/

customer* parent_of_new(customer* root, customer* node);


customer* parentof(customer* root, customer* node);


/*void* preNodeof(void* head, void* node);
void* preNodeofNew(void* head, void* node); // returns last node of list! so no order is implicated!*/


 /* add new node in tree in alphabetical order
 *      return 1 if added successfully, otherwise if username is duplicated return 0
 */
bool insert_customer(customer** customer_root/*, customer* new_node*/);

/* Bonus Part:
 * remove a customer by its username
 * (also you should remove all his/her orders)
 *      return 1 if removed successfully, otherwise return 0
 */

void deltree(food_row* root);

/*void dellist(void* head);*/

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
void copy_customer(customer* c1, customer* c2);// copies customer c2 information into customer c1
customer* parentof(customer* root, customer* node);

bool remove_customer_by_parent(customer* removing_customer,customer* parent_of_removing); // removes node that has 1 child at best. 


bool remove_customer(Akbar_Joojeh* akbar_joojeh, char username[]);


/*
 * search a customer by username and return its pointer
 *     return NULL if customer did not find
 */
customer* search_customer(customer* customer_root, char username[]);



/**--------------- Foods --------------**/
/*
 * print all foods
 */
void print_foods(food* food_list);

 
/*
 * add new food
 *     return 1 if added successfully, otherwise if name is duplicated return 0
 */
bool add_food(food* food_list); // non sorted


bool _add_food(food* food_list, food* new_food);
/*
 * search a food by name and return its pointer
 *      return NULL if food did not find
 */
food* search_food(food* food_list, char name[]);

 

/**--------------- Orders --------------**/
/*
 * print all orders with user informatin and total price
 */
order* search_order(order* order_list, char username[]);

void print_one_customer(customer*);
bool print_customer(customer* customers, char username[]);


int total_price(food_row* head_of_food_rows, food* list_of_foods); // returns -1 if cant find food

void print_food_rows(food_row* row);


void print_orders(Akbar_Joojeh* akbar_joojeh);


/*
 * add new order
 *     return 1 if added successfully, otherwise if order number is duplicated or entered invalid username or invalid food return 0
 */
bool add_order(Akbar_Joojeh* akbar_joojeh);


bool _add_order(Akbar_Joojeh* akbar_joojeh, order* new_order);

/*
 * remover a order by its number
 *      return 1 if removed successfully, otherwise return 0
 */
bool remove_order(order* , int );
int whattodo(); // asks operator what to do and returns relative number
Akbar_Joojeh* initial_akbar(); // to initialize akbar_joojeh in first of program running
void report(bool done); // reports if reguest action was done or not
void goodbye(); // prints goodbye massage
bool remove_food(food* food_list, char* food_name); // to remove a food by it's name
#endif