#include "tree_serializer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>


const std::string TreeSerializer::FILE_NAME = "tree.bin";

TreeSerializer::TreeSerializer(){}
TreeSerializer::~TreeSerializer(){}

void TreeSerializer::clearSerializedNodes(Serialize::Node* node){

    if (node){
        for (int i = 0; i<node->childs_size(); i++){
            clearSerializedNodes(node->mutable_childs(i));
        }
        delete node;
    }
}

void TreeSerializer::Serialize(const Tree& tree,const std::string& file_name){
    std::ofstream out(file_name,std::ios::binary);

    std::cout<<"Serialize tree to \""<<file_name<<"\" file"<<std::endl;

    Serialize::Node* root_node = new Serialize::Node();
    prepareNode(root_node,tree.getHead());
    root_node->SerializePartialToOstream(&out);
    clearSerializedNodes(root_node);
}


void TreeSerializer::prepareNode(Serialize::Node* parent_node,Node* node){
    if (node){
        for (auto current_node : node->getChilds()){
            Serialize::Node* child(parent_node->add_childs());
            prepareNode(child,current_node);
        }

        if (!setNodeValue(parent_node,node->getValue(),node->getValueType())){
            std::cerr<<"Type of data is unknown"<<std::endl;
        }
    }
}

bool TreeSerializer::setNodeValue(Serialize::Node* new_node,const std::string& value,ValueType valueType){
    switch(valueType){
        case ValueType::INT_TYPE :
            new_node->set_valueint(std::stoi(value));
            new_node->set_type(Serialize::Node_TYPE::Node_TYPE_INT);
        break;

        case ValueType::STRING_TYPE:
            new_node->set_valuestring(value);
            new_node->set_type(Serialize::Node_TYPE::Node_TYPE_STRING);

        break;

        case ValueType::DOUBLE_TYPE:
            new_node->set_valuedouble(std::stod(value));
            new_node->set_type(Serialize::Node_TYPE::Node_TYPE_DOUBLE);

        break;

        default:
            return false;
    }

    return true;

}



Tree TreeSerializer::Deserialize(const std::string& file_name){
    std::ifstream in(file_name,std::ios::binary);
    Serialize::Node node;
    std::cout<<"Deserialize tree from \""<<file_name<<"\" file"<<std::endl;
    Tree* tree = nullptr;

    if (in && node.ParseFromIstream(&in)){
        std::cout<<"Deserialize successfully"<<std::endl;
        Node* head = createNode(node);
        return Tree(createTree(head,node));
    }else {
        std::cerr<<"No such file"<<std::endl;
    }

    return Tree();
}

Node* TreeSerializer::createTree(Node* node , const Serialize::Node& nodeSer){

    for (auto childNode : nodeSer.childs()){
            Node* newNode = createNode(childNode);
            if (newNode){
                node->addChild(createTree(newNode,childNode));
            }
    }

    return node;
}

Node* TreeSerializer::createNode(const Serialize::Node& nodeSer){
    Node* node = nullptr;

    switch(nodeSer.type()){
        case Serialize::Node_TYPE::Node_TYPE_INT :
            node = new IntNode(nodeSer.valueint());
        break;

        case Serialize::Node_TYPE::Node_TYPE_DOUBLE :
            node = new DoubleNode(nodeSer.valuedouble());
        break;

        case Serialize::Node_TYPE::Node_TYPE_STRING :
            node = new StringNode(nodeSer.valuestring());
        break;
    }
    return node;
}
