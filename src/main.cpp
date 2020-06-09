#include <iostream>
#include "tree_serializer.h"
#include "tree.h"

using namespace std;


int main(){

    TreeSerializer tr;

    {
        Tree souceTree(10);

        Node* node_10 = souceTree.AddChild(souceTree.getHead(),35);
        Node* node_20 = souceTree.AddChild(node_10,436);
        Node* node_11 = souceTree.AddChild(souceTree.getHead(),4444);
        Node* node_12 = souceTree.AddChild(souceTree.getHead(),"String4444");
        Node* node_30 = souceTree.AddChild(node_20,34.64);
        Node* node_21 = souceTree.AddChild(node_12,"NewString");

        cout<<"Print source tree"<<endl;
        souceTree.Print();

        tr.Serialize(souceTree,TreeSerializer::FILE_NAME);
    }

    {
        Tree desTree = tr.Deserialize(TreeSerializer::FILE_NAME);
        cout<<"\nPrint deserialized tree:"<<endl;
        desTree.Print();
    }


    return 0;
}
