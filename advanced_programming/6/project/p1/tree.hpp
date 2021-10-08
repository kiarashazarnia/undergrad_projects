#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>

#define NO_PARENT -1

enum OperatorType { Add, Multiply, Not, Median};

class Node{
public:
    virtual int evaluate() = 0;
    void set_index(int _index);
    int getindex();
    virtual Node* search(int index) = 0;
    virtual void clean() = 0;
protected:
    int index;
};

class NumberNode : public Node{
public:
    Node* search(int index);
    void set_value(int _value);
    int evaluate();
    void clean();
private:
    int value;
};
class OperatorNode : public Node{
public:
    virtual void add_child(Node* node) = 0;
    Node* search(int index);
    void clean();
protected:
    std::vector<Node*> children;
};

class BiChild : public OperatorNode{
public:
    void add_child(Node* node);
};

class MultNode : public BiChild{
public:
    int evaluate();
};

class SumNode : public BiChild{
public:
    int evaluate();
};

class MedianNode : public OperatorNode{
public:
    void add_child(Node* node);
    int evaluate();
private:
};

class NotNode : public OperatorNode{
public:
    void add_child(Node* node);
    int evaluate();
private:
};

class Tree{
public:
    Tree() : root(NULL) {}
    bool index_exist(int index);
    Node* find_n_report(int index);
    Node* new_operator_node(int index, OperatorType type);
    Node* new_number_node(int index, int value);
    void add_root(Node* node);
    void add_number_node(int index, int parent_index, int value);
    void add_operator_node(int index, int parent_index, OperatorType type);
    int evaluate();
    ~Tree();
private:
    Node* root;
};

class Error{
public:
    Error(std::string what_happend);
private:
    std::string description;
};
#endif