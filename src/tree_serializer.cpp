#include "tree_serializer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>


const std::string TreeSerializer::FILE_NAME = "tree.bin";


void TreeSerializer::Serialize(const Tree& tree,const std::string& file_name){
    std::ofstream out(file_name,std::ios::binary);
    node_list.clear_nodes();
    int level = 0;
    SerializeTree(tree.getHead(),level);
    node_list.SerializePartialToOstream(&out);
}



void TreeSerializer::SerializeTree(const Node* node,int& level){

    if (node){
        if(node->hasChild()){
            for (auto it = node->getChilds().begin(); it != node->getChilds().end(); it++){
                SerializeTree(*it,++level);
            }
        }
        if (!addToNodeList(node->getValue(),node->getValueType(),level)){
            std::cerr<<"Type of data is unknown"<<std::endl;
        }

        --level;
    }
}


bool TreeSerializer::addToNodeList(const std::string& value,ValueType valueType,const uint32_t& level){

    Serialize::Node* new_node = node_list.add_nodes();

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

    new_node->set_level(level);
    return true;
}


Tree TreeSerializer::Deserialize(const std::string& file_name){
    std::ifstream in(file_name,std::ios::binary);
    Serialize::NodeList nodeList;

    std::map<int,std::vector<Node*>> node_map;

    if (!in){
        std::cerr<<"No such file"<<std::endl;
    }else{
        if (nodeList.ParseFromIstream(&in)){
             for(const auto& value : nodeList.nodes()){
                switch(value.type()){
                    case Serialize::Node_TYPE::Node_TYPE_INT :
                        std::cout<<"value: "<<std::setw(10)<<value.valueint();
                        node_map[value.level()].push_back(new IntNode(value.valueint()));
                    break;

                    case Serialize::Node_TYPE::Node_TYPE_DOUBLE :
                        std::cout<<"value: "<<std::setw(10)<<value.valuedouble();
                        node_map[value.level()].push_back(new DoubleNode(value.valuedouble()));
                    break;

                    case Serialize::Node_TYPE::Node_TYPE_STRING :
                        std::cout<<"value: "<<std::setw(10)<<value.valuestring();
                        node_map[value.level()].push_back(new StringNode(value.valuestring()));
                    break;
                }
                std::cout<<" level: "<<std::setw(5)<<value.level()<<std::endl;
             }
        }
    }
    //return true;
}
