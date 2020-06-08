#include <iostream>
#include "tree_serializer.h"
#include "tree.h"

using namespace std;


typedef Node<int> IntNode;
typedef Node<string> StringNode;
typedef Node<int> DSNode;
typedef Node<int> IntNode2;

int main(){

    Tree tree(10);

    auto leftNode = tree.AddChild(tree.getHead(),34);

    auto fromLeftNode = tree.AddChild(leftNode,436);


    auto rightNode =tree.AddChild(tree.getHead(),4444);

    const Node<int>* fromRightNode_1 = tree.AddChild(rightNode,6);

    auto fromRightNode_2 = tree.AddChild(rightNode,-46);

    /*if (is_same<IntNode,StringNode>::value){
        cout<<"sd"<<endl;
    }*/

    tree.Print();


    TreeSerializer tr;
    tr.Serialize(tree);
    tr.Deserialize();

return 0;
}
