#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define id_start_point 0

/*
    ******** Structs ********
    ******** Structs start with Capital word.
 */

enum control_code
{
	Add,
 	Delete,
 	Update,
 	Search,
 	PrintAll,
 	Invalid
};

struct Contact
{
    string first_name;
    string last_name;
    string email_address;
    string phone_number;
    int id;
};
/*	id most be uique */

/*
    ******** option_flag ********
    -f first_name
    -l last_name
    -p phone_number
    -e email_address
*/

#define first_name_flag string("-f")
#define last_name_flag string("-l")
#define phone_number_flag string("-p")
#define email_flag string("-e")

/*
    ******** commands functions ********
    working with a vector of Contacts: vector<Contact> contact
*/
string related_string(const string& command, string option_flag);
bool is_duplicated_contact(vector<Contact> &contacts, Contact contact);
bool add_contact(const string& command, vector<Contact> &contact);
string search_item(const string &command);
int search_contact_by_id(const vector<Contact> &contact, int id);
int search_contact(const vector<Contact> &contact, string search_item);
bool search_contacts(const vector<Contact> &contact, string search_item);
int deleting_id(const string &command);
bool delete_contact_by_id(vector<Contact> &contact, int id);
void print_contact(Contact contact);
void print_contacts(const vector<Contact> &contact);
void search_n_print_contact(const vector<Contact> &contact, string search_item);
bool search_n_print_contacts(const vector<Contact> &contact, string search_item);
bool is_flag_commanded(const string &command, string flag);
int updating_id(const string &command);
void feed_updating_contact(const string& command, Contact old_contact, Contact& new_contact);
bool is_duplicated_contact(vector<Contact> &contacts, Contact contact, int exception_contact_index);
bool update_contact(const string &command, vector<Contact> &contact, int id);

/*
    ******** control flow ********
*/
bool erase_string_from(string &source, string what_erasing);
void erase_all_about_flag(string& command, string option_flag, string related_string);
void erase_white_spaces(string &source);

#define add_command string("add")
#define update_command string("update")
#define delete_command string("delete")
#define search_command string("search")
#define print_command string("print_all")

bool commanded(string command, string command_name);
control_code what_commanded(string command);
bool check_phone_number(string checking_item);
bool check_email(string checking_item);
bool is_flag(string checking_item);
bool check_add_syntax(string command);
bool check_syntax(string command, control_code command_code);
void report_progress(bool done);


/*
	******** Trimming ********
*/
#define trimming_char_number 64
#define trimming_char '*'

void print_char(char character, int number);

/*
	******** Loading and Saving ********
	contacts.cvs
*/
void load(vector<Contact> &contacts);
void save(const vector<Contact> &contacts);
