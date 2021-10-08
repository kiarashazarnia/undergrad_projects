#include "common.hpp"

void println(string s){
    cout << s << endl;
}
bool IdBank::have(string _id){
    for(unsigned i = 0; i < size(); i++)
        if(at(i) == _id)
            return true;
    return false;
}
void IdBank::add(string _id){
    if(have(_id))
        throw Error("duplicated id");
    push_back(_id);
}
void IdBank::print(){
    printby("");
}
void IdBank::printby(string head){
    for(unsigned i = 0; i < size(); i++)
        println(head + at(i));
}
Error::Error(string des){
    description = des;
}
void Error::print(){
    cerr << description << endl;
}
void IdBank::remove(string _id){
    if(have(_id)){
        IdBank::iterator removing = begin() + this -> findIndex(_id);
        erase(removing);
    }
}
size_t IdBank::findIndex(string _id){
    for(unsigned i = 0; i < size(); i++)
        if(at(i) == _id)
            return i;
    throw Error("id not found");        
}
void IData::setId(string _id){
    id = _id;
}
string IData::getId(){
    return id;
}
bool IData::isId(string _id){
    return id == _id;
}
string IdBank::IDat(int index){
    return at(index);
}
vector<string> IdBank::stringVec(){
    vector<string> list;
    for(unsigned i = 0; i < this -> size(); i++)
        list.push_back(this -> IDat(i));
    return list;
}

string IdBank::continousString(string head){
    string str;
    for(unsigned i = 0; i < this -> size(); i++)
        str += head + this -> IDat(i) + " ";
    return str;    
}

string vectorToString(vector<string> vec, string label){
    string str;
    for(unsigned i = 0; i < vec.size(); i++)
        str += (label + vec.at(i) + " ");
    return str;
}

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

vector<string> split(string str){
    string word;
    vector<string> splitted;
    while(str.size() != 0){
        word = split_first_word(str);
        splitted.push_back(word);
    }
    return splitted;
}