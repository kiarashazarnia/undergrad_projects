// AP Assingment1 Kiarash Azarnia 810195576
//#define debugging

#include "header.h"

int main()
{
	int index, id;
    vector<Contact> contacts;
    load(contacts);
    string command, keyword;
    bool done;
    control_code command_name;

    while(true)
    {
		getline(cin,command);
		if(cin.eof())
			break;

        command_name = what_commanded(command);
        done = check_syntax(command,command_name);
        if(done)
        {
            switch(command_name)
            {
                case Add:
                    done = add_contact(command, contacts);
                break;

                case Delete:
                    id = deleting_id(command);
                    done = delete_contact_by_id(contacts, id);
                break;

                case Update:
                    id = updating_id(command);
                    done = update_contact(command, contacts, id);
                break;

                case Search:
                    keyword = search_item(command);
					done = search_n_print_contacts(contacts, keyword);
					#ifdef debugging
					if(!done)
						cerr<<"Error: not found."<<endl;
					#endif
					continue;
                break;

				case PrintAll:
					print_contacts(contacts);
					continue;
				break;

				default:
                    done = 0;
                break;
            }
        }
        report_progress(done);
    }
    save(contacts);
    return 0;
}
