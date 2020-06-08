#include <iostream>
#include "tree_serializer.h"
#include "tree.h"

using namespace std;


int main(){


    Tree tree(10);

    Node* node_10 = tree.AddChild(tree.getHead(),35);
    Node* node_20 = tree.AddChild(node_10,436);
    Node* node_11 =tree.AddChild(tree.getHead(),4444);
    Node* node_12 =tree.AddChild(tree.getHead(),"String4444");
    Node* node_30 = tree.AddChild(node_20,34.64);

    tree.Print();

    TreeSerializer tr;
    tr.Serialize(tree,TreeSerializer::FILE_NAME);
    tr.Deserialize(TreeSerializer::FILE_NAME);


return 0;
}
