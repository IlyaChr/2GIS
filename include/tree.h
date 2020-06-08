#pragma once

#include <vector>
#include <utility>
#include <string>
#include <iostream>



enum class ValueType{
    UNKNOWN_TYPE = 0,
    STRING_TYPE = 1,
    INT_TYPE = 2,
    DOUBLE_TYPE = 3
};

template <typename T>
struct Node{

    Node(T value):
        value(value)
        {}

    bool hasChild() const{
        return !childs.empty();
    }

    mutable std::vector<Node*> childs;
    T value;
};

template<typename T>
using NP = Node<T>*;

template<typename T>
class Tree
{
    public:
        Tree(T value);
        ~Tree();

        NP<T> AddChild(const NP<T> node,T value);

        void Print() const;

        const NP<T> getHead() const;

    protected:
        void PrintTree(const NP<T> currentNode) const;

    private:
        NP<T> tree_head ;


};


template<typename T>
Tree<T>::Tree(T value){
    tree_head = new Node<T>(std::move(value));
}

template<typename T>
Tree<T>::~Tree(){
}

template<typename T>
NP<T> Tree<T>::AddChild(const NP<T> node,T value){
            NP<T> newNode = new Node<T>(std::move(value));
            node->childs.push_back(newNode);
            return newNode;
}

template<typename T>
void Tree<T>::Print() const{
    std::cout<<"--------PrintTree--------"<<std::endl;
    PrintTree(getHead());
    std::cout<<std::endl;
}

template<typename T>
void Tree<T>::PrintTree(const NP<T> currentNode) const{


    if (currentNode){
        if(currentNode->hasChild()){
            for (auto it = currentNode->childs.begin(); it != currentNode->childs.end(); it++){
                PrintTree(*it);
            }
        }
        std::cout<<"value: "<<currentNode->value<<std::endl;
    }
}

template<typename T>
const NP<T> Tree<T>::getHead() const{
    return tree_head;
}

