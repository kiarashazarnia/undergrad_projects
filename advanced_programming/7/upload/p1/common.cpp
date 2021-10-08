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