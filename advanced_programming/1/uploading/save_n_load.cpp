#include "header.h"
#include <cmath>
#include <fstream>

#define id_column_number 0
#define first_name_column_number 1
#define last_name_column_number 2
#define phone_column_number 3
#define email_column_number 4

/*
	******** saving format ********
	0<id>\t	1<first_name>\t	2<last_name>\t	3<email_address>\t	4<phone_column_number>\n
*/

int requested_information(const string &line)
{
	int index = 0;
	int id;
	string requested_string;
	do
	{
		requested_string += line.at(index);
		index++;
	}while(line.at(index) != '\t');
	id = 0;
	for(int i = 0; i<requested_string.length(); i++)
		id += (requested_string.at(i)-'0')*pow(10,requested_string.length()-i-1);
	return id;
}

string requested_information(const string &line, int column_number)
{
	int index = 0;
	string requested_string;
	for(int i = 0; i<column_number; i++)
	{
		do
		{
			index++;
		}while(line.at(index) != '\t');
		index++;
	}
	do
	{
		requested_string += line.at(index);
		index++;
		if(index == line.length())
			break;
	}while(line.at(index) != '\t' );
	return requested_string;
}

void load(vector<Contact> &contacts)
{
	string loading_line;
	ifstream file;
	Contact loading_contact;
	file.open("contacts.cvs", ios::in);
	if(!file.good()) //checking file exists or not
		return;
	while( getline(file, loading_line) )
	{
		loading_contact.id = requested_information(loading_line);
		loading_contact.first_name = requested_information(loading_line, first_name_column_number);
		loading_contact.last_name = requested_information(loading_line, last_name_column_number);
		loading_contact.phone_number = requested_information(loading_line, phone_column_number);
		loading_contact.email_address = requested_information(loading_line, email_column_number);

		if(!is_duplicated_contact(contacts, loading_contact))
			contacts.push_back(loading_contact);
	}
	file.close();
}

void save(const vector<Contact> &contacts)
{
	ofstream file;
	file.open("contacts.cvs", ios::out);
	for(int i = 0; i<contacts.size(); i++)
	{
		file<<contacts[i].id<<"\t"
			<<contacts[i].first_name<<"\t"
			<<contacts[i].last_name<<"\t"
			<<contacts[i].phone_number<<"\t"
			<<contacts[i].email_address<<"\n";
	}
	file.close();
}
