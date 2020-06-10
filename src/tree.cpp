#include "tree.h"
#include <utility>
#include <iostream>
#include <memory>

Node::Node(std::string value,ValueType value_type):
        value(value),
        value_type(value_type)
        {}

void Node::addChild(Node* node){
        childs.push_back(node);
}

bool Node::hasChild() const{
        return !childs.empty();
}

ValueType Node::getValueType() const{
        return value_type;
}

std::vector<Node*>& Node::getChilds() const{
        return childs;
}

std::string Node::getValue() const{
        return value;
};


IntNode::IntNode(int value):Node(std::to_string(value),ValueType::INT_TYPE){}

DoubleNode::DoubleNode(double value):Node(std::to_string(value),ValueType::DOUBLE_TYPE){}

StringNode::StringNode(std::string value):Node(value,ValueType::STRING_TYPE){}


Tree::Tree():tree_head(nullptr){}

Tree::Tree(Node* head):tree_head(head){}


Tree::Tree(const Tree& otherTree):
    tree_head(otherTree.tree_head){}


Tree::Tree(Tree&& otherTree):
    tree_head(otherTree.tree_head){
    otherTree.tree_head = nullptr;
}

Tree::~Tree(){
    freeNode(tree_head);
}

void Tree::freeNode(Node* currentNode){
    if (currentNode){
        for (auto node : currentNode->getChilds()){
            freeNode(node);
        }
        delete currentNode;
    }
}



void Tree::Print() const{
    std::cout<<"--------PrintTree--------"<<std::endl;
    PrintTree(getHead());
    std::cout<<std::endl;
}


void Tree::PrintTree(const Node* currentNode) const{
    if (currentNode){
        for (auto node : currentNode->getChilds()){
            PrintTree(node);
        }
        std::cout<<"value: "<<currentNode->getValue()<<std::endl;
    }
}


Node* Tree::getHead() const{
    return tree_head;
}



Node* Tree::createSpecificNode(std::string value){
    return new StringNode(std::move(value));
}


Node* Tree::createSpecificNode(int value){
    return new IntNode(std::move(value));
}


Node* Tree::createSpecificNode(double value){
    return new DoubleNode(std::move(value));
}



