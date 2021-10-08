#include "tree.hpp"
void Tree::add_root(Node* node){
    if(root != NULL)
        throw Error("duplication root");
    root = node;
}
Node* Tree::find_n_report(int index){
    if(!index_exist(index))
        throw Error("parent not found");
    return root -> search(index);
}
void Tree::add_number_node(int index, int parent_index, int value){
    if(index_exist(index))
        throw Error("index duplication");
    Node* node = new_number_node(index, value);
    if(parent_index == NO_PARENT)
        return add_root(node);
    Node* parent = find_n_report(parent_index);
    dynamic_cast<OperatorNode*> (parent) -> add_child(node);
}
void Tree::add_operator_node(int index, int parent_index, OperatorType type){
    if(index_exist(index))
        throw Error("index duplication");
    Node* node = new_operator_node(index, type);
    if(parent_index == NO_PARENT)
        return add_root(node);
    Node* parent = find_n_report(parent_index);
    dynamic_cast<OperatorNode*> (parent) -> add_child(node);
}
int Tree::evaluate(){
    if(root == NULL)
        throw Error("no tree to evaluate");
    return root -> evaluate();
}
int MultNode::evaluate(){
    if(children.size() != 2){
        throw Error("multiply error");
    }
    int a = children.at(0) -> evaluate();
    int b = children.at(1) -> evaluate();
    return a * b;
}
int SumNode::evaluate(){
    if(children.size() != 2){
        throw Error("summation error");
    }
    int a = children.at(0) -> evaluate();
    int b = children.at(1) -> evaluate();    
    return a + b;
}
int MedianNode::evaluate(){
    if(children.size() == 0){
        throw Error("median error");
    }
    int sum = 0, med;
    int n = children.size();
    for(int i = 0; i < n; i++){
        sum += children.at(i) -> evaluate();
    }
    med = sum / n;
    return med;
}
int NotNode::evaluate(){
    if(children.size() != 1){
        throw Error("not error");
    }
    int val = children.at(0) -> evaluate();
    return -val;
}
int NumberNode::evaluate(){
    return value;
}
void Node::set_index(int _index){
    index = _index;
}
int Node::getindex(){
    return index;
}
Node* OperatorNode::search(int _index){
    if(index == _index)
        return this;
    Node* node;
    for(int i = 0; i < children.size(); i++){
        node = children.at(i) -> search(_index);
        if(node != NULL)
            return node;
    }
    return NULL;
}
Node* NumberNode::search(int _index){
    if(index == _index)
        return this;
    else
        return NULL;
}
Node* Tree::new_number_node(int index, int value){
    Node* node = new NumberNode;
    node -> set_index(index);
    dynamic_cast<NumberNode*> (node) -> set_value(value);
    return node;
}
Node* Tree::new_operator_node(int index, OperatorType type){
    Node* node;
    switch(type){
        case Add:
            node = new SumNode; break;
        case Multiply:
            node = new MultNode; break;
        case Not:
            node = new NotNode; break;
        case Median:
            node = new MedianNode; break;
        default:
            throw Error("invalid type");
    }
    node -> set_index(index);
    return node;
}
void BiChild::add_child(Node* node){
    if(children.size() >= 2)
        throw Error("full node");
    children.push_back(node);
}
void MedianNode::add_child(Node* node){
    children.push_back(node);
}
void NotNode::add_child(Node* node){
    if(children.size() >= 1)
        throw Error("full node");
    children.push_back(node);
}
void NumberNode::set_value(int _value){
    value = _value;
}
Error::Error(std::string what_happend){
    description = what_happend;
    std::cerr << what_happend << std::endl;
}
bool Tree::index_exist(int index){
    if(root != NULL){
        Node* node = root -> search(index);
        if(node != NULL){
            return 1;
        }
    }
    return 0;
}
Tree::~Tree(){
    if(root != NULL)
        root -> clean();
}
void NumberNode::clean(){
    delete this;
}
void OperatorNode::clean(){
    for(int i = 0; i < children.size(); i++)
        children.at(i) -> clean();
    delete this;
}
