#include "command.hpp"

bool is_white_space(char c){
    return c == ' ' || c == '\t';
}
int first_pos(unsigned i, unsigned j){
    if(i == string::npos)
        return j;
    if(j == string::npos)
        return i;
    if(i < j)
        return i;
    else
        return j;    
}
int first_blank_pos(string s){
    int space = s.find(" ");
    int tab = s.find("\t");
    return first_pos(space, tab);
}
string split_first_word(string& str){
    string word;
    int pos = first_blank_pos(str);
    if(pos == string::npos){
        word = str;
        str.erase();
    }
    else{
        word = str.substr(0, pos);
        str.erase(0, pos+1);
    }
    return word;
}
vector<string> split_str(string str){
    string word;
    vector<string> splitted;
    while(str.size() != 0){
        word = split_first_word(str);
        splitted.push_back(word);
    }
    return splitted;
}
void Command::giveCommand(){
    while(command_line.empty())
        getline(cin, command_line);
}
vector<string> Command::split(){
    splitted_command = split_str(command_line);
    return splitted_command;
}
CommandName Command::whatCommanded(){
    split();
    string command_name = splitted_command.at(0);
    for(unsigned i = 0; i < commands.size(); i++)
        if(command_name == commands.at(i).str)
            return (CommandName) i;
    return CommandName::invalid;
}
int Command::words(){
    split();
    return splitted_command.size();
}
string Command::text(){
    return fromWordNum(1);
}
string Command::fromWordNum(int num){
    string str = command_line;
    for(unsigned i = 0; i < num; i++)
        split_first_word(str);
    return str;
}
void Command::flush(){
    if(log_enable){
        cerr << command_line << endl << SEPRATE << endl;
    }    command_line.erase();
    splitted_command.erase(splitted_command.begin());
}