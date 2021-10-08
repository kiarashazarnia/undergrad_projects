#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

using namespace std;

#define JEEKSIZE 140
#define HASHTAG_MARK "#"
#define MENTION_MARK "@"

void println(string s);

class IdBank : private vector<string>{
public:
    using vector<string>::size;
    using vector<string>::at;
    string IDat(int index);
    bool have(string _id);
    void add(string _id);
    void print();
    void printby(string head = "");
    void remove(string _id);
    size_t findIndex(string Id);
private:
};

class IData{
public:
    virtual void setId(string _id);
    virtual string getId();
    virtual bool isId(string _id);
protected:
    string id;
};

template <typename Type>
class DataBase{
public:
    Type* newData(Type data = Type());
    virtual string genId() = 0;
    virtual Type* searchId(string id);
    void pop_back();
    ~DataBase();
    size_t size();
    Type* at(size_t index);
protected:
    vector<Type*> pointers;
};

class Error{
public:
    Error(string des);
    void print();
private:
    string description;
};
class ErrorNotFound : public Error{
public:
    ErrorNotFound(string s) : Error(s){}
};

template <typename Type>
Type* DataBase<Type>::searchId(string id){
    for(unsigned i = 0; i < size(); i++)
        if(dynamic_cast<IData*>(pointers.at(i)) -> isId(id) && 
            dynamic_cast<IData*>(pointers.at(i)) != NULL)
            return pointers.at(i);
    throw Error("id not found in database");        ;
}
template <typename Type>
DataBase<Type>::~DataBase(){
    for(int i = 0; i < pointers.size(); i++)
        delete pointers.at(i);
}
template <typename Type>
Type* DataBase<Type>::newData(Type data){
    Type* pointer = new Type;
    *pointer = data;
    pointers.push_back(pointer);
    pointer -> setId(genId());
    return pointer;
}
template<typename Type>
void DataBase<Type>::pop_back(){
    delete pointers.at(size() - 1);
    pointers.pop_back();
}
template<typename Type>
size_t DataBase<Type>::size(){
    return pointers.size();
}
template<typename Type>
Type* DataBase<Type>::at(size_t index){
    return pointers.at(index);
}

#endif

