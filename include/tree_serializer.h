#ifndef TREESERIALIZER_H
#define TREESERIALIZER_H

#include <string>
#include "tree.h"
#include "tree.pb.h"

class TreeSerializer
{
    public:
        TreeSerializer(){}
        virtual ~TreeSerializer(){}

        void Serialize(const Tree& tree,const std::string& file_name);

        Tree Deserialize(const std::string& file_name);

        static const std::string FILE_NAME;

    protected:
        bool addToNodeList(const std::string& value,ValueType valueType,const uint32_t& level);

        void SerializeTree(const Node* node,int& level);

    private:
        Serialize::NodeList node_list;
};



#endif // TREESERIALIZER_H
