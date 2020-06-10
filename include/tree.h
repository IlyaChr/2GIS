#pragma once

#include <vector>
#include <string>


enum class ValueType{
    UNKNOWN_TYPE = 0,
    STRING_TYPE = 1,
    INT_TYPE = 2,
    DOUBLE_TYPE = 3
};

class Node{
public:

    Node(std::string value,ValueType value_type);

    void addChild(Node* node);

    bool hasChild() const;

    ValueType getValueType() const;

    std::vector<Node*>& getChilds() const;

    std::string getValue() const;

protected:
    mutable std::vector<Node*> childs;
    ValueType value_type;
    std::string value;
};


class IntNode : public Node{
public:
    IntNode(int value);
};

class DoubleNode : public Node{
public:
    DoubleNode(double value);
};

class StringNode : public Node{
public:

    StringNode(std::string value);

};


class Tree
{
    public:

        Tree();

        template<typename T>
        Tree(T value);

        Tree(const Tree& otherTree);
        Tree(Tree&& otherTree);
        Tree(Node* head);

        ~Tree();

        template<typename ChildType>
        Node* AddChild(Node* node,ChildType value);

        void Print() const;

        Node* getHead() const;


    protected:
        void PrintTree(const Node* currentNode) const;

        void freeNode(Node* currentNode);


    private:
        Node* tree_head ;

        template <typename T>
        ValueType getValueType(const T& value) const;

        Node* createSpecificNode(int value);
        Node* createSpecificNode(double value);
        Node* createSpecificNode(std::string value);

};

template<typename T>
Tree::Tree(T value){
    tree_head = createSpecificNode(value);
}



template<typename ChildType>
Node* Tree::AddChild(Node* node,ChildType value){
        Node* newNode = createSpecificNode(value);
        node->addChild(newNode);
        return newNode;
}




template <typename T>
ValueType Tree::getValueType(const T& value) const{
    if (std::is_same<int,T>::value){
        return ValueType::INT_TYPE;

    } else if (std::is_same<double,T>::value){
        return ValueType::DOUBLE_TYPE;

    } else if (std::is_same<std::string,T>::value){
        return ValueType::STRING_TYPE;
    }
    return ValueType::UNKNOWN_TYPE;
}





