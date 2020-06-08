#include "tree.h"


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


Tree::~Tree(){
    freeNode(tree_head);
}

void Tree::freeNode(Node* currentNode){
    if (currentNode){
        if(currentNode->hasChild()){
            for (auto it = currentNode->getChilds().begin(); it != currentNode->getChilds().end(); it++){
                freeNode(*it);
            }
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
        if(currentNode->hasChild()){
            for (auto it = currentNode->getChilds().begin(); it != currentNode->getChilds().end(); it++){
                PrintTree(*it);
            }
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

/*Tree* Tree::createTreeFromMap(const std::map<int,std::vector<Node*>>& tree_map){
    Tree* tree;
    if (!tree_map.empty()){*/
        //tree = new Tree(tree_map.at(0)[0]);

        //Node* currentNode;

        /*for (const auto& [key,value] : tree_map){
            currentNode = value[];
            for (const Node& node : node){
                currentNode->addChild(node);
            }
        }*/

  //  }
  //  return tree;
//}*/



