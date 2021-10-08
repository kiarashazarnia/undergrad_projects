#include "header.h"
#include <cmath>

#define seprator " "

/*
  ******** option_flag
  -f first_name
  -l last_name
  -p phone_number
  -e email_address
*/

//#define debugging
//for cerr reports

//flag is the string related to the option <-f | -l | -p | -e>
string related_string(const string &command, string option_flag)
{
  string related_string;
  if(command.rfind(option_flag) == string::npos)
    return "";
  int index_option = command.rfind(option_flag);
  int i = index_option + option_flag.length();
  if(i == command.length())
    return "";
  // i starts in white space before of related string
  // rejecting white space
  while(command.at(i) == ' ' || command.at(i) == '\t')
    i++;
  for( ; i<command.length(); i++)
  {
     if(command.at(i) == ' ' || command.at(i) == '\t')
       break;
     related_string += command.at(i);
  }
  return related_string;
}

/*	add <-f first_name> <-l last_name> <-p phone_number> <-e email_address>
	<Command Ok | Command Failed>*/

// first_name and last_name, phone_number, emial must be unique
bool is_duplicated_contact(vector<Contact> &contacts, Contact contact)
{
	for(int i=0; i<contacts.size(); i++)
	{
		if( contact.email_address == contacts[i].email_address ||
			contact.phone_number == contacts[i].phone_number ||
			(contact.first_name == contacts[i].first_name &&
			contact.last_name == contacts[i].last_name))
			return 1;
	}
	return 0;
}

bool add_contact(const string &command, vector<Contact> &contact)
{
	Contact adding_contact;
	adding_contact.first_name = related_string(command, first_name_flag);
	adding_contact.last_name = related_string(command, last_name_flag);
	adding_contact.email_address = related_string(command, email_flag);
	adding_contact.phone_number = related_string(command, phone_number_flag);
	if( is_duplicated_contact(contact, adding_contact) )
	{
        #ifdef debugging
		cerr<<"Error: contact is duplicated."<<endl;
        #endif
		return 0;
	}
    if(contact.size() == 0)
        adding_contact.id = id_start_point;
    else
	   adding_contact.id = (contact.end()-1)->id + id_start_point +1;
	contact.push_back(adding_contact);
	return 1;
}

void print_char(char character, int number)
{
	for( ; number>0; number--)
		cout<<character;
	cout<<endl;
}

void print_contact(Contact contact)
{
	//<id> <first_name> <last_name> <email_address> <phone_number>
	cout<<contact.id<<seprator<<contact.first_name<<seprator<<contact.last_name<<seprator;
	cout<<contact.phone_number<<seprator<<contact.email_address<<endl;
}

void print_contacts(const vector<Contact> &contact)
{
	print_char(trimming_char, trimming_char_number);
	for(int i = 0; i< contact.size(); i++)
	{
		print_contact(contact[i]);
	}
	print_char(trimming_char, trimming_char_number);
}

// cuts chracters from index to end of command or first white space and returns it
string search_item(const string &command)
{
    string keyword;
    const string search_word = "search";
    int index = command.find(search_word) + search_word.length();
    // rejecting white space
	while( index < command.length() )
	{
		while( (command.at(index) == ' ' || command.at(index) == '\t') )
			index++;
		if(command.at(index) == ' ' || command.at(index) == '\t')
			break;
			keyword += command.at(index);
			index++;
	}
    return keyword;
}

bool search_in_contact(Contact contact, string search_item)
{
	return (   contact.first_name.find(search_item) != string::npos
			|| contact.last_name.find(search_item) != string::npos
			|| contact.phone_number.find(search_item) != string::npos
			|| contact.email_address.find(search_item) != string::npos);
}

/*	search <keyword>
	<id> <first_name> <last_name> <email_address> <phone_number>*/
void search_n_print_contact(const vector<Contact> &contact, string search_item)
{
	bool found;
	for(int i = 0; i<contact.size(); i++)
	{
		found = search_in_contact(contact[i], search_item);
		if(found)
			print_contact(contact[i]);
	}
}

bool search_n_print_contacts(const vector<Contact> &contact, string search_item)
{
	bool found = 0;
	for(int i = 0; i<contact.size(); i++)
	{
		found |= search_in_contact(contact[i], search_item);
		if(found)
			print_contact(contact[i]);
	}
    return found;
}

// if finds, returns contact's position number in vector else returns -1
int search_contact(const vector<Contact> &contact, string search_item)
{
	bool found;
	for(int i = 0; i<contact.size(); i++)
	{
		found = search_in_contact(contact[i], search_item);
		if(found)
			return i;
	}
	return -1;
}

