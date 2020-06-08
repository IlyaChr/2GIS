#ifndef TREESERIALIZER_H
#define TREESERIALIZER_H

#include <fstream>
#include "tree.h"
#include "tree.pb.h"

class TreeSerializer
{
    public:
        TreeSerializer(){}
        virtual ~TreeSerializer(){}

        template<typename T>
        void Serialize(const Tree<T>& tree);
        bool Deserialize();

        static const std::string FILE_NAME;

    protected:
        template<typename T>
        bool addToNodeList(const T& value,const uint32_t& level);

        template<typename T>
        void SerializeTree(const Node<T>* node,int& level);

    private:
        Serialize::NodeList node_list;
};

template<typename T>
void TreeSerializer::Serialize(const Tree<T>& tree){
    std::ofstream out(FILE_NAME,std::ios::binary);
    node_list.clear_nodes();
    int level = 0;
    SerializeTree(tree.getHead(),level);
    node_list.SerializePartialToOstream(&out);
}




template<typename T>
void TreeSerializer::SerializeTree(const Node<T>* node,int& level){

    if (node){
        if(node->hasChild()){
            for (auto it = node->childs.begin(); it != node->childs.end(); it++){
                SerializeTree(*it,++level);
            }
        }
        if (!addToNodeList(node->value,level)){
            std::cerr<<"Type of data is unknown"<<std::endl;
        }

        --level;
    }
}


template<typename T>
bool TreeSerializer::addToNodeList(const T& value,const uint32_t& level){

    Serialize::Node* new_node = node_list.add_nodes();

    if (std::is_same<int,T>::value){
        new_node->set_valueint(value);
        new_node->set_type(Serialize::Node_TYPE::Node_TYPE_INT);

    }else if (std::is_same<std::string,T>::value){
        new_node->set_valuestring(std::to_string(value));
        new_node->set_type(Serialize::Node_TYPE::Node_TYPE_STRING);

    }else if (std::is_same<double,T>::value){
        new_node->set_valuedouble(value);
        new_node->set_type(Serialize::Node_TYPE::Node_TYPE_DOUBLE);

    }else{
        return false;
    }

    new_node->set_level(level);
    return true;
}



#endif // TREESERIALIZER_H
