#include "header.h"

//#define debugging
//for cerr reports

/*
	******** commands format ********

	flag is the string related to the option <-f | -l | -p | -e>

	add <-f first_name> <-l last_name> <-p phone_number> <-e email_address>
	<Command Ok | Command Failed>

	print format
	<id> <first_name> <last_name> <email_address> <phone_number>

	search <keyword>
	<id> <first_name> <last_name> <email_address> <phone_number>

	delete <id>
	<Command Ok | Command Failed>

	update <id> [-f first_name] [-l last_name] [-p phone_number] [-e email_address]
	<Command Ok | Command Failed>

	print_all
	<all contacts>

	******** option_flag ********
	-f first_name
	-l last_name
	-p phone_number
	-e email_address

*/

// command_name must start at first of command
bool commanded(string command, string command_name)
{
	/*int white_spaces = 0;
	while(command.at(i) == ' ' || command.at(i) == '\t')
		white_spaces = 0;*/
	return (command.find(command_name) != string::npos/*== white_spaces*/);
}

control_code what_commanded(string command)
{
	if (commanded(command, add_command))
		return Add;
	else if (commanded(command, search_command))
		return Search;
	else if (commanded(command, delete_command))
		return Delete;
	else if (commanded(command, update_command))
		return Update;
	else if (commanded(command, print_command))
		return PrintAll;
	else
	{
		#ifdef debugging
		cerr << "Error: Invalid command format." << endl;
		#endif
		return Invalid;
	}
}

bool check_phone_number(string checking_item)
{
	if(checking_item.length() == 0)
		return 0;
	if (checking_item.at(0) != '0' || checking_item.at(1) != '9')
	{
		#ifdef debugging
		cerr << "Error: phone_number must strats with \"09\"." << endl;
		#endif
		return 0;
	}
	if (checking_item.length() != 11)
	{
		#ifdef debugging
		cerr << "Error: phone_number must be 11 digits." << endl;
		#endif
		return 0;
	}
	for (int i = 0; i < 11; i++)
	{
		if (checking_item.at(i) > '9' || checking_item.at(i) < '0')
		{
			#ifdef debugging
			cerr << "Error: phone_number digits can only be numbers." << endl;
			#endif
			return 0;
		}
	}
	return 1;
}

bool check_email(string checking_item)
{
	if(checking_item.length() == 0)
		return 0;
	bool is_correct = 1;
	int dot_index, at_index;
	at_index = checking_item.find(string("@"));
	dot_index = checking_item.rfind(string("."));
	if (at_index == string::npos || dot_index == string::npos)
		is_correct = 0;
	if (at_index == 0 || dot_index == 0)
		is_correct = 0;
	if (at_index > dot_index || (at_index + 1 == dot_index)) // user.gmail@com | user@.com
		is_correct = 0;
	if (at_index != checking_item.rfind(string("@"))) // user@gmail@.com
		is_correct = 0;
	for (int i = 0; i < checking_item.length(); i++)
	{
		if (checking_item.at(i) == ',') // unallowed characters ,
		{
			is_correct = 0;
			break;
		}
	}
	if (is_correct)
		return 1;
	#ifdef debugging
	cerr << "Error: email syntax is incorrect." << endl;
	#endif
	return 0;
}

bool is_flag(string checking_item)
{
	return (checking_item == "-f" ||
			checking_item == "-l" ||
			checking_item == "-e" ||
			checking_item == "-p" );
}

bool erase_string_from(string &source, string what_erasing)
{
	bool found = 0;
	if(source.find(what_erasing) == string::npos)
		return 0;
	int index= source.find(what_erasing);
	int i = 0;
	while(index + what_erasing.length() < source.length())
	 	{
			index = source.find(what_erasing, i);
			if(index+what_erasing.length()<source.length())
			{
				if(source.at(index+what_erasing.length()) == '\t' || source.at(index+what_erasing.length()) == ' ')
				{found =1;	break;}
			}
			i++;
		}
	if(!found && (index + what_erasing.length()!=source.length()) ) return 0;
	source.erase(index, what_erasing.length());
	return 1;
}
void erase_all_about_flag(string& command, string option_flag, string related_string)
{
	erase_string_from(command, related_string);
	erase_string_from(command, option_flag);
}
void erase_white_spaces(string &source)
{
	for(int i=0; i<source.length(); i++)
	{
		while(i<source.length())
		{
			if(!(source.at(i) == ' ' || source.at(i) == '\t'))
				break;
			source.erase(i,1);
		}
	}
}