int search_contact_by_id(const vector<Contact> &contact, int id)
{
	bool found;
	for(int i = 0; i<contact.size(); i++)
	{
		found = contact[i].id == id;
		if(found)
			return i;
	}
    #ifdef debugging
	cerr<<"Error: no contact with "<<id<<"id."<<endl;
    #endif
	return -1;
}

// returns commandded id to delete contact
int deleting_id(const string &command)
{
    string id_string;
    int id = 0;
    const string delete_word = "delete";
    int index = command.find(delete_word) + delete_word.length();
    // rejecting white space
	while(index < command.length())
	{
		if(!(command.at(index) == ' ' || command.at(index) == '\t'))
			break;
		index++;
	}
	while(index < command.length())
	{
		if(command.at(index) == ' ' || command.at(index) == '\t')
			break;
		if('9' < command.at(index) || '0' > command.at(index))
			return -1;
		id_string += command.at(index);
		index++;
	}
    // translating string to integer
    for(int i = 0; i < id_string.length(); i++)
        id += (id_string.at(i)-'0')*pow(10,id_string.length()-i-1);
    return id;
}

  /*delete <id>
  <Command Ok | Command Failed>*/
bool delete_contact_by_id(vector<Contact> &contact, int id)
{
    int index = search_contact_by_id(contact, id);
    if(index == -1)
        return 0;
	contact.erase(contact.begin() + index);
        return 1;
}

bool is_flag_commanded(const string &command, string flag)
{
	return (command.find(flag) != string::npos);
}

/*	update <id> [-f first_name] [-l last_name] [-p phone_number] [-e email_address]
	<Command Ok | Command Failed>*/

int updating_id(const string &command)
{
    string id_string;
    int id = 0;
    const string update_word = "update";
    int index = command.find(update_word) + update_word.length();
    // rejecting white space
	while(index < command.length())
	{
		if(!(command.at(index) == ' ' || command.at(index) == '\t'))
			break;
		index++;
	}
	while(index < command.length())
	{
		if(command.at(index) == ' ' || command.at(index) == '\t')
			break;
		if('9' < command.at(index) || '0' > command.at(index))
			return -1;
		id_string += command.at(index);
		index++;
	}
    // translating string to integer
    for(int i = 0; i < id_string.length(); i++)
        id += (id_string.at(i)-'0')*pow(10,id_string.length()-i-1);
    return id;
}

void feed_updating_contact(const string& command, Contact old_contact, Contact& new_contact)
{
    if( is_flag_commanded(command, email_flag) )
		 new_contact.email_address = related_string(command, email_flag);
    else
         new_contact.email_address = old_contact.email_address;
	if( is_flag_commanded(command, first_name_flag) )
		new_contact.first_name = related_string(command, first_name_flag);
    else
        new_contact.first_name = old_contact.first_name;
	if( is_flag_commanded(command, last_name_flag) )
		 new_contact.last_name = related_string(command, last_name_flag);
    else
        new_contact.last_name = old_contact.last_name;
	if( is_flag_commanded(command, phone_number_flag) )
		 new_contact.phone_number = related_string(command, phone_number_flag);
    else
        new_contact.phone_number = old_contact.phone_number;
    new_contact.id = old_contact.id;
}

bool is_duplicated_contact(vector<Contact> &contacts, Contact contact, int exception_contact_index)
{
    for(int i=0; i<contacts.size(); i++)
	{
		if( contact.email_address == contacts[i].email_address ||
			contact.phone_number == contacts[i].phone_number ||
			(contact.first_name == contacts[i].first_name &&
			contact.last_name == contacts[i].last_name))
        {
            if(i == exception_contact_index)
                continue;
			return 1;
        }
	}
	return 0;
}

bool update_contact(const string &command, vector<Contact> &contact, int id)
{
    Contact updating_contact;
	int index = search_contact_by_id(contact, id);
	if(index == -1)
		return 0;
    feed_updating_contact(command, contact[index], updating_contact);
    if(!(check_email(updating_contact.email_address) && check_phone_number(updating_contact.phone_number)))
    {
        #ifdef debugging
        cerr<<"Error: email or phone_number is incorrect."<<endl;
        #endif
        return 0;
    }
    if( is_duplicated_contact(contact, updating_contact, index) )
	{
        #ifdef debugging
		cerr<<"Error: contact is duplicated."<<endl;
        #endif
		return 0;
	}
    contact[index] = updating_contact;
	return 1;
}
