#ifndef TREESERIALIZER_H
#define TREESERIALIZER_H

#include <string>
#include "tree.h"
#include "tree.pb.h"

class TreeSerializer
{
    public:
        TreeSerializer();
        ~TreeSerializer();

        void Serialize(const Tree& tree,const std::string& file_name);

        Tree Deserialize(const std::string& file_name);

        static const std::string FILE_NAME;

    protected:

        void prepareNode(Serialize::Node* parent_node,Node* node);

        bool setNodeValue(Serialize::Node* parent_node,const std::string& value,ValueType valueType);

        Node* createTree(Node* root , const Serialize::Node& node);

        Node* createNode(const Serialize::Node& node);

    private:
        Serialize::Node* root_node;
};



#endif // TREESERIALIZER_H
