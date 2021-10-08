#include "header.h"
#include <cmath>

void represent_array_in_string(char* char_pointer, string& word)
{
    word.erase(word.begin(), word.end());
    while(char_pointer != NULL)
    {
        if(*char_pointer == '\0')
            break;
        word.push_back(*char_pointer);
        char_pointer++;
    }   
}

void represent_command_line_to_string(int argc, char** argv, CommandLine& command_line)
{
    string word;
    (*argv)++;
    argc--;
    while(*argv != NULL)
    {
        if(!argc)
            break;
        word.erase(word.begin(), word.end());
        while(**argv != '\0')
        {
            word.push_back(**argv);
            (*argv)++;
        }
        command_line.push_back(word);
        (*argv)++;
        argc--;
    }
    if(argc != 0)
    {
        #ifdef ERRORREP
        //    cerr<<"Error: sth is wrong with command representation"<<endl;
        #endif
    }
}

Command what_commanded(string& command_name)
{
    if(command_name.compare(ENCODE) == 0)
        return Encode;
    if(command_name.compare(DECODE) == 0)
        return Decode;
    if(command_name.compare(DECOMP) == 0)
        return DecompressOnly;
    if(command_name.compare(COMP) == 0)
        return CompressOnly;
    return Invalid;
}