bool check_add_syntax(string command)
{
	string checking_item;
	int items_number = 0; // must be 4

	checking_item = related_string(command, first_name_flag);
	erase_all_about_flag(command, first_name_flag, checking_item);
	if (checking_item.length() != 0)
		if(!is_flag(checking_item))
		items_number++;

	checking_item = related_string(command, last_name_flag);
	erase_all_about_flag(command, last_name_flag, checking_item);
	if (checking_item.length() != 0)
		if(!is_flag(checking_item))
		items_number++;

	checking_item = related_string(command, phone_number_flag);
	erase_all_about_flag(command, phone_number_flag, checking_item);
	if (check_phone_number(checking_item))
		items_number++;

	checking_item = related_string(command, email_flag);
	erase_all_about_flag(command, email_flag, checking_item);
	if (check_email(checking_item))
		items_number++;

	erase_white_spaces(command);
	return (items_number == 4 && command == add_command);
}

//returns 0 if flag issued without it's string
bool erase_data_from_update_command(string& command)
{
	string checking_item;
	if( is_flag_commanded(command, email_flag) )
	{
		checking_item = related_string(command, email_flag);
		if(checking_item.length() == 0)
			return 0;
		erase_all_about_flag(command, email_flag, checking_item);
	}
	if( is_flag_commanded(command, first_name_flag) )
	{
		checking_item = related_string(command, first_name_flag);
		if(checking_item.length() == 0)
			return 0;
		erase_all_about_flag(command, first_name_flag, checking_item);
	}
	if( is_flag_commanded(command, last_name_flag) )
	{
		checking_item = related_string(command, last_name_flag);
		if(checking_item.length() == 0)
			return 0;
		erase_all_about_flag(command, last_name_flag, checking_item);
	}
	if( is_flag_commanded(command, phone_number_flag) )
	{
		checking_item = related_string(command, phone_number_flag);
		if(checking_item.length() == 0)
			return 0;
		erase_all_about_flag(command, phone_number_flag, checking_item);
	}
	return 1;
}

bool check_update_syntax(string checking_item)
{
	string id_string;
	const string update_word = "update";
	int index = checking_item.find(update_word) + update_word.length();
	// rejecting white space
	while(index < checking_item.length())
	{
		if(!(checking_item.at(index) == ' ' || checking_item.at(index) == '\t'))
			break;
		index++;
	}
	while(index < checking_item.length())
	{
		if(checking_item.at(index) == ' ' || checking_item.at(index) == '\t')
			break;
		if('9' < checking_item.at(index) || '0' > checking_item.at(index))
			return 0;
		id_string += checking_item.at(index);
		index++;
	}
	if(!erase_data_from_update_command(checking_item))
		return 0;
	erase_string_from(checking_item, id_string);
	erase_white_spaces(checking_item);
	return (checking_item == update_word);
}

bool check_delete_syntax(string checking_item)
{
	string id_string;
	const string delete_word = "delete";
	int index = checking_item.find(delete_word) + delete_word.length();
	// rejecting white space
	while(index < checking_item.length())
	{
		if(!(checking_item.at(index) == ' ' || checking_item.at(index) == '\t'))
			break;
		index++;
	}
	while(index < checking_item.length())
	{
		if(checking_item.at(index) == ' ' || checking_item.at(index) == '\t')
			break;
		if('9' < checking_item.at(index) || '0' > checking_item.at(index))
			return 0;
		id_string += checking_item.at(index);
		index++;
	}
	erase_string_from(checking_item, id_string);
	erase_white_spaces(checking_item);
	return (checking_item == delete_word);
}

bool check_search_syntax(string checking_item)
{
	/*will be coded soon*/
	return 1;
}

bool check_syntax(string command, control_code what_commanded)
{
	switch (what_commanded)
	{
	case Add:
		return check_add_syntax(command);
	break;

	case Search:
		return check_search_syntax(command);
	break;

	case Delete:
		return check_delete_syntax(command);
	break;

	case Update:
		return check_update_syntax(command);
	break;

	case PrintAll:
		return 1;
	break;

	default:
		return 0;
	break;
	}
}

//<Command Ok | Command Failed>
void report_progress(bool done)
{
	if(done)
		cout<<"Command Ok"<<endl;
	else
		cout<<"Command Failed"<<endl;
}
