#include "header.h"
#include "test.h"
#include <cstdlib>

#define COM_NAME 1
#define INP_FILE 2
#define OUT_FILE 3
#define KEY 4

int main(int argc, char** argv)
{
    string input_file_name, output_file_name, command_name, key_str;
    int cesar_key;

    represent_array_in_string(argv[INP_FILE], input_file_name);
    represent_array_in_string(argv[OUT_FILE], output_file_name);
    represent_array_in_string(argv[COM_NAME], command_name);
    represent_array_in_string(argv[KEY], key_str);

    Command command = what_commanded(command_name);
    
    switch(command)
    {
        case Encode:
            cesar_key = atoi(key_str.c_str());
			compress_only(input_file_name.c_str(), output_file_name.c_str());
			cezar(output_file_name.c_str(), cesar_key);
			hash_sdbm(output_file_name.c_str());
        break;
        case Decode:
			{
				long long hash = read_hash(input_file_name.c_str());
				remove_hash_n_copy(input_file_name.c_str(), HELP_FILE);
				if(hash != sdbm(HELP_FILE))
				{
					#ifdef ERRORREP
					cerr << "Error: hash isn't adjust." << endl;
					#endif
					break;
				}
				cesar_key = atoi(key_str.c_str());
				decezar(HELP_FILE, cesar_key);
				decompress_only(HELP_FILE, output_file_name.c_str());            
				remove(HELP_FILE);
			}
        break;
        case CompressOnly:
			compress_only(input_file_name.c_str(), output_file_name.c_str());
        break;
        case DecompressOnly:
			decompress_only(input_file_name.c_str(), output_file_name.c_str());            
        break;
        case Invalid:
			#ifdef ERRORREP
			cerr << "Error: invalid command." << endl;
			#endif
        break;
    }
    return 0;
}